#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cstdint>


class BiscuitBox
{
public:
	unsigned int m_N;
	std::vector<unsigned int> m_sections;

	BiscuitBox() = default;
	BiscuitBox(const BiscuitBox& other) = default;
	~BiscuitBox() = default;
	BiscuitBox& operator=(const BiscuitBox& other) = default;

	BiscuitBox(unsigned int N)
		:m_N(N), m_sections()
	{
		m_sections.reserve(N);
		for (unsigned int i = 0; i < m_N; i++)
			m_sections.emplace_back(i + 1);
	}

	void CreateBox(unsigned int N)
	{
		m_N = N;
		m_sections.reserve(N);
		for (unsigned int i = 0; i < m_N; i++)
			m_sections.emplace_back(i + 1);
	}

	friend std::ostream& operator<<(std::ostream& outS, const BiscuitBox& b)
	{
		std::cout << "N : " << b.m_N << ", ";
		for (size_t i = 0; i < b.m_N; i++)
			std::cout << b.m_sections[i] << ' ';

		std::cout << '\n';

		return outS;
	}

	bool AllEaten() const
	{
		for (size_t i = 0; i < m_sections.size(); i++)
		{
			if (m_sections[i] != 0)
				return false;
		}

		return true;
	}

	unsigned long long GetP() const
	{
		unsigned long long sum = 0, non_negative_count = 0;
		for (size_t i = 0; i < m_sections.size(); i++)
		{
			if (m_sections[i] > 0)
			{
				sum += m_sections[i];
				non_negative_count++;
			}
		}

		return (sum / non_negative_count);
	}


};

void PrintBox(std::vector<BiscuitBox>& biscs)
{

	for (size_t i = 0; i < biscs.size(); i++)
	{
		std::cout << biscs[i] << '\n';
	}

}


//days start from 1
unsigned long long EatFastest(BiscuitBox& box)
{
	unsigned long long days = 0;
	unsigned long long p = 0;		 //the optimal number of biscuits to eat in a day

	while (!(box.AllEaten()))
	{
		p = box.GetP();
		for (size_t i = 0; i < box.m_sections.size(); i++)
		{
			if (box.m_sections[i] >= p)
				box.m_sections[i] -= p;
		}
		days++;
	}

	return days;
}

int main() {

	unsigned int tests_num;
	unsigned int* sections{ nullptr };

	std::cin >> tests_num;

	sections = new unsigned int[tests_num] {0u};

	for (unsigned i = 0; i < tests_num; i++)
		std::cin >> sections[i];

	std::vector<BiscuitBox> biscuits;
	biscuits.reserve(tests_num);

	for (unsigned int i = 0; i < tests_num; i++)
		biscuits.emplace_back(BiscuitBox(sections[i]));

//	PrintBox(biscuits);

	for (size_t i = 0; i < biscuits.size(); i++)
		std::cout << EatFastest(biscuits[i]) << '\n';


	//freeing memory
	delete[] sections;


	std::system("pause");
	return 0;
}