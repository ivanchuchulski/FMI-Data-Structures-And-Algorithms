#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <unordered_set>

using namespace std;

class Graph
{
private:
	int vertices;
	vector<vector<int>> adj;        //no need to store the weights
public:

	Graph(int vert) : vertices(vert), adj(vert)
	{}

	void AddEdge(int u, int v)
	{
		adj[u].push_back(v);
	}


	void Util_HasCycle(int current, unordered_set<int>& passed, int& counter)
	{
		passed.insert(current);

		for (auto neigh : adj[current])
		{
			if (passed.count(neigh) > 0)
				counter++;
			else
				Util_HasCycle(neigh, passed, counter);
		}

		passed.erase(current);

	}

	bool HasCycle()
	{
		unordered_set<int> passed;
		int counter = 0;

		for (int vert = 0; vert < vertices; vert++)
		{
			Util_HasCycle(vert, passed, counter);
			passed.clear();

			if (counter > 0)
				return true;
		}

		return false;
	}

};


int main() {

	ios_base::sync_with_stdio(false);

	int tests;

	cin >> tests;

	for (int i = 0; i < tests; i++)
	{
		int vert;
		int edges;

		cin >> vert >> edges;

		Graph graph(vert);

		for (int j = 0; j < edges; j++)
		{
			int u, v, w;
			cin >> u >> v >> w;
			graph.AddEdge(u - 1, v - 1);
		}

		if (graph.HasCycle())
			cout << "true";
		else
			cout << "false";

		cout << ' ';
	}


	system("pause");
	return 0;
}