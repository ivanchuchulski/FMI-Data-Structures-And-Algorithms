#include <iostream>
#include <vector>
#include <string>

#include "Trie.hpp"

using std::cout;
using std::cin;

int main() {

	std::vector<std::string> words = { "the", "a", "there", "answer", "any", "by", "bye", "their" };

	fmi::Trie trie;

	for (auto& str : words)
		trie.Insert(str);

	if (trie.Search(words[1]))
		cout << "yes\n";
	else
		cout << "no\n";



	std::system("pause");
	return 0;
}