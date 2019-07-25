#include <iostream>
#include <cstdlib>
#include <numeric>			//std::accumulate
#include <algorithm>		//std::swap
#include <vector>


bool ValidateInput(int n, int k)
{
	if (n < 1 || n > 100000)
		return false;

	else if (k < 2 || k > 100)
		return false;

	else
		return true;
}
bool ValidateArr(const int* a, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (a[i] < 1 || a[i] > 10000)
			return false;
	}

	return true;
}

int GetSum(int n, int k, const int* products)
{
	std::vector<int> vec;

	for (int i = 0; i < n; i++)
		vec.push_back(products[i]);

	for (int i = n - 1; i - k + 1 >= 0; i -= k)
		vec[i - k + 1] = 0;


	return std::accumulate(vec.begin(), vec.end(), 0);

}

int main() {
	int n, k;
	int* ai = nullptr;

	std::cin >> n >> k;

	bool valid_input = ValidateInput(n, k);

	if (!valid_input)
	{
		std::cout << 0 << '\n';
		return 0;
	}

	ai = new int[n];

	for (int i = 0; i < n; i++)
		std::cin >> ai[i];

	bool valid_arr = ValidateArr(ai, n);

	if (!valid_arr)
	{
		std::cout << 0 << '\n';
		return 0;
	}

	std::sort(ai, ai + n);

	if (k > n)
	{
		int total = std::accumulate(ai, ai + n, 0);
		std::cout << total << '\n';

		std::system("pause");
		return 0;
	}

	std::cout << GetSum(n, k, ai) << '\n';


	//free dynamic memory
	delete[] ai;

	std::system("pause");
	return 0;
}