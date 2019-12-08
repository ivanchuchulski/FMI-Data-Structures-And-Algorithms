#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <numeric>

using std::cout;
using std::cin;
using int64 = long long;


int main() {

	int N = 0;
	int clone_from, mass;

	std::vector<std::list<int>> snowman_list;
	int64 overall_sum = 0;

	//adding the 0-th snowman
	snowman_list.push_back(std::list<int>(1, 0));

	cin >> N;
	snowman_list.reserve(N);


	for (int i = 0; i < N; i++)
	{
		cin >> clone_from >> mass;

		snowman_list.emplace_back(snowman_list[clone_from]);

		if (mass == 0)
		{
			if (snowman_list.back().size() == 1)		// we dont pop if we have 1 element
				;
			else
				snowman_list.back().pop_back();
		}
		else
			snowman_list.back().push_back(mass);

		overall_sum += std::accumulate(snowman_list.back().begin(), snowman_list.back().end(), 0);
	}


	cout << overall_sum << '\n';


	std::system("pause");
	return 0;
}