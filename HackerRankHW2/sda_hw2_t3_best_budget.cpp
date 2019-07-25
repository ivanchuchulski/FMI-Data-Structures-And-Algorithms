#include <iostream>
#include <cstdlib>



int partition(int* arr, int low, int high)
{
	int pivot = arr[high];
	int i = low;

	for (int j = low; j < high; j++)
	{
		if (arr[j] <= pivot)
		{
			std::swap(arr[i], arr[j]);
			i++;
		}
	}

	std::swap(arr[i], arr[high]);

	return i;
}

void QuickSort(int* arr, int low, int high)
{
	if (low < high)
	{
		int part_indx = partition(arr, low, high);

		QuickSort(arr, low, part_indx - 1);
		QuickSort(arr, part_indx + 1, high);
	}
}

void Print(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		std::cout << arr[i] << ' ';
	
	std::cout << '\n';
}

int main() {

	int N;
	int money;
	int* items = nullptr;

	std::cin >> N >> money;

	items = new int[N];

	for (int i = 0; i < N; i++)
		std::cin >> items[i];

	Print(items, N);

	QuickSort(items, 0, N - 1);

	Print(items, N);

	int bought_count = 0;
	for (size_t i = 0; i < N; i++)
	{
		money -= items[i];

		if (money <= 0)
			break;
		else
			bought_count++;
	}


	std::cout << bought_count;

	//free memory
	delete[] items;

	std::system("pause");
	return 0;
}