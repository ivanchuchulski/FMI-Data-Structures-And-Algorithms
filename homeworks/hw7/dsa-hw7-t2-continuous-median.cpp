#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iomanip>

using std::cout;
using std::cin;

class MaxHeap
{

private:
	std::vector<int> arr_max;

public:
	MaxHeap() : arr_max()
	{}

	~MaxHeap()
	{}

	bool Empty() const { return arr_max.empty(); }

	int Size() const { return arr_max.size(); }

	int Parent(int ind) { return (ind - 1) / 2; }
	int Left(int ind) { return 2 * ind + 1; }
	int Right(int ind) { return 2 * ind + 2; }

	void SiftUp(int ind);            //max heapify up,    O(log(n))
	void SiftDown(int ind);            //max heapify down, O(log(n))

	void Insert(int value);            //O(log(n))

	//only peek the max value without removing it
	int GetMax() const;

	//get the max value by removing it, O(log(n))
	int ExtractMax();
};


void MaxHeap::SiftUp(int ind)
{
	while (ind != 0 && arr_max[Parent(ind)] < arr_max[ind])
	{
		std::swap(arr_max[Parent(ind)], arr_max[ind]);
		ind = Parent(ind);
	}
}

void MaxHeap::SiftDown(int ind)
{
	int largest = ind;
	int left = Left(ind);
	int right = Right(ind);

	if (left < Size() && arr_max[left] > arr_max[largest])
		largest = left;

	if (right < Size() && arr_max[right] > arr_max[largest])
		largest = right;

	if (largest != ind)
	{
		std::swap(arr_max[largest], arr_max[ind]);
		SiftDown(largest);
	}
}

void MaxHeap::Insert(int value)
{
	arr_max.push_back(value);

	SiftUp(Size() - 1);
}

int MaxHeap::GetMax() const
{
	if (Empty())
		throw std::out_of_range("out of range");

	return arr_max[0];
}

int MaxHeap::ExtractMax()
{
	if (Empty())
		throw std::out_of_range("out of range");

	int maximal = arr_max[0];

	arr_max[0] = arr_max.back();
	arr_max.pop_back();

	SiftDown(0);

	return maximal;
}

class MinHeap
{
private:
	std::vector<int> arr_min;

public:
	MinHeap() : arr_min()
	{}

	~MinHeap()
	{}


	bool Empty() const { return arr_min.empty(); }

	int Size() const { return arr_min.size(); }

	int Parent(int ind) { return (ind - 1) / 2; }
	int Left(int ind) { return 2 * ind + 1; }
	int Right(int ind) { return 2 * ind + 2; }

	void SiftUp(int ind);            //heapify up,    O(log(n))
	void SiftDown(int ind);            //heapify down, O(log(n))

	void Insert(int value);            //O(log(n))

	int GetMin() const;
	int ExtractMin();
};


void MinHeap::SiftUp(int ind)
{
	while (ind != 0 && arr_min[Parent(ind)] > arr_min[ind])
	{
		std::swap(arr_min[Parent(ind)], arr_min[ind]);
		ind = Parent(ind);
	}
}

void MinHeap::SiftDown(int ind)
{
	int smallest = ind;
	int left = Left(ind);
	int right = Right(ind);

	if (left < Size() && arr_min[left] < arr_min[smallest])
		smallest = left;

	if (right < Size() && arr_min[right] < arr_min[smallest])
		smallest = right;

	if (smallest != ind)
	{
		std::swap(arr_min[smallest], arr_min[ind]);
		SiftDown(smallest);
	}
}

void MinHeap::Insert(int value)
{
	arr_min.push_back(value);

	SiftUp(Size() - 1);
}

int MinHeap::GetMin() const
{
	if (Empty())
		throw std::out_of_range("out of range");

	return arr_min[0];
}

inline int MinHeap::ExtractMin()
{
	if (Empty())
		throw std::out_of_range("out of range");

	int minimal = arr_min[0];

	arr_min[0] = arr_min.back();
	arr_min.pop_back();

	SiftDown(0);

	return minimal;
}


void AdjustHeaps(MaxHeap& lower, MinHeap& upper)
{
	if (lower.Size() == upper.Size())
		return;		// no need to reballance

	if (lower.Size() > upper.Size() + 1)
		upper.Insert(lower.ExtractMax());

	else if (upper.Size() > lower.Size() + 1)
		lower.Insert(upper.ExtractMin());

	else
		return;
}

double ComputeMedian(MaxHeap& lower, MinHeap& upper)
{
	if (lower.Size() == upper.Size())
		return (static_cast<double>(lower.GetMax()) + static_cast<double>(upper.GetMin())) / 2;

	else if (lower.Size() > upper.Size())
		return lower.GetMax();

	else
		return upper.GetMin();
}


int main() {

	int N;
	int entry;

	MaxHeap lower_citizens;
	MinHeap upper_citizens;

	cin >> N;

	cout << std::fixed << std::setprecision(1);

	for (int i = 0; i < N; i++)
	{
		cin >> entry;

		if (lower_citizens.Empty() || entry < lower_citizens.GetMax())
			lower_citizens.Insert(entry);

		else
			upper_citizens.Insert(entry);

		AdjustHeaps(lower_citizens, upper_citizens);

		cout << ComputeMedian(lower_citizens, upper_citizens) << '\n';
	}


	
	std:system("pause");
	return 0;
}