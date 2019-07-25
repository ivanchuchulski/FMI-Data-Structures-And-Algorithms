#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// <letter_index, counter>
struct LetterCounter
{
	int letter_index;	// 'A' = 0, 'B' = 1, ... , 'Z' = 25
	int counter;
};

int main() {

	ios_base::sync_with_stdio(false);

	const size_t alphabet_size = 'Z' - 'A' + 1;
	int tests_num;

	cin >> tests_num;

	for (int t = 0; t < tests_num; t++)
	{
		string source;
		string target;

		cin >> source;
		cin >> target;

		//	sort(source.begin(), source.end());
		//	sort(target.begin(), target.end());

		vector<int> letters(alphabet_size, 0);

		for (int i = 0; i < source.size(); i++)
		{
			letters[source[i] - 'A']++;
			letters[target[i] - 'A']--;
		}

		bool already_are_anagrams = true;
		for (int i = 0; i < letters.size(); i++)		//initial check if the words are already anagrams
		{
			if (letters[i] != 0)			//the words are not already anagrams
			{
				already_are_anagrams = false;
				break;
			}
		}

		if (already_are_anagrams)
		{
			cout << 0 << '\n';
			continue;	//continue to next test
		}

		int to_pay = 0;
		
		vector<LetterCounter> leftover;	//<letter, count>

		for (int i = 0; i < letters.size(); i++)
		{
			if (letters[i] > 0)
			{
				for (int j = i + 1; j < letters.size(); j++)
				{
					if (letters[j] < 0)
					{
						int minim = min(letters[i], abs(letters[j]));

						to_pay += minim * (j - i);

						letters[j] += minim;
						letters[i] -= minim;

						if (letters[i] == 0)
							break;
					}
				}

				if (letters[i] > 0)
					leftover.push_back({ i, letters[i] });

			}
		}

		if (!leftover.empty())
		{
			for (LetterCounter& lett : leftover)
			{
				for (int j = 0; j < letters.size(); j++)
				{
					if (letters[j] < 0)
					{
						int minim = min(lett.counter, abs(letters[j]));

						to_pay += minim * (alphabet_size -lett.letter_index + j);

						letters[j] += minim;
						lett.counter -= minim;
					}
				
					if (lett.counter == 0)
						break;
				
				}
			}

		}


		cout << to_pay << '\n';
	}

	system("pause");
	return 0;
}