#pragma once
#include <cmath>
#include <algorithm>


int LinearSearch(int* arr, int size, int to_find)
{
	for (int i = 0; i < size; i++)
		if (arr[i] == to_find)
			return i;

	return -1;
}


int BinaryRecursive(int* sorted, int first, int last, int to_find)
{
	if (first > last)	//recursion bottom
		return -1;

	int middle = first + (last - first) / 2;

	if (sorted[middle] == to_find)
		return middle;
	else if (to_find < sorted[middle])
		return BinaryRecursive(sorted, first, middle - 1, to_find);
	else
		return BinaryRecursive(sorted, middle + 1, last, to_find);
}

int BinaryIterative(int* sorted, int size, int to_find)
{
	int first = 0, last = size - 1;

	while (first <= last)
	{
		int middle = first + (last - first) / 2;

		if (sorted[middle] == to_find)
			return middle;
		else if (to_find < sorted[middle])
			last = middle - 1;
		else
			first = middle + 1;
	}

	return -1;		//if not found
}

int TernarySearch(int* sorted, int first, int last, int to_find)
{
	if (first > last)
		return -1;

	int mid1 = (2 * first + last) / 3;
	int mid2 = (first + 2 * last) / 3;

	if (sorted[mid1] == to_find)
		return mid1;
	else if (sorted[mid2] == to_find)
		return mid2;

	if (to_find < sorted[mid1])
		return TernarySearch(sorted, first, mid1 - 1, to_find);
	else if (to_find < sorted[mid2])
		return TernarySearch(sorted, mid1 + 1, mid2 - 1, to_find);
	else
		return TernarySearch(sorted, mid2 + 1, last, to_find);
}


bool JumpSearch(int* arr, int size, int to_find)
{
	int step = (int)std::sqrt(size);
	int prev = 0;
	int next = prev + step;

	while (arr[std::min(next, size) - 1] < to_find)
	{
		prev = next;
		next += step;

		if (prev >= size)
			return false;
	}

	while (arr[prev] < to_find)
	{
		prev++;
		if (prev == std::min(step, size))
			return false;
	}

	if (arr[prev] == to_find)
		return true;
	else
		return false;
}








 