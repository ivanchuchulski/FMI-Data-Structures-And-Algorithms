#include "ForwardListTailless.h"


ForwardListTailless::ForwardListTailless()
	:	_head(nullptr),  _size(0)
{}

ForwardListTailless::ForwardListTailless(const ForwardListTailless& other)
	:	_head(nullptr), _size(0)
{
	CopyFrom(other);
}

ForwardListTailless & ForwardListTailless::operator=(const ForwardListTailless& other)
{
	if (this != &other)
	{
		Clear();
		CopyFrom(other);
	}

	return *this;		// TODO: insert return statement here
}

ForwardListTailless::~ForwardListTailless()
{
	Clear();
}

void ForwardListTailless::CopyFrom(const ForwardListTailless& other)
{
	if (other.Empty())
		return;

	//copy _head first
	_head = new Node(other._head->_data);

	Node* from = other._head;
	Node* to = _head;

	while (from->_next != nullptr)
	{
		from = from->_next;
		to->_next = new Node(from->_data);
		to = to->_next;
	}

	_size = other._size;
}

void ForwardListTailless::Clear()
{
	Node* destroyer = nullptr;
	while (_head != nullptr)
	{
		destroyer = _head;
		_head = _head->_next;		//advance
		delete destroyer;			//destoy previous
	}

	_head = nullptr;
	_size = 0;
}


void ForwardListTailless::PrintList(std::ostream& outS) const
{
	if (Empty())
	{
		outS << "empty list {}\n";
		return;
	}

	Node* it = _head;

	while (it != nullptr)
	{
		outS << it->_data << ' ';
		it = it->_next;
	}
	
	outS << '\n';
}

void ForwardListTailless::PushBack(int value)
{
	Node* entry = new Node(value);
	_size++;

	if (Empty())
	{
		_head = entry;
		return;
	}

	Node* it = _head;
	
	while (it->_next != nullptr)	//go until the last node
		it = it->_next;

	it->_next = entry;
}

void ForwardListTailless::PushFront(int value)
{
	Node* entry = new Node(value);
	_size++;

	if (Empty())
	{
		_head = entry;
		return;
	}

	entry->_next = _head;
	_head = entry;
}


// list positions are counted from 1
void ForwardListTailless::InsertAt(int pos, int value)
{
	if (pos > _size || pos < 1)
		return;

	Node* to_add = new Node(value);
	_size++;

	Node* prev = nullptr;
	Node *curr = _head;

	for (int i = 1; i < pos; i++)
	{
		prev = curr;
		curr = curr->_next;
	}

	prev->_next = to_add;
	to_add->_next = curr;
}

void ForwardListTailless::DeleteFirst()
{
	if (Empty())
		return;

	Node* to_remove = _head;	//holds the old _head

	_head = _head->_next;
	delete to_remove;
	_size--;
}

void ForwardListTailless::DeleteLast()
{
	if (Empty())
		return;

	if (_size == 1)		//if we have only a 1 node
	{
		Clear();
		return;
	}

	Node* prev = nullptr;
	Node* curr = _head;

	while (curr->_next != nullptr)
	{
		prev = curr;
		curr = curr->_next;
	}

	//after the loop curr to the backmost node
	prev->_next = nullptr;
	delete curr;
	_size--;
}

void ForwardListTailless::DeleteAt(int pos)
{
	if (pos > _size || pos < 1)
		return;

	Node* prev = nullptr;
	Node* curr = _head;

	for (int i = 1; i < pos; i++)
	{
		prev = curr;
		curr = curr->_next;
	}

	prev->_next = curr->_next;
	delete curr;
}


void ForwardListTailless::Reverse()
{
	if (Empty() || _size == 1)
		return;

	Node* prev = nullptr;
	Node* curr = _head;
	Node* next = nullptr;

	while (curr != nullptr)
	{
		next = curr->_next;

		curr->_next = prev;

		prev = curr;
		curr = next;
	}

	_head = prev;	//curr is pointing at null at the end of the loop, so prev is the last node
}














