#include <iostream>
#include <queue>

using std::cout;
using std::cin;
using int64 = unsigned long long;


inline int64 AbsoluteValue(long long num)
{
	return num > 0 ? num : -num;
}


/*
	202



*/

//function to check all the magic numbers above 9
bool IsMagic(int64 num, const int& magic_difference)
{
	int last_digit = num % 10;

	num /= 10;

	while (num != 0)
	{
		int current = num % 10;

		if (AbsoluteValue(current - last_digit) != magic_difference)
			return false;

		last_digit = current;
		num /= 10;
	}

	//if loop didnt break, the number is magic
	return true;
}

int main () {

	std::ios_base::sync_with_stdio(false);	//making i/o streams faster by unsyncing them with C ones

	const size_t magic_difference = 2;
	int64 N;
	cin >> N;

	if (N <= 9)		//we consider all numbers from 1 to 9 to be magic
	{
		for(size_t i = 0; i < N; i++)
			cout << i + 1 << ' ';

		std::system("pause");
		return 0;
	}


	//print all basic magic numbers
	for (size_t i = 0; i < 9; i++)
		cout << i + 1 << ' ';

	for (int64 number = 10; number <= N; number++)
	{
		if (IsMagic(number, magic_difference))
			cout << number << ' ';
		else
			continue;
	}


	std::system("pause");
	return 0;
}