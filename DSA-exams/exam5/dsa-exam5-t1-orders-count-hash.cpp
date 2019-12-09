#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <list>
#include <utility>

using namespace std;

struct Client
{
	int id;
	int count;

	Client(int other_id)
	{
		id = other_id;
		count = 0;
	}

	bool operator==(const Client& other)
	{
		return id == other.id;
	}

	bool operator!=(const Client& other)
	{
		return !(*this == other);
	}
};


class HashTable
{
public:
	int entries;
	vector<list<Client>> arr;

	HashTable(int N)
		: entries(0), arr(N)
	{

	}

	int Hash(int id)
	{
		return id % arr.size();
	}

	void AddOrder(int other_id)
	{
		auto& which_client = arr[Hash(other_id)];

		auto it = find(which_client.begin(), which_client.end(), other_id);

		//adding new order
		if (it == which_client.end())
		{
			which_client.push_back(Client(other_id));
		}




	}

	void IncrementOrder(int other_id)
	{

	}
};




int main() {

	int N;
	unordered_map<int, int> clients;

	cin >> N;

	int id = 0;
	int ship_order_count = 10;
	for (int i = 0; i < N; i++)
	{
		cin >> id;

		clients.insert({ id, 0 });

		clients[id]++;

		if (clients[id] == ship_order_count)
			clients.erase(id);

		//printing for debugging
		 //for (auto& p : clients)
		 //    cout << p.first << ", " << p.second << endl;

		 //cout << endl;
	}

	int sum = 0;
	for (auto& p : clients)
		sum += p.second;

	cout << clients.size() << ' ' << sum << '\n';


	return 0;
}