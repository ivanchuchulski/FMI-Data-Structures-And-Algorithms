#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cout;
using std::cin;


namespace fmi
{
	const int alpabet_size = 26;

	struct Node
	{
		bool _word_end;
		int _times_occured;		// counter for occurences of a char in a node

		Node* _childs[alpabet_size];

		Node()
		{
			_word_end = false;
			_times_occured = 0;

			for (auto& ch : _childs)
				ch = nullptr;
		}

	};


	class Trie
	{
	private:
		Node* _root;

	public:
		Trie()
			: _root(new Node())
		{}

		~Trie() 
		{}

		void InitialInsert(std::string& str)
		{
			Node* top = _root;

			for (auto& letter : str)
			{
				size_t indx = letter - 'a';

				//no mathcing for that letter yet
				if (top->_childs[indx] == nullptr)
					top->_childs[indx] = new Node();

				top = top->_childs[indx];
			}

			top->_times_occured++;
			top->_word_end = true;
		}

		void Insert(std::string& str, std::string& out)
		{
			Node* top = _root;
			bool stop_print = false;

			for (char letter : str)
			{
				size_t indx = letter - 'a';

				if (!stop_print)
					out += letter;

				if (top->_childs[indx] == nullptr)			//no mathcing for that letter yet
				{
					top->_childs[indx] = new Node();
					stop_print = true;
				}

				top = top->_childs[indx];
			}


			top->_times_occured++;
			top->_word_end = true;

			if (top->_times_occured > 1)
			{
				std::string as_string;
				int number = top->_times_occured;

				while (number > 0)
				{
					as_string.insert(as_string.end(), ((number % 10) + '0'));	//not as_string.begin()
					number /= 10;
				}
				std::reverse(as_string.begin(), as_string.end());

				out += ' ';
				out += as_string;		//int to char
			}

		}

	};
}


int main() {

	int N;
	std::string input_str;
	std::string dummy;
	fmi::Trie trie;
	std::vector<std::string> prefixes;
	
	std::ios_base::sync_with_stdio(false);

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		cin >> input_str;

		if (i == 0)
		{
			trie.InitialInsert(input_str);
			prefixes.push_back(std::string(1, input_str[0]));
		}
		else
		{
			trie.Insert(input_str, dummy);
			prefixes.push_back(dummy);
			dummy.clear();
		}


	}

 
	for (auto& pref : prefixes)
		cout << pref << '\n';




	std::system("pause");
	return 0;
}