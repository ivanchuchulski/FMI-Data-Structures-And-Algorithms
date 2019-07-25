#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>


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
		std::cout << s << '\n';

	std::cout << '\n';
}

void PrintVector(const std::vector<std::string>& vec)
{
	for (auto& v : vec)
		std::cout << v << '\n';

	std::cout << '\n';
}

void FindSubsPerms(std::string& str, std::vector<std::string>& vec)
{
	do
	{
	//	std::cout << str << '\n';

		for (size_t i = 0; i < str.size(); i++)
		{
	//		std::cout << "sub : " << str.substr(i) << '\n';
			vec.emplace_back(str.substr(i));
		}

	} while (std::next_permutation(str.begin(), str.end()));
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

	std::vector<std::string> subs_a;
	std::vector<std::string> subs_b;

	subs_a.reserve(str_a.size());
	subs_b.reserve(str_b.size());

	FindSubsPerms(str_a, subs_a);
	FindSubsPerms(str_b, subs_b);

//	std::cout << "\n subs : \n";
//	PrintVector(subs_a);
//	PrintVector(subs_b);
//	std::cout << '\n';

	std::sort(subs_a.begin(), subs_a.end());
	std::sort(subs_b.begin(), subs_b.end());

//	std::cout << "\n sorted subs : \n";
//	PrintVector(subs_a);
//	PrintVector(subs_b);
//	std::cout << '\n';


	std::vector < std::string> perm_subs;
	perm_subs.reserve(10);

	for (size_t i = 0; i < subs_a.size(); i++)
	{
		for (size_t j = 0; j < subs_b.size(); j++)
		{
			if (subs_a[i] == subs_b[j])
				//perm_subs.emplace_back(subs_a[i]);
				continue;

			else
				subs_a.erase(subs_a.begin() + i);
		}
	}

	size_t ind = 0;

	for (size_t i = 1; i < perm_subs.size(); i++)
	{
		if (perm_subs[i].length() > perm_subs[ind].length())
			ind = i;
	
		else if (perm_subs[i].length() == perm_subs[ind].length())
		{
			if (perm_subs[i] < perm_subs[ind])
				ind = i;
		}
	}

//	std::cout << "\n permut subs : \n";
//	PrintVector(perm_subs);
//	std::cout << '\n';

	std::cout << perm_subs[ind] << '\n';

	system("pause");
	return 0;
}