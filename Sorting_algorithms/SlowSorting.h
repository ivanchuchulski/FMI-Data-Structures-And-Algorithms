#pragma once
#include <array>

template<size_t size>
void BubbleSort(std::array<int, size>& arr, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		bool is_sorted = true;
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (arr[j + 1] < arr[j])
			{
				is_sorted = false;
				std::swap(arr[j + 1], arr[j]);
			}
		}

		if (is_sorted)
			break;
	}
}

template<size_t size>
void SelectionSort(std::array<int, size>& arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		size_t min_indx = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[min_indx])
				min_indx = j;
		}

		if (min_indx != i)
			std::swap(arr[i], arr[min_indx]);
	}
}

template<size_t size>
void InsertionSort_Ch(std::array<int, size>& arr, int size)
{
	for (int i = 1; i < size; i++)
	{
		int key = arr[i];
		int j = i - 1;

		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
		}

		arr[j + 1] = key;
	}
}

void InsertionSort(int* arr, size_t size)
{
	for (int i = 1; i < size; i++)
	{
		for (int indx = i; indx > 0 && arr[indx] < arr[indx - 1]; indx--)
		{
				std::swap(arr[indx], arr[indx - 1]);
		}
	}

}