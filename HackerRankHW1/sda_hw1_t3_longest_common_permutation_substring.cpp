#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>


void MakeStringToLowercase(std::string& str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += ('a' - 'A');
		else
			continue;
	}
}

void PrintString(const std::string& str)
{
	for (auto& s : str)
		std::cout << s;

	std::cout << '\n';
}

int FindOccurences(const std::string& str, const char ch)
{
	int occs = 0;
	for (size_t i = 0; i < str.length();i++)
	{
		if (str[i] == ch)
			occs++;
	}

	return occs;
}

int main() {

	const size_t MAX_SIZE = 1001;
	char* a =  new char[MAX_SIZE];
	char* b = new char[MAX_SIZE];

	std::memset(a, 0, MAX_SIZE);
	std::memset(b, 0, MAX_SIZE);

	std::cin.getline(a, 1001);
	std::cin.getline(b, 1001);

	std::string str_a{ a };
	std::string str_b{ b };

	//free dynamic memory
	delete[] a;
	delete[] b;

	MakeStringToLowercase(str_a);
	MakeStringToLowercase(str_b);


	//the size of the searched substring
	size_t overlap = 0;

	for (size_t i = 0; i < str_a.length() && i < str_b.length(); i++)
		overlap++;

	std::string substr;
	std::string buffer;

	for (size_t i = 0; i < str_a.length(); i++)
	{
		for (size_t j = 0; j < str_b.length(); j++)
		{
			if (str_a[i] == str_b[j])
			{
				bool found = false;
				for (size_t k = 0; k < buffer.length(); k++)
				{
					if (str_a[i] == buffer[k])
					{
						found = true;
						break;
					}
				}

				if(!found)
					buffer.push_back(str_b[j]);
			}
				
		}
	}

	PrintString(buffer);
	std::sort(buffer.begin(), buffer.end());
	PrintString(buffer);


	for (size_t i = 0; i < buffer.length(); i++)
	{
		size_t counter = std::min(FindOccurences(str_a, buffer[i]), FindOccurences(str_b, buffer[i]));

		if (counter != 0)
			substr.append(counter, buffer[i]);
	}

	PrintString(substr);

	system("pause");
	return 0;
}