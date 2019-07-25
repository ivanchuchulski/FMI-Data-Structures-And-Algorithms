#pragma once

#include <vector>
#include <functional>
#include <algorithm>
#include <stdexcept>

/* in the C++ Standart Library when using a priority_queue, for MaxHeap the Comparison param is set to std::less,
	and to achieve for MinHeap it should be set to std::greater
	then the expressions in th SiftUp and Sift Down should be different from the ones in my implementation

	e.g. for MaxHeap with Comparison := std::less
	in SiftUp :
	while ( ind != 0 && !_cmp(_arr[ind], _arr[Parent(ind)]) ){ ..same.. }

*/

//by using std::greater we are defining a MaxHeap
template<typename T, typename Comparison = std::greater<T>>
class TemplateHeap
{
private:
	std::vector<T> _arr;
	Comparison _cmp;

protected:
	int Left(int ind) { return 2 * ind + 1; }

	int Right(int ind) { return 2 * ind + 2; }

	int Parent(int ind)
	{
		if (Empty())
			return -1;

		return (ind - 1) / 2;
	}

	void SiftUp(int ind);
	void SiftDown(int ind);

public:
	TemplateHeap() : _arr(), _cmp()
	{}

	TemplateHeap(const TemplateHeap<T, Comparison>& other) : _arr(other._arr), _cmp(other._cmp)
	{}

	TemplateHeap& operator=(const TemplateHeap<T, Comparison>& other)
	{
		if (this != &other)
		{
			_arr = other._arr;
			_cmp = other._cmp;
		}

		return *this;
	}

	~TemplateHeap()
	{}

	bool Empty() const { return _arr.empty(); }
	int Size() const { return _arr.size(); }

	void Insert(const T& value);

	T GetTop() const;
	T ExtractTop();

};


template<typename T, typename Comparison>
void TemplateHeap<T, Comparison>::Insert(const T & value)
{
	_arr.push_back(value);

	SiftUp(Size() - 1);
}

template<typename T, typename Comparison>
T TemplateHeap<T, Comparison>::GetTop() const
{
	if (Empty())
		throw std::out_of_range("out of range");

	return _arr.front();
}

template<typename T, typename Comparison>
T TemplateHeap<T, Comparison>::ExtractTop()
{
	if (Empty())
		throw std::out_of_range("out of range");

	T top = _arr.front();

	_arr.front() = _arr.back();
	_arr.pop_back();

	SiftDown(0);

	return top;
}

template<typename T, typename Comparison>
void TemplateHeap<T, Comparison>::SiftUp(int ind)
{
	while (ind != 0 && _cmp(_arr[ind], _arr[Parent(ind)]))
	{
		std::swap(_arr[ind], _arr[Parent(ind)]);
		ind = Parent(ind);
	}
}

template<typename T, typename Comparison>
void TemplateHeap<T, Comparison>::SiftDown(int ind)
{
	int prioritized = ind;
	int left = Left(ind);
	int right = Right(ind);

	if (left < Size() && _cmp(_arr[left], _arr[prioritized]))
		prioritized = left;

	if (right < Size() && _cmp(_arr[right], _arr[prioritized]))
		prioritized = right;

	if (prioritized != ind)
	{
		std::swap(_arr[prioritized], _arr[ind]);
		SiftDown(prioritized);
	}
}