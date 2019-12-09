#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>

using int64 = long long;

void PrintArr(int64* arr, int N)
{
	for (int i = 0; i < N; i++)
		std::cout << arr[i] << ' ';

	std::cout << '\n';
}

int64 DryBinary(std::vector<int64>& clothes, int size, unsigned long long dryer)
{
	unsigned first = 0, last = size - 1, middle;

	while (first <= last)
	{
		middle = (first + last) / 2;

		if (clothes[middle] == dryer)
			return middle;

		else if (dryer < clothes[middle])
		{
			if (first == last)
				return middle;
			else
				last = middle - 1;
		}

		else
		{
			if (first == last)
				return middle;
			else
				first = middle + 1;
		}
	}

	return middle;
}


//clothes are dry if all of their dry time is <= 0 
bool AllDry(const int64* clothes, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (clothes[i] > 0)
			return false;
	}
	return true;
}

int64 DryClothes_brute(int64* clothes, int size, const int64 dryer, const int wind)
{
	int64 time = 0;
	do
	{
		int apply_dryer_to = size - 1;

		for (int i = 0; i < size; i++)
		{
			if (i == apply_dryer_to)
				clothes[i] -= dryer;
			else
				clothes[i] -= wind;
		}

		//sort the elements by insertion sort
		for (int i = 1; i < size; i++)
		{
			for (int indx = i; indx > 0 && clothes[indx] < clothes[indx - 1]; indx--)
			{
				std::swap(clothes[indx], clothes[indx - 1]);
			}
		}
		
		time++;

	} while (!AllDry(clothes, size));

	return time;
}

bool CanDryOut(int64* clothes, int size, const int64 dryer, const int wind, const int64 potential_time)
{
	//clothes only on the wind
//for (int i = 0; i < size; i++)
//{
//	if (clothes[i] < time_on_wind)
//		clothes[i] = 0;
//	else
//		clothes[i] -= time_on_wind;
//}
//
////apply the dryer
//while (clothes[size - 1] > 0)
//{
//	time++;
//	clothes[size - 1] -= dryer;
//}

	int64 time_needed = 0;
	std::vector<int64> copy(size, 0);

	for (int i = 0; i < size; i++)
		copy[i] = clothes[i];

	for (int i = 0; i < copy.size(); i++)
	{
		if (copy[i] < potential_time)
			copy[i] = 0;
		else
			copy[i] -= potential_time * wind;
	}

	for (int i = 0; i < copy.size(); i++)
	{
		if (copy[i] > 0)
		{
			int t = 0;
			if (copy[i] / dryer > 0)
				time_needed += copy[i] / dryer;
			else
				time_needed += copy[i] % dryer;
		}
		else
			continue;

	}

	return time_needed <= potential_time;
}

int64 DryClothes(int64* clothes, int size, const int64 dryer, const int wind)
{
	int64 optimal_time = 0;
	int64 max_time = clothes[size - 1];

	//std::vector<int64> possibilities(max_time, 0);

	bool* possibilities = new bool[max_time] {0};

	int64 first = 0, last = max_time - 1;

	while (first <= last)
	{
		int64 middle = first + (last - first) / 2;

		if (CanDryOut(clothes, size, dryer, wind, middle))
		{
			possibilities[middle] = 1;
			last = middle - 1;			//maybe search for faster time
		}
		else
			first = middle + 1;
	}


	for (int i = 0; i < max_time; i++)
	{
		if (possibilities[i] > 0)
		{
			optimal_time = i;
			break;
		}
			
	}

	//freeing memory
	delete[] possibilities;

	return optimal_time;
}

int main() {

	int N{};
	int64 dryer_power{};
	const int wind_power = 1;
	int64* clothes{ nullptr };

	std::cin >> N >> dryer_power;

	clothes = new int64[N] {0};
	for (int i = 0; i < N; i++)
		std::cin >> clothes[i];


	std::sort(clothes, clothes + N);		//sorting in ascending order
//	PrintArr(clothes, N);

//	std::cout << DryClothes_brute(clothes, N, dryer_power, wind_power) << '\n';
	std::cout << DryClothes(clothes, N, dryer_power, wind_power) << '\n';

	//freeing memory
	delete[] clothes;

	std::system("pause");
	return 0;
}