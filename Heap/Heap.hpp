#pragma once

#include <vector>
#include <functional>
#include <algorithm>

bool Greater(int lhs, int rhs)
{
	return lhs > rhs;
};

bool Smaller(int lhs, int rhs)
{
	return lhs < rhs;
}

class Heap
{
private:
	std::vector<int> _arr;
	std::function<bool(int, int)> _comparator;

protected:
	void SiftUp(int ind);
	void SiftDown(int ind);

	int Left(int i);
	int Right(int i);
	int Parent(int i);

public:
	//ctors and dtor
	Heap();
	Heap(const Heap& other);
	Heap(std::function<bool(int, int)> comparator);
	~Heap();

	Heap& operator=(const Heap& other);

	bool Empty() const;
	int Size() const;

	void Insert(int value);

	int GetTop();
	int ExtractTop();
};


Heap::Heap() : _arr(), _comparator(Greater)
{}

Heap::~Heap()
{}

Heap::Heap(const Heap& other) : _arr(), _comparator(other._comparator)
{}

Heap::Heap(std::function<bool(int, int)> comparator) : _arr(), _comparator(comparator)
{}

inline Heap & Heap::operator=(const Heap& other)
{
	if (this != &other)
	{
		_arr = other._arr;
		_comparator = other._comparator;
	}

	return *this;		// TODO: insert return statement here
}

bool Heap::Empty() const
{
	return _arr.empty();
}

int Heap::Size() const
{
	return _arr.size();
}

void Heap::Insert(int value)
{
	_arr.push_back(value);

	SiftUp(_arr.size() - 1);
}

int Heap::GetTop()
{
	if (_arr.empty())
		return -1;	//or throw...

	return _arr.front();
}

int Heap::ExtractTop()
{
	if (_arr.empty())
		return -1;	//or throw...
	
	int top = _arr.front();

	_arr.front() = _arr.back();
	_arr.pop_back();

	SiftDown(0);

	return top;
}

int Heap::Left(int i)
{
	return 2 * i + 1;
}

int Heap::Right(int i)
{
	return 2 * i + 2;
}

int Heap::Parent(int i)
{
	return (i - 1) / 2;
}

void Heap::SiftUp(int ind)
{
	while (ind != 0 && _comparator(_arr[ind], _arr[Parent(ind)]))
	{
		std::swap(_arr[ind], _arr[Parent(ind)]);
		ind = Parent(ind);
	}
}

void Heap::SiftDown(int ind)
{
	int prioritized = ind;
	int left = Left(ind);
	int right = Right(ind);

	if (left < Size() && _comparator(_arr[left], _arr[prioritized]))
		prioritized = left;

	if (right < Size() && _comparator(_arr[right], _arr[prioritized]))
		prioritized = right;

	if (prioritized != ind)
	{
		std::swap(_arr[prioritized], _arr[ind]);
		SiftDown(prioritized);
	}

}