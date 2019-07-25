//task1
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <queue>
#include <list>

using namespace std;

int main() {

	ios_base::sync_with_stdio(false);

	int N;
	unordered_map<int, int> complaints;		// <int, int> means <entry number, how many times it appeared>
	list<int> entries;

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		int entry;
		cin >> entry;

		auto success = complaints.insert({ entry, 1 });
		entries.push_back(entry);

		if (!success.second)	//checking insert success, if false, then we already had a entry with the same value
			complaints[entry]++;

	}

	vector<int> que;
	vector<int> out;

	for (int i : entries)
	{
		if (complaints[i] == 1)
			out.push_back(i);

		if (complaints[i] >= 2)
		{
			que.push_back(i);
			complaints[i] = 0;	//setting it to 0 because if we encounter it later, we dont have to write to the que
		}
	}


	for (int j : out)
		cout << j << ' ';

	for (int k : que)
		cout << k << ' ';


	system("pause");
	return 0;
}
