#pragma once

#include <string>


namespace fmi
{

	const int alpabet_size = 26;

	struct Node
	{
		bool _is_word_end;
		Node* _childs[alpabet_size];

		Node()
		{
			_is_word_end = false;

			for (auto& ch : _childs)
				ch = nullptr;
		}

	};


	class Trie
	{
	public:
		Node* _root;

		Trie();
		~Trie();

		void Insert(std::string& str);
		bool Search(std::string& str);

	};

}

fmi::Trie::Trie()
	: _root(new Node())
{}

//ToDo : implement destructor
fmi::Trie::~Trie()
{}

void fmi::Trie::Insert(std::string& str)
{
	Node* top = _root;

	for (auto& letter : str)
	{
		size_t indx = letter - 'a';

		if (top->_childs[indx] == nullptr)
			top->_childs[indx] = new Node();


		top = top->_childs[indx];
	}

	top->_is_word_end = true;
}

bool fmi::Trie::Search(std::string& str)
{
	Node* top = _root;

	for (auto& letter : str)
	{
		size_t indx = letter - 'a';

		if (top->_childs[indx] == nullptr)
			return false;

		top = top->_childs[indx];
	}

	return top != nullptr && top->_is_word_end;
}
