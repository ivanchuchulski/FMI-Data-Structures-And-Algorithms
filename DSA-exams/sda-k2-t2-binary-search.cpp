#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using std::cout;
using std::cin;
using std::vector;

void BinarySearch(int* arr, int size, int x, int& found_pos, int& divisions_num)
{
	int first = 0, last = size - 1;
	int divisions = 0;

	while (first <= last)
	{
		divisions++;
		int middle = first + (last - first) / 2;

		if (arr[middle] == x)
		{
			found_pos = middle;
			divisions_num = divisions;
			return;
		}
		else if (x < arr[middle])
			last = middle - 1;
		else
			first = middle + 1;
	}

	found_pos = -1;
	divisions_num = divisions;
}


int main() {

	int N;
	int* arr{ nullptr };
	int K;
	int* quer{ nullptr };

	cin >> N;
	arr = new int[N];
	for (int i = 0; i < N; i++)
		cin >> arr[i];

	cin >> K;
	quer = new int[K];
	for (int i = 0; i < K; i++)
		cin >> quer[i];

	vector<int> indeces;
	vector<int> divisions;

	for (int i = 0; i < K; i++)
	{
		int divs_needed = 0;
		int found_at = 0;
		BinarySearch(arr, N, quer[i], found_at, divs_needed);

		indeces.push_back(found_at);
		divisions.push_back(divs_needed);
	}

	for (int i = 0; i < indeces.size(); i++)
		cout << indeces[i] << ' ';

	cout << '\n';

	for (int i = 0; i < divisions.size(); i++)
		cout << divisions[i] << ' ';

	cout << '\n';

	delete[] arr;
	delete[] quer;
	

	std::system("pause");
	return 0;
}