#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <utility>

using namespace std;

namespace fmi
{

	class Graph
	{
	public:
		Graph(int vert_count)
			:	vertices(vert_count), 
				adj_list(vert_count)
		{}

		~Graph() = default;

		void AddEdge(int u, int v, int cost);

		void DijkstraSparse_set(int source);		//implementation optimal for sparse graphs
		void DijkstraSparse_pq(int source);			//implementation optimal for sparse graphs

		void PrimSparse_set(int source);


		vector<int> RestorePath(int source, int target, vector<int>& pred);

	private:
		int vertices;
		vector<vector<pair<int, int>>> adj_list;		//	pair<neighbour, weight>
	};


	void fmi::Graph::AddEdge(int u, int v, int cost)
	{
		adj_list[u].push_back({v, cost});
		adj_list[v].push_back({u, cost});	//if the graph is not oriented
	}

	void fmi::Graph::DijkstraSparse_set(int source)
	{
		const int INF = 1000000;

		vector<int> dist(vertices, INF);
		vector<int> pred(vertices, -1);
		set<pair<int, int>> que;		//the pair<distance_from_source, vertex_index>

		dist[source] = 0;
		que.insert({ 0, source });

		while (!que.empty())
		{
			int current = que.begin()->second;
			que.erase(que.begin());

			for (auto neigh : adj_list[current])
			{
				int to = neigh.first;
				int cost = neigh.second;

				if (dist[current] + cost < dist[to])
				{
					que.erase({ dist[to], to });

					dist[to] = dist[current] + cost;
					pred[to] = current;

					que.insert({ dist[to], to });
				}
			}
		}

		for (int i = 0; i < dist.size();i++)
			cout << "vertex " << i << " distance : " <<  dist[i] << '\n';

	}

	vector<int> fmi::Graph::RestorePath(int source, int target, vector<int>& pred)
	{
		vector<int> path;

		for (int vert = target; vert != source; vert = pred[vert])
			path.push_back(vert);

		path.push_back(source);		//add the source vertex first

		return path;
	}

	void fmi::Graph::DijkstraSparse_pq(int source)
	{
		using IntPair = pair<int, int>;
		const int INF = 1000000;

		vector<int> dist(vertices, INF);
		vector<int> pred(vertices, INF);
		priority_queue<IntPair, vector<IntPair>, std::greater<IntPair>> que;	//creating a min heap
	
		dist[source] = 0;
		que.push({ 0, source });

		while (!que.empty())
		{
			int current = que.top().second;
			int d_curr = que.top().first;

			que.pop();

			if (d_curr != dist[current])
				continue;

			for (auto neigh : adj_list[current])
			{
				int to = neigh.first;
				int cost = neigh.second;

				if (dist[current] + cost < dist[to])
				{
					dist[to] = dist[current] + cost;
					pred[to] = current;

					que.push({ dist[to], to });
				}
			}
		}

		for (int i = 0; i < dist.size(); i++)
			cout << "vertex " << i << " distance : " << dist[i] << '\n';
	}


	void fmi::Graph::PrimSparse_set(int source)
	{
		int total_weight = 0;
		const int INF = 1000000;

	//	vector<pair<int, int>> min_edge(vertices, INF);



	}
} 
