#include <iostream>
#include <vector>
#include <string>
#include <list>

using std::cout;
using std::cin;


namespace fmi
{
	using std::string;
	using std::list;
	using std::vector;

	const size_t DEFAULT_SIZE = 8;

	struct Node
	{
		int _dublicate_count;
		string _key;

		Node(int dubl_count, string& str)
			:	_dublicate_count(dubl_count),
				_key(str)
		{}

		Node(const Node& other) = default;

		bool operator==(const Node& rhs) const
		{
			return _key == rhs._key;
		}

		bool operator!=(const Node& rhs) const
		{
			return !(*this == rhs);
		}


	};

	class HashTable
	{
	public:
		HashTable(int size = DEFAULT_SIZE);
		~HashTable() = default;

		inline bool Empty() const { return _entries == 0; }
		inline int TableSize() const { return _table.size(); }
		inline int Entries() const { return _entries; }

		void ClearTable();

		bool InsertItem(string& node);
		Node Find(string& key);

	private:
		int HashFunction(string& str);

	private:
		int _entries;
		vector<list<Node>> _table;
	};
}

/*		implementation		*/

fmi::HashTable::HashTable(int size)
	:	_entries(0),
		_table()
{
	int builder_size = size > 0 ? size : DEFAULT_SIZE;

	_table.reserve(builder_size);
	for (int i = 0; i < builder_size; i++)
		_table.push_back({});
}


inline int fmi::HashTable::HashFunction(string& str)
{
	return str.size() % _table.size();
}

bool fmi::HashTable::InsertItem(string& key)
{
	auto& which_list = _table[HashFunction(key)];
	auto itr = which_list.begin();

	for (; itr != which_list.end(); ++itr)
	{
		if (itr->_key == key)
			break;
	}

	if (itr != which_list.end())
	{
		itr->_dublicate_count++;	//item is in hash table, unsuccessful insertion
	}	

	which_list.push_back(Node(1, key));
	_entries++;


	return true;	//on successful insetion
}


fmi::Node fmi::HashTable::Find(string & key)
{
	auto& which_list = _table[HashFunction(key)];
	auto itr = which_list.begin();

	for (; itr != which_list.end(); ++itr)
	{
		if (itr->_key == key)
			break;
	}

	if (itr == which_list.end())
		return Node{};	//item not found, return empty object

	return Node(*itr);	//returning a copy of the found item
}

void fmi::HashTable::ClearTable()
{
	for (auto& item : _table)
		item.clear();
}




int main() {

	int N;
	std::string input_str;
	std::string dummy;
	std::vector<std::string> prefixes;


	cin >> N;

	fmi::HashTable table(N);

	for (int i = 0; i < N; i++)
	{
		cin >> input_str;

		if (i == 0)
		{
			table.InitialInsert(input_str);
			prefixes.push_back(std::string(1, input_str[0]));
		}
		else
		{
			//	trie.GetPrefix(input_str, dummy);
			//	prefixes.push_back(dummy);

			table.Insert(input_str, dummy);
			prefixes.push_back(dummy);
			dummy.clear();
		}


	}


	for (auto& pref : prefixes)
		cout << pref << '\n';




	std::system("pause");
	return 0;
}