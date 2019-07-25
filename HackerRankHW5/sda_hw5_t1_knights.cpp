#include <iostream>
#include <cstdlib>


using std::cout;
using std::cin;


struct Node
{
	int _data;
	Node* _next;
	Node(int data, Node* next = nullptr)
		: _data(data), _next(next)
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
	Queue()
		: _front(nullptr), _back(nullptr), _size(0)
	{}

	Queue(const Queue& other)
		: _front(nullptr), _back(nullptr), _size(0)
	{
		CopyFrom(other);
	}

	~Queue()
	{
		Clear();
	}

	Queue& operator=(const Queue& other)
	{
		if (this != &other)
		{
			Clear();
			CopyFrom(other);
		}

		return *this;		// TODO: insert return statement here
	}

	void Clear();

	void Enqueue(int value);
	void Dequeue();

	inline bool Empty() const
	{
		return _front == nullptr;
	}

	void Print(std::ostream& outS = std::cout) const;

	Node* Front()
	{
		return _front;
	}

	size_t Size() { return _size; }
};


int main() {
	
	const size_t kill_ratio = 2;
	unsigned N;
	Queue knights;

	cin >> N;



	//put all people with odd indeces in the queue
	//the ones with even indeces will get killed in the first round
	for (size_t i = 0; i < N; i++)
	{
		if ((i + 1) % 2 != 0)
			knights.Enqueue(i + 1);
		else
			continue;
	}

	knights.Print();

	//if N is odd, after the first round(where all the even knights are eliminated)
	//the lastly enqueued knight should kill first, so we enqueue all the others before him 
	if (N % 2 != 0)
	{
		for (int i = 0; i < knights.Size() - 1; i++)
		{
			knights.Enqueue(knights.Front()->_data);
			knights.Dequeue();
		}
	}

	knights.Print();

	size_t alive = knights.Size();
	Node* killer = knights.Front();
	Node* victim = nullptr;

	while (alive != 1)
	{
		victim = killer->_next;

		knights.Enqueue(killer->_data);		//putting the killer at the back of the queue

		killer = victim->_next;

		for (size_t i = 1; i <= kill_ratio; i++)	//removing the killer and the victim from the front of the queue
			knights.Dequeue();

		alive--;
	}

	//knights.Print();

	//the last remaining
	cout << knights.Front()->_data << '\n';

	std::system("pause");
	return 0;
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

void Queue::Enqueue(int value)
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

void Queue::Dequeue()
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

	while (it->_next != nullptr)		//printing until the last
	{
		outS << it->_data << " -> ";
		it = it->_next;
	}

	outS << it->_data << '\n';		//printing the last
}