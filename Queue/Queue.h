#pragma once


struct Node
{
	int _data;
	Node* _next;
	Node(int data, Node* next = nullptr)
		:	_data(data), _next(next)
	{}
};

class Queue
{
private:
	Node* _front;	//front of the queue, dequeue here, equiv to _head
	Node* _back;	//back of the queue, enqueue here, equiv to _tail
	size_t _size;

private:
	void CopyFrom(const Queue& other);

public:
	Queue();
	Queue(const Queue& other);
	~Queue();
	Queue& operator=(const Queue& other);

	void Clear();

	void Enqueue(int value);
	void Dequeue();

	inline bool Empty() const
	{
		return _front == nullptr;
	}

	inline size_t Size() const
	{
		return _size;
	}

	void Print(std::ostream& outS = std::cout) const;

};

Queue::Queue()
	: _front(nullptr), _back(nullptr), _size(0)
{}

Queue::Queue(const Queue& other)
	: _front(nullptr), _back(nullptr), _size(0)
{
	CopyFrom(other);
}

Queue::~Queue()
{
	Clear();
}

inline Queue & Queue::operator=(const Queue & other)
{
	if (this != &other)
	{
		Clear();
		CopyFrom(other);
	}

	return *this;		// TODO: insert return statement here
}


inline void Queue::Clear()
{
	if (Empty())
		return;

	Node* destroyer = _front;
	while (_front != nullptr)
	{
		destroyer = _front;
		_front = _front->_next;
		delete destroyer;
	}

	 _front = _back = nullptr;
	_size = 0;
}

inline void Queue::CopyFrom(const Queue & other)
{
	if (other.Empty())
		return;

	_front = new Node(other._front->_data);

	Node* from = other._front;
	Node* to = _front;

	while (from->_next != nullptr)
	{
		from = from->_next;
		to->_next = new Node(from->_data);
		to = to->_next;
	}

	_back = to;
	_size = other._size;
}

inline void Queue::Enqueue(int value)
{
	Node* entry = new Node(value);
	_size++;

	if (Empty())
	{
		_front = _back = entry;
		return;
	}

	_back->_next = entry;
	_back = entry;
}

inline void Queue::Dequeue()
{
	if (Empty())
		return;

	if (_size == 1)
	{
		Clear();
		return;
	}

	Node* destroyer = _front;
	_front = _front->_next;
	delete destroyer;

	_size--;

}


inline void Queue::Print(std::ostream & outS) const
{
	if (Empty())
	{
		outS << "Empty queue!\n";
		return;
	}

	const Node* it = _front;

	while (it != nullptr)
	{
		outS << it->_data << " -> ";
	}

	outS << '\n';
}
