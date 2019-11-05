#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
	

class Graph
{
private:
	int vertices;
	vector<vector<int>> adj_list;

public:
	Graph(int vert_count)
		:	vertices(vert_count), adj_list(vert_count)
	{}

	~Graph() = default;

	void AddEdge(int u, int v)
	{
		adj_list[u].push_back(v);
		adj_list[v].push_back(u);
	}

	int GetLevelCount()
	{
		int level_counter = 0;
		bool* used = new bool[vertices] { false };
		queue<int> que;

		que.push(0);
		used[0] = true;
		
		while (!que.empty())
		{
			level_counter++;

			int que_size = que.size();
			while (que_size > 0)
			{
				int current = que.front();
				que.pop();

				for (int neigh : adj_list[current])
				{
					if (!used[neigh])
					{
						que.push(neigh);
						used[neigh] = true;
					}
				}

				que_size--;
			}
		}

		delete[] used;
		return level_counter;
	}


	int GetNodeLevel(int vert)
	{
		int level_counter = 0;

		if (vert == 0)
			return level_counter;

		bool* used = new bool[vertices] { false };
		queue<int> que;

		que.push(0);
		used[0] = true;

		while (!que.empty())
		{
			level_counter++;

			int que_size = que.size();
			while (que_size > 0)
			{
				int current = que.front();
				que.pop();

				if (current == vert)
					return level_counter;

				for (int neigh : adj_list[current])
				{
					if (!used[neigh])
						que.push(neigh);
				}

				que_size--;
			}
		}

		delete[] used;
		return -1; // if vertex not present
	}
};


int main() {

	ios_base::sync_with_stdio(false);

	int vert_count;
	int ivan_pos;
	int alex_pos = 0;	//Alex starts at the root of the tree
	
	cin >> vert_count >> ivan_pos;

	Graph playground(vert_count);
	int u, v;

	for (int i = 0; i < vert_count - 1; i++)
	{
		cin >> u >> v;
		playground.AddEdge(u - 1, v - 1);
	}
	
	ivan_pos--;
	int move_count = 0;

	if (ivan_pos == alex_pos)
	{
		cout << move_count << '\n';
		return 0;
	}

	int deepest_level = playground.GetLevelCount();
	int ivan_level = playground.GetNodeLevel(ivan_pos);
	int alex_level = playground.GetNodeLevel(alex_pos);



	system("pause");
	return 0;
}
