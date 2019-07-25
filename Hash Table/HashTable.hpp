#pragma once

#include <string>
#include <list>
#include <vector>
#include <algorithm>

/*hash table with chaining, each item is a linked list*/

namespace fmi
{
	using std::string;
	using std::list;
	using std::vector;

	const size_t DEFAULT_SIZE = 8;

	struct Node
	{
		int _data;
		string _key;

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
		HashTable(const HashTable& other);
		~HashTable();
		HashTable& operator=(const HashTable& other);

		inline bool Empty() const  { return _entries == 0; }
		inline int TableSize() const { return _table.size(); }
		inline int Entries() const { return _entries; }

		void ClearTable();
		
		bool InsertItem(Node& node);
	//	bool InsertItem(Node&& node);	//method, used in Rehashing(), it accepts a rvalue reference
		bool Delete(Node& node);
		Node Find(string& key);		//aiming for O(1)

	private:
		int HashFunction(string& str);
		void Rehash();


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

fmi::HashTable::HashTable(const HashTable& other)
	:	_entries(other._entries),
		_table(other._table)
{
	//_table.reserve(_entries);
	//for (int i = 0; i < _size; i++)
	//	_table.push_back(other._table[i]);
}

fmi::HashTable& fmi::HashTable::operator=(const HashTable& other)
{
	if (this != &other)
	{
		ClearTable();

		_entries = other._entries;
		_table.reserve(_entries);
		_table = other._table;
	}

	return *this;		// TODO: insert return statement here
}

fmi::HashTable::~HashTable()
{}



inline int fmi::HashTable::HashFunction(string& str)
{
	return str.size() % _table.size();
}

bool fmi::HashTable::InsertItem(Node& node)
{
	auto& which_list = _table[HashFunction(node._key)];

	auto itr = which_list.begin();
//	auto pos = std::find(which_list.begin(), which_list.end(), node);	//if the Node object has comparison operators == and !=

	for (; itr != which_list.end(); ++itr)
	{
		if (*itr == node)
			break;
	}

	if (itr != which_list.end())
		return false;	//item is in hash table, unsuccessful insertion

	which_list.push_back(node);
	_entries++;

	if (_entries > _table.size())
		Rehash();

	return true;	//on successful insetion
}

bool fmi::HashTable::Delete(Node& node)
{	
	auto& which_list = _table[HashFunction(node._key)];
	auto itr = which_list.begin();
//	auto pos = std::find(which_list.begin(), which_list.end(), node);	//if the Node object has comparison operators == and !=

	for (; itr != which_list.end(); ++itr)
	{
		if (*itr == node)
			break;
	}

	if (itr == which_list.end())
		return false;	//item not found, unsuccessful deletion
	
	which_list.erase(itr);
	_entries--;
	return true;	//on successful deletion
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

void fmi::HashTable::Rehash()
{
	vector<list<Node>> old_entries = _table;

	_table.resize(2 * _table.size());
	ClearTable();

	_entries = 0;
	for (auto& old_one : old_entries)
		for (auto& entry : old_one)
			InsertItem(entry);
}

void fmi::HashTable::ClearTable()
{
	for (auto& item : _table)
		item.clear();
}

