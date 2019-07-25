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


	Graph(int N)
		: vertices(N), adj_list(N)
	{}

	~Graph() = default;

	void AddEdge(int u, int v)
	{
		adj_list[u].push_back(v);
		adj_list[v].push_back(u);
	}

	void BFS(int source, int* distances)
	{
		bool* visited = new bool[vertices] {false};
		queue<int> que;

		que.push(source);
		visited[source] = true;

		while (!que.empty())
		{
			int current = que.front();
			que.pop();

			for (int neigh : adj_list[current])
			{
				if (!visited[neigh])
				{
					distances[neigh] = distances[current] + 1;
					visited[neigh] = true;
					que.push(neigh);
				}
			}
		}

		delete[] visited;
	}
};



int main() {

	int K;
	int a, b;

	const int max_edges = 300001;

	int* distances = new int[max_edges] {0};
	Graph graph(max_edges);

	cin >> K;

	for (int i = 0; i < K; i++)
	{
		cin >> a >> b;
		graph.AddEdge(a, b);
	}

	graph.BFS(0, distances);

	int sum = 0;

	for (int i = 0; i < max_edges; i++)
	{
		if (distances[i] != 0)
			sum += distances[i];
	}

	cout << sum << '\n';

	delete[] distances;

	
	return 0;
}