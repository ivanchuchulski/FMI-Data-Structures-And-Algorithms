#include <iostream>
#include <cstdlib>
#include <vector>
#include <numeric>

using std::cout;
using std::cin;
using int64 = long long;

struct Snowman
{
	int ancestor;
	int mass;
};


int main() {

	int N = 0;
	int clone_from = 0, mass = 0;

	std::vector<int> snowman_masses;
	std::vector<int> ancestors;

	//std::vector<Snowman> snowmans;

	int64 overall_sum = 0;

	cin >> N;
	snowman_masses.reserve(N);
	ancestors.reserve(N);

	snowman_masses.emplace_back(0);
	ancestors.emplace_back(0);

	//snowmans.push_back({ 0, 0 });

	for (int i = 0; i < N; i++)
	{
		cin >> clone_from >> mass;

		if (mass == 0)
		{
			if (ancestors[clone_from] == 0)	//cloning from a snowman that has only 1 snoball
			{
				snowman_masses.emplace_back(0);
				ancestors.emplace_back(0);
			}
			else
			{
				snowman_masses.emplace_back(snowman_masses[ancestors[clone_from]]);
				ancestors.emplace_back(ancestors[ancestors[clone_from]]);
			}

		}
		else
		{
			snowman_masses.emplace_back(mass + snowman_masses[clone_from]);
			ancestors.emplace_back(clone_from);
		}
	}




	cout << std::accumulate(snowman_masses.begin(), snowman_masses.end(), 0) << '\n';


	std::system("pause");
	return 0;
}