	#include "DoublyLinkedList.h"




DoublyLinkedList::DoublyLinkedList()
	: _head(nullptr), _tail(nullptr), _size(0)
{}


DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList & other)
	: _head(nullptr), _tail(nullptr), _size(0)
{
	CopyFrom(other);
}

DoublyLinkedList::~DoublyLinkedList()
{
	Clear();
}


DoublyLinkedList & DoublyLinkedList::operator=(const DoublyLinkedList & other)
{
	if (this != &other)
	{
		Clear();
		CopyFrom(other);
	}

	return *this;		// TODO: insert return statement here
}

void DoublyLinkedList::CopyFrom(const DoublyLinkedList& other)
{
	if (other.Empty())
		return;

	//copying the head
	_head = new Node(other._head->_data);

	Node* from = other._head;
	Node* to = _head;

	while (from->_next != nullptr)
	{
		from = from->_next;
		to->_next = new Node(from->_data, to);
		to = to->_next;
	}

	_tail = to;
	_size = other._size;
}


void DoublyLinkedList::Clear()
{
	if (Empty())
		return;

	Node* destroyer = nullptr;

	while (_head != nullptr)
	{
		destroyer = _head;
		_head = _head->_next;
		delete destroyer;
	}

	_head = nullptr;
	_tail = nullptr;
	_size = 0;
}


void DoublyLinkedList::PushBack(int element)
{
	Node* entry = new Node(element);
	_size++;

	if (Empty())
	{
		_tail = _head = entry;
		return;
	}

	entry->_prev = _tail;
	_tail->_next = entry;
	_tail = entry;
}

void DoublyLinkedList::PushFront(int element)
{
	Node* entry = new Node(element);
	_size++;

	if (Empty())
	{
		_tail = _head = entry;
		return;
	}

	entry->_next = _head;
	_head->_prev = entry;
	_head = entry;
}

void DoublyLinkedList::PopBack()
{
	if (Empty())
		return;

	if (_head == _tail)
	{
		Clear();
		return;
	}

	_tail = _tail->_prev;
	delete _tail->_next;
	_tail->_next = nullptr;

	_size--;
}

void DoublyLinkedList::PopFront()
{
	if (Empty())
		return;

	if (_size == 1)
	{
		Clear();
		return;
	}

	_head = _head->_next;
	delete _head->_prev;
	_head->_prev = nullptr;

	_size--;
}

void DoublyLinkedList::PrintList(std::ostream & outS) const
{
	Node* it = _head;

	while (it != nullptr)
		outS << it->_data << ", ";

	outS << '\n';
}

void DoublyLinkedList::Reverse()
{
	if (Empty() || _size == 1)
		return;

	//set the tail
	_tail = _head;

	Node* temp = nullptr;
	Node* curr = _head;

	while (curr != nullptr)
	{
		temp = curr->_prev;
		curr->_prev = curr->_next;
		curr->_next = temp;

		curr = curr->_next;
	}






}


















