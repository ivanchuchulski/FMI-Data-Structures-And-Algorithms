#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct Couple
{
	int upper_sum;
	int lower_sum;
};


int main() {

	ios_base::sync_with_stdio(false);

	int tests_num;

	cin >> tests_num;

	for (int i = 0; i < tests_num; i++)
	{
		size_t arr_size;
		vector<int> numbers;

		vector<int> lower;	//negative numbers and 0
		vector<int> upper;	//positive numbers

		cin >> arr_size;

		numbers.resize(arr_size, 0);
		for (size_t j = 0; j < arr_size; j++)
			cin >> numbers[j];

		sort(numbers.begin(), numbers.end());		//sorting in ascending order

		for (int num : numbers)
		{
			if (num <= 0)
				lower.push_back(num);
			else
				upper.push_back(num);
		}

		Couple sums{ 0, 0 };

		int how_many_left = upper.size();


		for (size_t i = 0; i < upper.size(); i++)
		{
			if (upper[i] == 1)
			{
				sums.upper_sum += upper[i];
				how_many_left--;
			}
			else
			{
				if (how_many_left % 2 != 0)
				{
					sums.upper_sum += upper[i];
					how_many_left--;
				}
				else
				{
					if (how_many_left != 0)
					{
						sums.upper_sum += upper[i] * upper[i + 1];
						how_many_left -= 2;
						i++;
					}
					else
					{
						sums.upper_sum += upper[i];
						how_many_left--;
					}


				}
			}
		}

		how_many_left = lower.size();
		for (int j = lower.size() - 1; j >= 0; j--)
		{
			if (how_many_left % 2 == 0)
			{
				sums.lower_sum += lower[j] * lower[j - 1];
				how_many_left -= 2;
				j--;
			}
			else
			{
				sums.lower_sum += lower[j];
				how_many_left--;
			}
		}

		//check only with summation, will be more if only 1s in the array
		sums.upper_sum = max(sums.upper_sum, accumulate(upper.begin(), upper.end(), 0));

		int overall_sum = max(sums.upper_sum+ sums.lower_sum,accumulate(numbers.begin(), numbers.end(), 0));

		cout << overall_sum << '\n';
	}


	system("pause");
	return 0;
}

