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
private:
	Node* _top;
	size_t _size;

private:
	void CopyFrom(const Stack& other);

public:

	Stack();
	Stack(const Stack& other);
	~Stack();
	Stack& operator=(const Stack& other);

	void Clear();

	void Push(int value);
	void Pop();



	int Peek() const
	{
		return _top->_data;
	}

	inline bool Empty() const
	{
		return _top == nullptr;
	}


};

inline Stack::Stack()
	: _top(nullptr), _size(0)
{}

inline Stack::Stack(const Stack & other)
	: _top(nullptr), _size(0)
{
	CopyFrom(other);
}


inline Stack::~Stack()
{
	Clear();
}

inline Stack & Stack::operator=(const Stack & other)
{
	if (this != &other)
	{
		Clear();
		CopyFrom(other);
	}

	return *this;// TODO: insert return statement here
}

inline void Stack::Clear()
{
	if (Empty())
		return;

	Node* destroyer = nullptr;

	while (_top != nullptr)
	{
		destroyer = _top;
		_top = _top->_next;
		delete destroyer;
	}

	_size = 0;
}

inline void Stack::CopyFrom(const Stack& other)
{
	if (other.Empty())
		return;

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


inline void Stack::Push(int value)
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

inline void Stack::Pop()
{
	if (Empty())
		return;

	Node* destroyer = _top;
	_top = _top->_next;

	delete destroyer;
	_size--;
}







