#pragma once
#include <array>
#include <utility>
#include <functional>
#include <cstdint>



void merge(int* arr, size_t first, size_t middle, size_t last)
{
	size_t out_indx = 0;
	int elements_count = last - first + 1;

	size_t left = first;
	size_t right = middle + 1;

	int* output = new int[elements_count] {0};

	//merging the the sorted subarrays
	while (left <= middle && right <= last)
	{
		if (arr[left] < arr[right])
			output[out_indx++] = arr[left++];
		else
			output[out_indx++] = arr[right++];
	}

	//add in remaining elements
	while (left <= middle)
		output[out_indx++] = arr[left++];

	while (right <= last)
		output[out_indx++] = arr[right++];

	//put the elements in the array
	for (int i = 0; i < elements_count; i++)
		arr[first++] = output[i];

	delete[] output;
}


//	call in MergeSort merge1(arr, left, middle, middle + 1, right);
void merge_faster(int* arr, int first, int middle, int last)
{
	size_t element_count = last - first + 1;
	int* output = new int[element_count];

	size_t left = first;
	size_t right = middle + 1;

	for (size_t i = 0; i < element_count; i++)
	{
		//adding the remaining elements
		if (left > middle)
			output[i] = arr[right++];
		else if (right > last)
			output[i] = arr[left++];

		//merging the subarrays
		else if (arr[left] <= arr[right])		//comparison '<'
			output[i] = arr[left++];
		else
			output[i] = arr[right++];
	}

	for (int i = 0; i < element_count; i++)
		arr[first++] = output[i];

	//free memory
	delete[] output;
}

//_> first = 0, last = size - 1
void MergeSort(int* arr, int first, int last)
{
	if (first < last)
	{
		int middle = (first + last) / 2;	//	or first + (last - first) / 2

		MergeSort(arr, first, middle);
		MergeSort(arr, middle + 1, last);

		merge_faster(arr, first, middle, last);
	//	merge(arr, left, middle, right);
	}

	else
		return;
}

template<size_t size>
int partition(std::array<int, size>& arr, int first, int last)
{
	int pivot = arr[last];
	int border = first;

	for (int i = first; i < last; i++)
	{
		if (arr[i] <= pivot)
		{
			std::swap(arr[border], arr[i]);
			border++;
		}
	}

	std::swap(arr[border], arr[last]);

	return border;
}

template<size_t size>
void QuickSort(std::array<int, size>& arr, int first, int last)
{
	if (first < last)
	{
		int pivot_indx = partition(arr, first, last);

		QuickSort(arr, first, pivot_indx - 1);
		QuickSort(arr, pivot_indx + 1, last);
	}
}









