#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include <queue>


using namespace std;


class Graph
{
public:
	int vertices;
	vector<list<int>> adj_list;


	Graph(int vert_count)
		: vertices(vert_count), adj_list(vert_count)
	{}

	~Graph() = default;

	void AddEdge(int u, int v)
	{
		adj_list[u].push_back(v);
		adj_list[v].push_back(u);
	}

	void BFS(int source, std::vector<int>& distances, const int edge_weight)
	{
		bool* visited = new bool[vertices] {false};
		queue<int> que;

		visited[source] = true;
		que.push(source);

		while (!que.empty())
		{
			int current = que.front();
			que.pop();

			for (int neigh : adj_list[current])
			{
				if (!visited[neigh])
				{
					distances[neigh] = distances[current] + edge_weight;

					visited[neigh] = true;
					que.push(neigh);
				}
			}
		}

		delete[] visited;
	}
};



int main() {

	const int max_nodes_num = 1000;
	const int edge_weight = 6;

	int querries;
	int u_node, v_node;
	int nodes;
	int edges;
	int start_from;



	cin >> querries;

	for (int i = 0; i < querries; i++)
	{
		cin >> nodes >> edges;

		Graph graph(nodes);
		vector<int> distances_from_source(nodes, 0);

		for (int j = 0; j < edges + 1; j++)
		{
			if (j < edges)
			{
				cin >> u_node >> v_node;

				//we add -1 because the input starts from 1, and in the graph we count them from 0
				graph.AddEdge(u_node - 1, v_node - 1);
			}

			else
				cin >> start_from;
		}

		graph.BFS(start_from - 1, distances_from_source, edge_weight);

		for (int i = 0; i < distances_from_source.size(); i++)
		{
			if (i == start_from - 1)	//we dont print the distance from the start to itself
				continue;

			else if (distances_from_source[i] == 0)		//unreachable node from the sourse
				cout << -1 << ' ';

			else
				cout << distances_from_source[i] << ' ';
		}

		cout << '\n';
	}

	std::system("pause");
	return 0;
}