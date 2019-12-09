#include <iostream>
#include <cstdlib>

#include "SlowSorting.h"
#include "FastSorting.h"
#include "FastestSorting.h"


void Print(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		std::cout << arr[i] << ' ';

	std::cout << '\n';
}

template<size_t size>
void PrintArray(std::array<int, size>& arr)
{
	for (int i = 0; i < arr.size(); i++)
		std::cout << arr[i] << ' ';

	std::cout << '\n';
}

void PrintUInts(char* arr, size_t size)
{
	for (size_t i = 0; i < size; i++)
		std::cout << arr[i] << ' ';

	std::cout << '\n';
}

int main() {


	{
		int arr[] = { 11, 9, 9, 5, 3 };
		int arr2[] = { 9, 11, 9, 5 };
		std::array<int, 10> numbers = { -300, 100, -200, 400, -500, 300, -100, 500, -400, 100 };

	//	Print(arr, 5);
	//	Print(arr2, 4);
		PrintArray(numbers);

	//	BubbleSort(arr1, arr1.size());
	//	SelectionSort(arr, arr.size());
	//	InsertionSort_Ch(arr, arr.size());
	//	InsertionSort(arr2, 4);


	//	MergeSort(arr, 0, 4);
	//	QuickSort(numbers, 0, numbers.size() - 1);

	//	Print(arr, 5);
	//	Print(arr2, 4);
		PrintArray(numbers);


		char a[6] = { 6, 3, 2, 3, 4, 1 };
		char b[6]{ 0 };

		PrintUInts(a, 6);

		CountingSort(a, 6, b);

		PrintUInts(b, 6);

	}

	std::system("pause");
	return 0;
}