#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <cmath>

using std::cout;
using std::cin;
using std::string;
using std::list;
using std::vector;

using int64 = long long;


/*hash table with chaining, each item is a linked list*/

namespace fmi
{
	const size_t DEFAULT_SIZE = 8;

	struct Node
	{
		int64 _data;

		bool operator==(const Node& rhs) const
		{
			return _data == rhs._data;
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
		~HashTable();

		inline bool Empty() const { return _inserted == 0; }
		inline size_t TableSize() const { return _table.size(); }
		inline size_t Entries() const { return _inserted; }

		void ClearTable();

		bool InsertItem(Node& node);

	private:
		int HashFunction(long long val);

	private:
		size_t _inserted;
		vector<list<Node>> _table;
	};
}

/*		implementation		*/

fmi::HashTable::HashTable(int size)
	:	_inserted(0),
		_table()
{
	if (size > 0)
	{
		_table.reserve(size);
		for (int i = 0; i < size; i++)
			_table.push_back({});
	}
}

fmi::HashTable::~HashTable()
{}

inline int fmi::HashTable::HashFunction(long long val)
{
	return	std::abs(val) % _table.size();
}

bool fmi::HashTable::InsertItem(Node& node)
{
	auto& which_list = _table[HashFunction(node._data)];

	auto itr = which_list.begin();

	for (; itr != which_list.end(); ++itr)
	{
		if (*itr == node)
			break;
	}

	if (itr != which_list.end())
		return false;	//item is in hash table, unsuccessful insertion

	which_list.push_back(node);
	_inserted++;

	return true;	//on successful insetion
}

void fmi::HashTable::ClearTable()
{
	for (auto& item : _table)
		item.clear();

	_inserted = 0;
}


int main() {

	std::ios_base::sync_with_stdio(false);

	int N;
	fmi::Node temp{ 0 };

	cin >> N;

	fmi::HashTable table(N);

	for (int i = 0; i < N; i++)
	{
		cin >> temp._data;

		table.InsertItem(temp);
	}

	cout << table.Entries() << '\n';

	std::system("pause");
	return 0;
}