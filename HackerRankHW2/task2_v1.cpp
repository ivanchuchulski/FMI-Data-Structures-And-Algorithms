#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

struct CharFrequency
{
	char m_ch;
	int m_occurences;

	CharFrequency() = default;
	CharFrequency(const CharFrequency& other) = default;
	~CharFrequency() = default;
	CharFrequency& operator=(const CharFrequency& other) = default;


	CharFrequency(char ch, int occs)
		:	m_ch(ch), m_occurences(occs)
	{}

	bool IsRepeating() const
	{
		return m_occurences > 1;
	}

	bool operator>(const CharFrequency& other)
	{
		return m_occurences > other.m_occurences;
	}
};


void SelectionSort(std::vector<CharFrequency>& vec)
{
	for (int i = 0; i < vec.size() - 1; i++)
	{
		int max_indx = i;
		for (int j = i + 1; j < vec.size(); j++)
		{
			if (vec[j] > vec[max_indx])
				max_indx = j;
		}

		if (max_indx != i)
			std::swap(vec[i], vec[max_indx]);
	}
}

int main () {

	std::string input;
	std::cin >> input;

	char first_ch = input[0];
	bool all_equal = true;

	for (int i = 1; i < input.length(); i++)
	{
		if (input[i] != first_ch)
		{
			all_equal = false;
			break;
		}
	}

	if (all_equal)
	{
		std::cout << "No\n";
		std::system("pause");
		return 0;
	}

	std::vector<CharFrequency> freqs;

	for (int i = 0; i < input.length(); i++)
	{
		bool already_counted = false;
		for (int j = 0; j < freqs.size(); j++)
		{
			if (input[i] != freqs[j].m_ch)
				continue;
			else
			{
				freqs[j].m_occurences++;
				already_counted = true;
			}
		}

		if (!already_counted)
			freqs.push_back(CharFrequency(input[i], 1));
	}

	bool has_repeating = false;
	for (int i = 0; i < freqs.size(); i++)
	{
		if (freqs[i].IsRepeating())
		{
			has_repeating = true;
			break;
		}
	}

	if (!has_repeating)
	{
		std::cout << "Yes\n";
		std::system("pause");
		return 0;
	}

	SelectionSort(freqs);


	CharFrequency most_repeating = freqs[0];
	int distinct_chars = freqs.size();
	int num_with_most_frequent = 0;

	for (int i = 1; i < freqs.size(); i++)
	{
		if (freqs[i].m_occurences > most_repeating.m_occurences)
			most_repeating = freqs[i];
		else
			continue;
	}

	for (int i = 0; i < freqs.size(); i++)
	{
		if (freqs[i].m_occurences == most_repeating.m_occurences)
			num_with_most_frequent++;
		else
			continue;
	}

	//len is odd
	if (input.size() % 2 != 0)
	{
		if (most_repeating.m_occurences > input.size() / 2)
		{
			if (distinct_chars < input.size() / 2) 
			{
				std::cout << "No\n";
				std::system("pause");
				return 0;
			}
		}
		else
		{
			std::cout << "Yes\n";
			std::system("pause");
			return 0;
		}
	}
	//len is even
	else 
	{
		if ((most_repeating.m_occurences > (input.size() / 2) + 1) || distinct_chars < input.size() / 2)
		{
			std::cout << "No\n";
			std::system("pause");
			return 0;
		}
		else
		{
			std::cout << "Yes\n";
			std::system("pause");
			return 0;
		}
	}


	std::system("pause");
	return 0;
}
