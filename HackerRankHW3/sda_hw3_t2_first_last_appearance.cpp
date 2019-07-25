#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <limits>
#include <vector>

using int64 = long long;

class Positions
{
public:
	int m_first;
	int m_last;

	Positions() = default;
	Positions(const Positions& other) = default;
	~Positions() = default;
	Positions& operator=(const Positions& other) = default;

	Positions(int first, int last)
		: m_first(first), m_last(last)
	{}
};

Positions FindAppearances(int64* sorted, int size, unsigned int to_find)
{
	int first = 0;
	int last = size - 1;

	bool found = false;
	int occurrence;

	while (first <= last)
	{
		int middle = first + (last - first) / 2;

		if (sorted[middle] == to_find)
		{
			occurrence = middle;
			found = true;
			break;
		}

		else if (to_find < sorted[middle])
			last = middle - 1;

		else
			first = middle + 1;
	}

	if (!found)
	{
		//std::cout << "-1 -1\n";
		return Positions(-1, -1);
	}

	else
	{
		//searching for number after the first appearance found
		int over = occurrence;
		int upper_first = occurrence + 1;

		while (upper_first <= last)
		{
			int upper_mid = upper_first + (last - upper_first) / 2;

			if (sorted[upper_mid] == to_find)
			{
				over = upper_mid;
				upper_first = upper_mid + 1;	//continue to search for potential appear
			}
			else
				last = upper_mid - 1;	//we overestimated, go lower and search
		}

		int under = occurrence;
		int lower_last = occurrence - 1;

		while (first <= lower_last)
		{
			int lower_mid = first + (lower_last - first) / 2;

			if (sorted[lower_mid] == to_find)
			{
				under = lower_mid;
				lower_last = lower_mid - 1;
			}
			else
				first = lower_mid + 1;
		}


		//the task says to increment the indices with 1 !!!
		//std::cout << under + 1 << ' ' << over + 1;
		return Positions(under + 1, over + 1);
	}

}

void PrintArr(int64* arr, int N)
{
	for (int i = 0; i < N; i++)
		std::cout << arr[i] << ' ';

	std::cout << '\n';
}

int main() {


	int N {0};
	int64* numbers{ nullptr };

	int Q {0};
	int64* queries{ nullptr };

	//std::cout << std::numeric_limits<unsigned int>::max() << '\n';

	std::cin >> N;
	numbers = new int64[N] {0};
	for (int i = 0; i < N; i++)
		std::cin >> numbers[i];


	std::cin >> Q;
	queries = new int64[Q];
	for (int i = 0; i < Q; i++)
		std::cin >> queries[i];

	//sorting in ascending order
	std::sort(numbers, numbers + N);

	//PrintArr(numbers, N);

	std::vector<Positions> appears;
	appears.reserve(Q);

	//overall complexity O(Q*log(N))
	for (int i = 0; i < Q; i++)
		appears.emplace_back(FindAppearances(numbers, N, queries[i]));

	for (auto& p : appears)
		std::cout << p.m_first << ' ' << p.m_last << '\n';

	std::system("pause");
	return 0;
}