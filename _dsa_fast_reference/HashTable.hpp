
struct Node
{
	int data;
	string key;

	bool operator==(const Node& rhs) const
	{
		return data == rhs.data;
	}

	bool operator!=(const Node& rhs) const
	{
		return !(*this == rhs);
	}
};

class HashTable
{
private:
	int entries;
	vector<list<Node>> table;

public:
	HashTable(int size) : entries(0), table(size)
	{
	//	table.reserve(size);
	//	for (int i = 0; i < size; i++)
	//		table.push_back({});
	}


	inline bool Empty() const { return entries == 0; }
	inline int TableSize() const { return table.size(); }
	inline int Entries() const { return entries; }

	void ClearTable()
	{
		for (auto& item : table)
			item.clear();
	}

	bool InsertItem(Node& node)
	{
		auto& which_list = table[HashFunction(node.key)];

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
		entries++;

		if (entries > table.size())
			Rehash();

		return true;	//on successful insetion
	}


	bool Delete(Node& node)
	{
		auto& which_list = table[HashFunction(node.key)];
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
		entries--;
		return true;	//on successful deletion
	}

	Node Find(string& key)
	{
		auto& which_list = table[HashFunction(key)];
		auto itr = which_list.begin();

		for (; itr != which_list.end(); ++itr)
		{
			if (itr->key == key)
				break;
		}

		if (itr == which_list.end())
			return Node{};	//item not found, return empty object

		return Node(*itr);	//returning a copy of the found item
	}

private:
	int HashFunction(string& str)
	{
		return str.size() % table.size();
	}

	void Rehash()
	{
		vector<list<Node>> old_entries = table;

		table.resize(2 * table.size());
		ClearTable();

		entries = 0;
		for (auto& old_one : old_entries)
			for (auto& entry : old_one)
				InsertItem(entry);
	}

};


