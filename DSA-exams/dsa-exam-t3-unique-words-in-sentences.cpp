#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {

	ios_base::sync_with_stdio(false);

	vector<string> out;
	string a;
	string b;

	unordered_map<string, int> occs;	//<word, occurance>

	getline(cin, a);
	getline(cin, b);

	string dummy;
	for (int i = 0; i < a.size(); i++)
	{

		if (a[i] == ' ')
		{
			occs[dummy]++;
			dummy.clear();
		}
		else
			dummy += a[i];
	}

	occs[dummy]++;
	dummy.clear();

	for (int i = 0; i < b.size(); i++)
	{
		if (b[i] == ' ')
		{
			occs[dummy]++;
			dummy.clear();
		}
		else
			dummy += b[i];
	}
	occs[dummy]++;

	for (auto& p : occs)
	{
		if (p.second == 1)
			out.push_back(p.first);
	}

	sort(out.begin(), out.end());

	for (string& str : out)
		cout << str << '\n';

	return 0;
}