/*
	time complexity is max(length(firstString), lenght(secondString), length(commonLetters)), 
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

struct StringLowercaseLetterMap
{
public:
	StringLowercaseLetterMap()
		: lettersMap()
	{}

	void AddOccurrence(char letter)
	{
		lettersMap[LetterIndex(letter)]++;
	}

	void AddOccurrence(char letter, int numberOfOccurrences)
	{
		lettersMap[LetterIndex(letter)] += numberOfOccurrences;
	}

	bool ContainsLetter(char letter)
	{
		return lettersMap[LetterIndex(letter)] > 0;
	}
	
	int GetLetterOccurrence(char letter)
	{
		return lettersMap[LetterIndex(letter)];
	}

	auto Begin()
	{
		return lettersMap.begin();
	}

	auto End()
	{
		return lettersMap.end();
	}

private:
	int LetterIndex(char letter)
	{
		return letter - 'a';
	}


private:
	static const int alphabetSize = 'z' - 'a' + 1;
	std::array<int, alphabetSize> lettersMap;
};


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

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	string firstString;
	string secondString;
	string result;
	StringLowercaseLetterMap firstMap;
	StringLowercaseLetterMap secondMap;

	getline(cin, firstString);
	getline(cin, secondString);

	ToLower(firstString);
	ToLower(secondString);

	// finding all unique common letters in the two strings
	for (char letter : firstString)
	{
		firstMap.AddOccurrence(letter);
	}

	for (char letter : secondString)
	{
		secondMap.AddOccurrence(letter);
	}

	// we know that the alphabet is only lowercase letters, so we can iterate over the alphabet itself
	// and in this way the input is sorted lexicographically
	for (char letter = 'a'; letter <= 'z'; letter++)
	{
		if (firstMap.ContainsLetter(letter) && secondMap.ContainsLetter(letter))
		{
			int counter = std::min(firstMap.GetLetterOccurrence(letter), secondMap.GetLetterOccurrence(letter));

			result.append(counter, letter);
		}
	}

	cout << result << newline;

	return 0;
}