#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>


inline int Min(int a, int b)
{
	return a < b ? a : b;
}

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

int main() {

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
	freqs.reserve(input.size());

	for (int i = 0; i < input.size(); i++)
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

	std::string sorted, left, right, output;
	for (int i = 0; i < freqs.size(); i++)
		sorted.append(freqs[i].m_occurences, freqs[i].m_ch);

	if (sorted.size() % 2 != 0)
	{
		for (int i = 0; i < sorted.size() / 2 + 1; i++)
			left.append(1, sorted[i]);

		for (int i = sorted.size() / 2 + 1; i < sorted.size(); i++)
			right.append(1, sorted[i]);
	}
	else
	{
		for (int i = 0; i < sorted.size() / 2; i++)
			left.append(1, sorted[i]);

		for (int i = sorted.size() / 2; i < sorted.size(); i++)
			right.append(1, sorted[i]);
	}

	int counter = 0;
	for (int i = 0; i < Min(left.size(), right.size()); i++)
	{
		output.append(1, left[i]);
		output.append(1, right[i]);
		counter++;
	}

	//appendint additional chars if needed
	if (counter != left.size())
	{
		while (counter < left.size())
			output.append(1, left[counter++]);
	}
	else
	{
		while (counter < right.size())
			output.append(1, right[counter++]);
	}

	bool is_possible = true;
	for (int i = 0; i < output.size() - 2; i++)
	{
		if (output[i] == output[i + 1])
		{
			is_possible = false;
			break;
		}
		else
			continue;
	}

	if (is_possible)
		std::cout << "Yes\n";
	else
		std::cout << "No\n";

	std::system("pause");
	return 0;
}
