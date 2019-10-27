/*
	given two strings A and B find a string which
		-is a substring of a permutaion of A and permutation a of B
		-has the maximum length of all string with that property
	if we have 2 or more strings that satisfies these conditions
	the output should be the smallest in lexicographical sense

	example :
	A = autumn
	B = tournament
	output : amntu, because is substr of perm of a : uamntu and is substr of a perm of b : ornamntuet

	complexity is max(length(firstString), lenght(secondString), length(commonLetters)), 
	also the append method is O(result) which is bigger than O(commonLetters) in some cases, but it's still
	less than the max of lengths of the input strings
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <array>

using namespace std;

#define newline '\n'

void ToLower(std::string& str)
{
	for (char ch : str)
	{
		if (ch >= 'A' && ch <= 'Z')
		{
			ch += ('a' - 'A');
		}
	}
}

int FindOccurences(const std::string& str, const char ch)
{
	return std::count(str.begin(), str.end(), ch);
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	string firstString;
	string secondString;
	string result;
	unordered_set<char> firstLetters;
	unordered_set<char> secondLetters;
	unordered_map<char, int> firstLettersOccurrences;
	unordered_map<char, int> secondLettersOccurrences;
	unordered_set<char> commonLetters;
	const int numberOfEnglishLetters = 'z' - 'a' + 1;
	std::array<int, numberOfEnglishLetters> resultLetters{};

	getline(cin, firstString);
	getline(cin, secondString);

	ToLower(firstString);
	ToLower(secondString);

	// finding all unique common letters in the two strings
	for (char letter : firstString)
	{
		firstLetters.insert(letter);
		firstLettersOccurrences[letter]++;
	}

	for (char letter : secondString)
	{
		secondLetters.insert(letter);
		secondLettersOccurrences[letter]++;
	}

	for (char letter : firstLetters)
	{
		if (secondLetters.find(letter) != secondLetters.end())
		{
			commonLetters.insert(letter);
		}
	}

	result.reserve(commonLetters.size());

	for (char letter : commonLetters)
	{
		//int counter = min(FindOccurences(firstString, letter), FindOccurences(secondString, letter)); // slower
		int counter = min(firstLettersOccurrences[letter], secondLettersOccurrences[letter]);
		resultLetters[letter - 'a'] += counter;
	}
	
	// sorting the output, O(1)
	for (int i = 0; i < resultLetters.size(); i++)
	{
		int count = resultLetters[i];
		char letter = i + 'a';

		result.append(count, letter);
	}

	cout << result << newline;

	return 0;
}