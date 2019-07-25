#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Complete the pangrams function below.
string pangrams(string s)
{
	int alphabet_size = 26 + 1;
	vector<int> counter(alphabet_size, 0);

	for (char ch : s)
	{
		if (ch == ' ')
			counter[26]++;
		else if (ch >= 'a' && ch <= 'z')
			counter[ch - 'a']++;
		else        //the upper case letters
			counter[ch - 'A']++;
	}

	for (int i = 0; i < alphabet_size; i++)
	{
		if (counter[i] == 0)
			return string("not pangram");
	}

	return string("pangram");
}

int main()
{
	string s;
	getline(cin, s);

	string result = pangrams(s);

	cout << result << "\n";

	system("pause");
	return 0;
}
