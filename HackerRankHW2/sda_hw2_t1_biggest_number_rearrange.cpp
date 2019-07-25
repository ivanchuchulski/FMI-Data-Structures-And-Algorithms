#include <iostream>
#include <cstdlib>
#include <utility>
#include <string>
#include <cstring>

int Power(int base, int power)
{
	if (power == 0)
		return 1;

	int result = 1;

	for (int i = 1; i <= power; i++)
		result *= base;

	return result;
}

int GetDigitCount(int number)
{
	if (number == 0)
		return 1;

	int digit_count = 0;

	while (number != 0)
	{
		digit_count++;
		number /= 10;
	}

	return digit_count;
}

void PrintArr(int* arr, int N)
{
	for (int i = 0; i < N; i++)
		std::cout << arr[i] << ' ';

	std::cout << "\n";
}

/*number digits := 1st 2nd 3rd 4th
					6   4   2   7        */
int KDigit(int num, int digit_count, int k)
{
	if (k < 1)
		return -1;

	if (digit_count < k)
		return -1;

	return ((num / Power(10, digit_count - k)) % 10);
}

bool IsGreater(int a, int b)
{
	int a_len = GetDigitCount(a);
	int b_len = GetDigitCount(b);

	int a_first_digit = KDigit(a, a_len, 1);
	int b_first_digit = KDigit(b, b_len, 1);

	if (a_first_digit > b_first_digit)
		return true;

	else if (a_first_digit == b_first_digit)
	{
		if (a_len == b_len)
			return a > b;

		else
		{
			std::string s1 = std::to_string(a).append(std::to_string(b));
			std::string s2 = std::to_string(b).append(std::to_string(a));

			//return true if s1 is after than s2, which means it is smaller number
			if (s1 > s2)
				return true;
			else
				return false;
		}
	}

	else
		return false;
}


void SelectionSort(int* arr, int N)
{
	for (int i = 0; i < N - 1; i++)
	{
		int max_indx = i;
		for (int j = i + 1; j < N; j++)
		{
			//if arr[j] is greater than arr[max_indx] 
			if (IsGreater(arr[j], arr[max_indx]))
				max_indx = j;
		}

		if (max_indx != i)
			std::swap(arr[i], arr[max_indx]);
	}
}

int main() {

	int N;
	int* arr = nullptr;

	std::cin >> N;

	if (N == 0)
	{
		std::cout << "0\n";
		return 0;
	}

	arr = new int[N];

	for (int i = 0; i < N; i++)
		std::cin >> arr[i];

	//check if all elemts are equal
	int first_element = arr[0];
	bool all_equal = true;

	for (int i = 1; i < N; i++)
	{
		if (arr[i] != first_element)
		{
			all_equal = false;
			break;
		}
	}

	if (all_equal)
	{
		if (arr[0] == 0)
			std::cout << "0\n";
		else
			for (int i = 0; i < N; i++)
			{
				std::cout << arr[i];
			}

		return 0;
	}

	//  PrintArr(arr, N);

	SelectionSort(arr, N);

	//  PrintArr(arr, N);

	  //print the number
	for (int i = 0; i < N; i++)
		std::cout << arr[i];

	std::cout << '\n';

	//free memory
	delete[] arr;

	std::system("pause");
	return 0;
}