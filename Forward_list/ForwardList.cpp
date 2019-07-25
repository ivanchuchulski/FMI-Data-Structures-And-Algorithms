
#include "ForwardList.h"


ForwardList::ForwardList()
	: _head(nullptr), _tail(nullptr), _size(0)
{}

ForwardList::ForwardList(const ForwardList& other)
	:	_head(nullptr), _tail(nullptr), _size(0)
{
	CopyFrom(other);
}

ForwardList & ForwardList::operator=(const ForwardList & other)
{
	if (this != &other)
	{
		Clear();
		CopyFrom(other);
	}

	return *this;		// TODO: insert return statement here
}

ForwardList::~ForwardList()
{
	Clear();
}

void ForwardList::Clear()
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

	_head = _tail = nullptr;
	_size = 0;
}

void ForwardList::CopyFrom(const ForwardList & other)
{
	if (other.Empty())
		return;

	//copy _head first
	_head = new Node {other._head->_data, nullptr};

	Node* from = other._head;
	Node* to = _head;

	while (from->_next != nullptr)
	{
		from = from->_next;
		to->_next = new Node{from->_data, nullptr};
		to = to->_next;
	}
	_tail = to;			//at the end of the loop to points just before null
	_size = other._size;
}


void ForwardList::PrintList(std::ostream& outS) const
{
	Node* it = _head;

	while (it != nullptr)
	{
		outS << "#" << it->_data << ' ';
		it = it->_next;
	}

	outS << '\n';
}

void ForwardList::PushBack(int value)
{
	Node* entry = new Node{value, nullptr};
	_size++;

	if (Empty())
	{
		_tail = _head = entry;
		return;
	}

	_tail->_next = entry;		//the previous last now points to the newly created node
	_tail = entry;
}

void ForwardList::PushFront(int value)
{
	Node* entry = new Node{value, nullptr};
	_size++;

	if (Empty())
	{
		_tail = _head = entry;
		return;
	}

	entry->_next = _head;
	_head = entry;
}

// list positions are counted from 1
void ForwardList::InsertAt_cf1(int pos, int value)
{
	if (pos < 1 || pos > _size)		//invalid index
		return;

	if (pos == 1)
	{
		PushFront(value);
		return;
	}

	Node* to_add = new Node{value, nullptr};
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

void ForwardList::DeleteFirst()
{
	if (Empty())
		return;

	if (_size == 1)
	{
		delete _head;
		_head = _tail = nullptr;
		_size = 0;
		return;
	}

	Node* destroy = _head;

	_head = _head->_next;
	delete destroy;
	_size--;
}

void ForwardList::DeleteLast()
{
	if (Empty())
		return;

	if (_size == 1)
	{
		delete _head;
		_head = _tail = nullptr;
		_size = 0;
		return;
	}

	Node* penult = _head;		//penultimate Node, the one before _tail

	while (penult->_next != _tail)
		penult = penult->_next;
	
	delete _tail;
	_size--;

	penult->_next = nullptr;
	_tail = penult;
}

void ForwardList::DeleteAt_cf1(int pos)
{
	if (pos < 1 || pos > _size)
		return;

	if (pos == 1)
	{
		DeleteFirst();
		return;
	}

	if (pos == _size)
	{
		DeleteLast();
		return;
	}

	Node* prev = nullptr;
	Node* curr = _head;

	for (int i = 1; i < pos; i++)
	{
		prev = curr;
		curr = curr->_next;
	}

	prev->_next = curr->_next;
	delete curr;
	_size--;
}

void ForwardList::Reverse()
{
	if (Empty() || _size == 1)
		return;

	//the new tail is the old head
	_tail = _head;

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

	_head = prev;

}


void ForwardList::InsertAt(int value, int pos)	//positions are counted from 0
{
	if (pos < 0  || pos > _size)	//invalid index
		return;

	if (pos == 0) 
	{
		PushFront(value);
		return;
	}

	Node* entry = new Node{value, nullptr};
	_size++;

	Node* prev = nullptr;
	Node* curr = _head;

	for (int i = 0; i < pos; i++)
	{
		prev = curr;
		curr = curr->_next;
	}

	prev->_next = entry;
	entry->_next = curr;
}


void ForwardList::DeleteAt(int pos)
{
	if (pos < 0 || pos > _size)
		return;

	if (pos == 0)
	{
		DeleteFirst();
		return;
	}

	Node* prev = nullptr;
	Node* curr = _head;

	for (int i = 0; i < pos; i++)
	{
		prev = curr;
		curr = curr->_next;
	}

	prev->_next = curr->_next;

	delete curr;
	_size--;
}

void ForwardList::Reverse_v2()
{
	Node* prev = nullptr;
	Node* temp = nullptr;

	_tail = _head;
	while (_head != nullptr)
	{
		temp = _head->_next;
		_head->_next = prev;

		prev = _head;
		_head = temp;
	}
	_head = prev;
}

