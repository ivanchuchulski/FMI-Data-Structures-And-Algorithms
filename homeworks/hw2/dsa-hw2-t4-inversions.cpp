#include <iostream>
#include <cstdlib>
#include <vector>

using std::cout;
using std::cin;
using int64 = long long int;


/*      left part begin := first			left part end := middle
		right part begin := middle + 1		right part end := last
*/
int64 merging(int* arr, int first, int middle, int last)
{
	int left = first;
	int right = middle + 1;
	int element_count = last - first + 1;
	std::vector<int> buffer(element_count, 0);

	int64 inversions = 0;

	for (size_t i = 0; i < element_count; i++)
	{
		if (left > middle)
			buffer[i] = arr[right++];
		else if (right > last)
			buffer[i] = arr[left++];

		else if (arr[left] <= arr[right])
			buffer[i] = arr[left++];
		else
		{
			buffer[i] = arr[right++];
			inversions += middle - left + 1;
		}
	}

	//copying in the main array
	for (int i = 0; i < element_count; i++)
		arr[first++] = buffer[i];

	return inversions;
}

int64 MergeSort(int* arr, int first, int last)
{
	int64 inversions = 0;

	if (first < last)
	{
		int middle = first + (last - first) / 2;

		inversions = MergeSort(arr, first, middle);
		inversions += MergeSort(arr, middle + 1, last);

		inversions += merging(arr, first, middle, last);
	}

	return inversions;
}

int main()
{
	int queries;
	cin >> queries;

	for (int quer = 0; quer < queries; quer++)
	{
		int N;
		int* heights = nullptr;

		cin >> N;
		heights = new int[N] {0};

		for (int j = 0; j < N; j++)
			cin >> heights[j];

		cout << MergeSort(heights, 0, N - 1) << '\n';


		delete[] heights;
	}

	std::system("pause");
	return 0;
}