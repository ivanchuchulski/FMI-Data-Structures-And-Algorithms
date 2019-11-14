#pragma once

struct Node
{
	int _data;
	Node* _next;

	Node(int data, Node* next = nullptr)
		:	_data(data), _next(next)
	{}
};


class Stack
{
public:
	Stack();
	Stack(const Stack& other);
	~Stack();
	Stack& operator=(const Stack& other);

	void Clear();

	bool Empty() const;
	int Size() const;

	int Peek() const

	void Push(int value);
	void Pop();

private:
	void CopyOtherStack(const Stack& other);

private:
	Node* _top;
	size_t _size;
};


inline Stack::Stack()
	: _top(nullptr), _size(0)
{}

inline Stack::Stack(const Stack & other)
	: _top(nullptr), _size(0)
{
	CopyOtherStack(other);
}

inline Stack::~Stack()
{
	Clear();
}

inline Stack& Stack::operator=(const Stack& other)
{
	if (this != &other)
	{
		Clear();

		if (!other.Empty()) 
		{
			CopyOtherStack(other);
		}
	}

	return *this;
}

inline void Stack::Clear()
{
	if (Empty())
	{
		return;
	}

	Node* destroyer = nullptr;

	while (_top != nullptr)
	{
		destroyer = _top;
		_top = _top->_next;
		delete destroyer;
	}

	_size = 0;
}

inline void Stack::CopyOtherStack(const Stack& other)
{
	//copy _top first
	_top = new Node(other._top->_data);

	Node* from = other._top;
	Node* to = _top;

	while (from->_next != nullptr)
	{
		from = from->_next;
		to->_next = new Node(from->_data);
		to = to->_next;
	}

	_size = other._size;
}


bool Stack::Empty() const
{
	return _top == nullptr;
}

int Stack::Size() const
{
	return _size;
}

int Stack::Peek() const
{
	return _top->_data;
}


void Stack::Push(int value)
{
	Node* entry = new Node(value);
	_size++;

	if (Empty())
	{
		_top = entry;
		return;
	}

	entry->_next = _top;
	_top = entry;
}

void Stack::Pop()
{
	if (Empty())
	{
		return;
	}

	Node* destroyer = _top;
	_top = _top->_next;

	delete destroyer;
	_size--;
}

