#include <iostream>
#include <cstdlib>
#include <vector>

using std::cout;
using std::cin;
using int64 = long long;




struct Snowball
{
	int _ball_mass;
	Snowball* _prev;
	Snowball* _next;

	Snowball(int ball_mass, Snowball* prev = nullptr, Snowball* next = nullptr)
		: _ball_mass(ball_mass), _prev(prev), _next(next)
	{}
};

class DoublyLinkedList
{
private:
	Snowball* _head, *_tail;
	int64 _total_mass;

public:

	//to create the initial snowman
	DoublyLinkedList()
		: _head(nullptr), _tail(nullptr), _total_mass(0)
	{
		Snowball* entry = new Snowball(0);

		_head = _tail = entry;
	}

	DoublyLinkedList(const DoublyLinkedList& other)
		: _head(nullptr), _tail(nullptr), _total_mass(0)
	{
		CopyFrom(other);
	}

	DoublyLinkedList& operator=(const DoublyLinkedList& other)
	{
		if (this != &other)
		{
			Clear();
			CopyFrom(other);
		}

		return *this;
	}


	DoublyLinkedList(const DoublyLinkedList& clone, int mass)
		: _head(nullptr), _tail(nullptr)
	{
		CopyFrom(clone);

		if (mass == 0)
		{
			if (_head == _tail)		//we dont pop if we have 1 element
				return;
			else
				PopBack();	//O(1)
		}
		else
			PushBack(mass); // O(1)

	}

	~DoublyLinkedList()
	{
		Clear();
	}

	inline bool Empty() const
	{
		return _head == nullptr ? true : false;
	}

	void Clear()
	{
		if (Empty())
			return;

		Snowball* destroyer = nullptr;

		while (_head != nullptr)
		{
			destroyer = _head;
			_head = _head->_next;
			delete destroyer;
		}

		_head = nullptr;
		_tail = nullptr;
		_total_mass = 0;
	}

	void CopyFrom(const DoublyLinkedList& other)
	{
		if (other.Empty())
			return;

		//copy _head first
		_head = new Snowball(other._head->_ball_mass);

		Snowball* from = other._head;
		Snowball* to = _head;

		while (from->_next != nullptr)
		{
			from = from->_next;
			to->_next = new Snowball(from->_ball_mass, to);		//make node and attach it to its _prev and _next
			to = to->_next;
		}
		_tail = to;			//at the end of the loop to points just before null
		_total_mass = other._total_mass;
	}

	void PushBack(int mass)
	{
		Snowball* entry = new Snowball(mass);
		_total_mass += mass;

		if (Empty())
			_tail = _head = entry;

		else
		{
			entry->_prev = _tail;
			_tail->_next = entry;
			_tail = entry;
		}
	}


	void PopBack()
	{
		if (Empty())
			return;

		//if (_head == _tail);

		_total_mass -= _tail->_ball_mass;

		_tail = _tail->_prev;
		delete _tail->_next;
		_tail->_next = nullptr;
	}

	Snowball* Begin()
	{
		return _head;
	}


	void PrintList(std::ostream& outS = std::cout) const
	{
		Snowball* it = _head;
		int counter = 0;

		while (it != nullptr)
		{
			outS << "node " << counter;
			outS << " : mass " << it->_ball_mass << '\n';
			it = it->_next;
			counter++;
		}

		outS << '\n';
	}


	inline int64 GetTotalMass() const
	{
		return _total_mass;
	}

};

int main() {

	int N = 0;
	int clone_from, mass;

	std::vector<DoublyLinkedList> snowman_list;
	int64 overall_sum = 0;

	//adding the 0-th snowman
	snowman_list.push_back(DoublyLinkedList());

	cin >> N;
	snowman_list.reserve(N);

	for (int i = 0; i < N; i++)
	{
		cin >> clone_from >> mass;
		snowman_list.push_back(DoublyLinkedList(snowman_list[clone_from], mass));
	//	overall_sum += snowman_list[i + 1].GetTotalMass();
	}


	for (auto& s : snowman_list)
		overall_sum += s.GetTotalMass();

	cout << overall_sum << '\n';


	std::system("pause");
	return 0;
}