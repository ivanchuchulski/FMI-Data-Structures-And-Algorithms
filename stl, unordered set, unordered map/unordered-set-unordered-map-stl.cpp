#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>
#include <utility>


using std::cout;
using std::cin;


int main() {


	{
		std::vector<int> vec{ 5, 3, 1, 8, 1, 11, 13 };

		std::unordered_set<int> u_set{ vec.begin(), vec.end() };

		for (auto it = u_set.begin(); it != u_set.end(); ++it)
			cout << *it << ' ';

		cout << '\n';

		auto elements_erased = u_set.erase(5);

		u_set.insert(10);

		for (int val : u_set)
			cout << val << ' ';

		cout << '\n';
	}


	{
		std::vector<std::pair<std::string, int>> vec{ {"a", 5}, { "b", 3}, {"c", 1}, {"d", 8},{"k", 1},{"e", 11}, {"f", 13} };

		std::unordered_map<std::string, int> u_map{ vec.begin(), vec.end() };


		for (auto it = u_map.begin(); it != u_map.end(); ++it)
			cout << it->first << ", " << it->second << '\n';

		cout << '\n';

		u_map.insert(std::pair<std::string, int>{ "w", 1});

	//	u_map.insert(std::pair<std::string, int>{ "a", 98});	//wont change anything with insert(), because keys are unique and the is already a key 'a'
		u_map["a"] = 98;										//here we access the element and change it

		for (auto& p : u_map)
			cout << p.first << ", " << p.second << '\n';

		cout << '\n';
	}






	std::system("pause");
	return 0;
}
