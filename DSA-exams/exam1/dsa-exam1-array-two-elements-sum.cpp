#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cstddef>  //for size_t
#include <string>

void PrintArr(const int* arr, size_t size)
{
	for (size_t i = 0; i < size; i++)
		std::cout << arr[i] << ' ';

	std::cout << '\n';
}

bool FindEqualWeights(const int* arr, size_t size)
{
	for (size_t i = 0; i < size - 2; i++)
	{
		for (size_t j = i + 1; j < size; j++)
		{
			for (size_t k = j + 1; k < size; k++)
			{
				if (arr[i] == arr[j] + arr[k])
					return true;
			}
		}
	}

	return false;

}

std::string Proposed1(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			for (int k = 0; k < size; k++)
				if (arr[i] + arr[j] == arr[k] && i != j && j != k && i != k)
					return std::string("true");


	return std::string("false");
}

std::string Proposed2(int* arr, int size)
{
	const int count_size = (size * (size - 1)) / 2;
	int* count = new int[count_size];

	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
			count[arr[i] + arr[j]] = count[arr[i] + arr[j]] + 1;
	}

	for (int i = 0; i < size; i++)
		if (count[arr[i]] > 0)
			return std::string("true");

	return std::string("false");
}

std::string Solut(int* arr, int size)
{
	//creating a vector and nulling it out
	std::vector<int> count;
	const int sums_count = (size * (size - 1)) / 2;
	count.reserve(sums_count);

	for (int i = 0; i < size; i++)
		for (int j = i + 1; j < size; j++)
			count.emplace_back(arr[i] + arr[j]);

	for (int i = 0; i < size; i++)
		for (int j = 0; j < count.size(); j++)
			if (arr[i] == count[j])
				return std::string("true");

	return std::string("false");
}

int main() {

	int n;
	std::cin >> n;

	if (n < 3 || n > 10000)
		return 0;

	int* arr = new int[n];

	for (size_t i = 0; i < n; i++)
		std::cin >> arr[i];

	//   PrintArr(arr, n);

	//std::sort(arr, arr + n, [](int a, int b) -> bool {return a > b; });

	//    PrintArr(arr, n);

	//std::cout << FindEqualWeights(arr, n);

	std::cout << Solut(arr, n) << '\n';



	//free memory
	delete[] arr;


	std::system("pause");
	return 0;
}
