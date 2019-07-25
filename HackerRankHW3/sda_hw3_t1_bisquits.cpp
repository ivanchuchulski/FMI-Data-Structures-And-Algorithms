#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>

namespace integers 
{
	using uint64 = unsigned long long;
	using int64 = long long;
	using uint32 = unsigned int;
	using int32 = int;
}




class BiscuitBox
{
public:
	integers::int64 m_sections;
	integers::int64 m_sum;

	BiscuitBox() = default;
	BiscuitBox(const BiscuitBox& other) = default;
	~BiscuitBox() = default;
	BiscuitBox& operator=(const BiscuitBox& other) = default;

	BiscuitBox(integers::int64 N)
		: m_sections(N), m_sum((N*(N + 1)) / 2)
	{}

	friend std::ostream& operator<<(std::ostream& outS, const BiscuitBox& b)
	{
		outS<< "N : " << b.m_sections << ", sum : " << b.m_sum << '\n';
		return outS;
	}

	bool AllEaten() const
	{
		return m_sum <= 0;
	}

};


int EatFastest(BiscuitBox& box)
{
	int days = 0;
	int counter = 1;
	int daily_dose = 0;
	
	int first = 0, last = box.m_sections - 1;

	while (first <= last)
	{
		int middle = first + (last - first) / 2;

		if (middle % 2 == 0)
			daily_dose = (middle + 1) / counter;

		else
			daily_dose = (middle / counter) + 1;
			
		box.m_sum -= (box.m_sections - middle) * daily_dose;


		first = middle + 1;
		counter++;
		days++;
	}

	std::cout << "sum " << box.m_sum << '\n';

	return days;
}

int Eat(BiscuitBox& box)
{
	if (box.m_sections == 0)
		return 0;
	else
		return static_cast<int>(log2(box.m_sections) + 1);
}

void PrintBox(std::vector<BiscuitBox>& biscs)
{
	for (auto& bisc : biscs)
		std::cout << bisc << '\n';

	std::cout << '\n';
}

int main() {

	int tests_num;
	int* sections{ nullptr };

	std::cin >> tests_num;

	if (tests_num == 0)
	{
		std::cout << 0 << '\n';
		return 0;
	}

	std::vector<BiscuitBox> biscuits;
	std::vector<int> results;

	biscuits.reserve(tests_num);
	results.reserve(tests_num);

	sections = new int[tests_num] {0};

	for (int i = 0; i < tests_num; i++)
	{
		std::cin >> sections[i];
		biscuits.emplace_back(BiscuitBox(sections[i]));
	}

	PrintBox(biscuits);

	for (int i = 0; i < tests_num; i++)
	{
		if (sections[i] == 0)
		{
		//	std::cout << 0 << '\n';
			results.emplace_back(0);
		}
		else
		{
			std::cout << EatFastest(biscuits[i]) << " <-> log = " << Eat(biscuits[i]) << '\n';
			results.emplace_back(EatFastest(biscuits[i]));
		}
	}

	//printing results
	for (auto& r : results)
		std::cout << r << '\n';


	//freeing memory
	delete[] sections;

	std::system("pause");
	return 0;
}