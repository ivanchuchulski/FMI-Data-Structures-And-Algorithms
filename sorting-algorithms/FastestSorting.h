#pragma once
#include <cstdint>

void CountingSort_Ch(char* arr, int size)
{
	char* copy = new char[size];
	int counts[256] = {0};

	for (int i = 0; i < size; i++)
		copy[i] = arr[i];

	//count how often each item appears
	for (int i = 0; i < size; i++)
		++counts[arr[i]];

	for (int i = 1; i <= 255; i++)
		counts[i] += counts[i - 1];

	for (int i = size - 1; i >= 0; i--)
	{
		arr[counts[copy[i] - 1]] = copy[i];
		counts[copy[i]] -= 1;
	}

	delete[] copy;
}


void CountingSort(const char* input, int size, char* result)
{
	size_t counts[256] = { 0 };

	for (int i = 0; i < size; i++)
		++counts[input[i]];

	for (int i = 1; i <= 255; i++)
		counts[i] += counts[i - 1];

	for (int i = size - 1; i >= 0; i--)
	{
		result[counts[input[i]] - 1] = input[i];
		--counts[input[i]];
	}
}








