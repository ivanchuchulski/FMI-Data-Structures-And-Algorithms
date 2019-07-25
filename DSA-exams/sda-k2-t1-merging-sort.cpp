#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void merging(int* arr, int first, int middle, int last)
{
	int elem_count = last - first + 1;
	int* buffer = new int[elem_count];

	int left = first;
	int right = middle + 1;

	for (int i = 0; i < elem_count; i++)
	{
		if (left > middle)
			buffer[i] = arr[right++];
		else if (right > last)
			buffer[i] = arr[left++];

		else if (arr[left] <= arr[right])
			buffer[i] = arr[left++];
		else
			buffer[i] = arr[right++];
	}

	int f = first;
	for (int i = 0; i < elem_count; i++)
	{
		arr[first++] = buffer[i];
		cout << buffer[i] << ' ';
	}

	//for (int i = f; i < elem_count; i++)
	//	cout << arr[i] << ' ';

	delete[] buffer;
}

void MergeSort(int* arr, int first, int last)
{
	int middle;

	if (first < last)
	{
		middle = (first + last) / 2;

		MergeSort(arr, first, middle);
		MergeSort(arr, middle + 1, last);

		merging(arr, first, middle, last);
	}

	if (first == last)
		cout << arr[first] << ' ';
}



int main() {
	int N;
	int* arr{ nullptr };

	cin >> N;

	arr = new int[N];

	for (int i = 0; i < N; i++)
		cin >> arr[i];


	MergeSort(arr, 0, N - 1);

	//for (int i = 0; i < N; i++)
	//   cout << arr[i] << ' ';


	delete[] arr;
 	
	std::system("pause");
	return 0;
}
