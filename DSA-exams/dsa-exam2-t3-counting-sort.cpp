#include <iostream>
#include <cstdlib>
#include <vector>

int main() {

	size_t N;
	unsigned* input{};

	std::cin >> N;

	input = new unsigned[N] {};
	for (size_t i = 0; i < N; i++)
		std::cin >> input[i];

	const int max_input_value = 10000;
	unsigned* counts = new unsigned[max_input_value]{};
	std::vector<unsigned> sorted;

	//counting
	for (unsigned i = 0; i < N; i++)
		counts[input[i]]++;

	//putting in sorted
	for (unsigned i = 0; i < max_input_value; i++)
	{
		if (counts[i] > 0)
			sorted.emplace_back(i);
		else
			continue;
	}

	//printing out
	for (auto& s : sorted)
		std::cout << s << ' ';

	std::cout << std::endl;

	//freeing memory
	delete[] input;
	delete[] counts;


	std::system("pause");
	return 0;
}