#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <utility>
#include <functional>

using namespace std;

namespace mst
{
	struct Edge
	{
		int to;
		int cost;

		bool operator<(const Edge& other) const
		{
			return cost < other.cost;
		}

		bool operator>(const Edge& other) const
		{
			return cost > other.cost;
		}

		Edge(int _to, int _cost)
			:	to(_to), cost(_cost)
		{}
	};

	class Graph
	{

	private:
		int vertices;
		vector <vector<Edge>> adj_list;

	public:
		Graph(int vert_count)
			:	vertices(vert_count),
				adj_list(vert_count)
		{}

		~Graph() = default;

		void AddEdge(int u, int v, int cost)
		{
			adj_list[u].push_back({ v, cost });
			adj_list[v].push_back({ u, cost });
		}

		void Prim_set(int source = 0)
		{
			int total_weight = 0;
			const int INF = 1'000'000;

			vector<Edge> key(vertices, { -1, INF });	//key[vertex_index] stores the cheapest edge to it from the MST we build
			set<Edge> que;
			bool* inMST = new bool[vertices] {false};

			key[source].cost = 0;
			que.insert({ source, 0 });

			for (int i = 0; i < vertices; i++)
			{
				if (que.empty())
					return;		// no mst!, or disconnected graph!

				int current = que.begin()->to;
				que.erase(que.begin());

				total_weight += key[current].cost;
				inMST[current] = true;

				if (key[current].to != -1)
					cout << current << ' ' << key[current].to << '\n';

				for (Edge edg : adj_list[current])
				{
					int to = edg.to;
					int price_from_current = edg.cost;
					int old_price = key[edg.to].cost;

					if (price_from_current < old_price && !inMST[to])
					{
						que.erase({ to, old_price });

						key[to] = { current, price_from_current };

						que.insert({ to, price_from_current });
					}
				}
			}

			cout << total_weight << '\n';

			delete[] inMST;
		}

		void Prim_pq(int source = 0)
		{
			const int INF = 1'000'000;
			int total_weight = 0;

			priority_queue<Edge, vector<Edge>, greater<Edge>> que;

			vector<int> key(vertices, INF);
			vector<int> pred(vertices, -1);
			bool* inMST = new bool[vertices] { false };

			que.push(Edge(source, 0));
			key[source] = 0;

			for (int i = 0; i < vertices; i++)
			{
				if (que.empty())
					return;		//no mst, disconnected graph

				int current = que.top().to;
				int curr_dist = que.top().cost;
				que.pop();

				if (curr_dist != key[current])
					continue;

				total_weight += key[current];
				inMST[current] = true;

				if (pred[current] != -1)
					cout << current << ' ' << pred[current] << '\n';

				for (Edge neigh : adj_list[current])
				{
					if (neigh.cost < key[neigh.to] && !inMST[neigh.to])
					{
						key[neigh.to] = neigh.cost;
						pred[neigh.to] = current;
						que.push(Edge(neigh.to, neigh.cost));
					}
				}
			}

			cout << total_weight << '\n';
			delete[] inMST;
		}

	};


}

