#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <limits>
#include <vector>

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

Positions FindNumber(unsigned int* sorted, unsigned size, unsigned to_find)
{
	int first = 0;
	int last = size - 1;
	int middle;

	bool found = false;
	int occurrence;

	while (first <= last)
	{
		middle = (first + last) / 2;

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
		int over = occurrence;
		for (int i = occurrence + 1; i < size; i++)
		{
			if (sorted[i] == to_find)
				over = i;
			else
				break;
		}

		int under = occurrence;
		for (int i = occurrence - 1; i >= 0; i--)
		{
			if (sorted[i] == to_find)
				under = i;
			else
				break;
		}
		
		//the task says to increment the indices with 1 !!!
		//std::cout << under + 1 << ' ' << over + 1;
		return Positions(under + 1, over + 1);
	}

}

void PrintArr(unsigned int* arr, unsigned N)
{
	for (unsigned i = 0; i < N; i++)
		std::cout << arr[i] << ' ';

	std::cout << '\n';
}

int main() {

	unsigned N {0};
	unsigned int* numbers{ nullptr };

	unsigned Q {0};
	unsigned int* queries{ nullptr };

	//std::cout << std::numeric_limits<unsigned int>::max() << '\n';

	std::cin >> N;
	numbers = new unsigned int[N] {0};
	for (unsigned i = 0; i < N; i++)
		std::cin >> numbers[i];


	std::cin >> Q;
	queries = new unsigned int[Q];
	for (unsigned i = 0; i < Q; i++)
		std::cin >> queries[i];

	//sorting in ascending order
	std::sort(numbers, numbers + N);

	//PrintArr(numbers, N);

	std::vector<Positions> appears;

	for (unsigned i = 0; i < Q; i++)
		appears.emplace_back(FindNumber(numbers, N, queries[i]));

	for (auto& p : appears)
		std::cout << p.m_first << ' ' << p.m_last << '\n';

	std::system("pause");
	return 0;
}