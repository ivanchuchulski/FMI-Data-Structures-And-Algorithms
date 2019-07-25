#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <utility>

using namespace std;

namespace nums
{
	using uint64 = unsigned long long;
	using uint32 = unsigned int;
}
namespace fmi
{

	class Graph
	{
	private:
		int vertices;
		vector<vector<pair<nums::uint32, nums::uint64>>> adj_list;		//	pair<neighbour, weight>

	public:
		Graph(nums::uint32 vert_count)
			:	vertices(vert_count),
				adj_list(vert_count)
		{}

		~Graph() = default;

		void AddEdge(nums::uint32 u, nums::uint32 v, nums::uint64 cost) 
		{
			adj_list[u].push_back({ v, cost });
			adj_list[v].push_back({ u, cost });		//bec the graph is not oriented
		}

		void DijkstraSparse_set(nums::uint32 source)
		{
			const nums::uint64 INF = 10'000'000'000;

			vector<nums::uint64> dist(vertices, INF);
			set<pair<int, int>> que;		//the pair<distance_from_source, vertex_index>

			dist[source] = 0;
			que.insert({ 0, source });

			while (!que.empty())
			{
				nums::uint32 current = que.begin()->second;
				que.erase(que.begin());

				for (auto neigh : adj_list[current])
				{
					nums::uint32 to = neigh.first;
					nums::uint64 cost = neigh.second;

					if (dist[current] + cost < dist[to])
					{
						que.erase({ dist[to], to });

						dist[to] = dist[current] + cost;

						que.insert({ dist[to], to });
					}
				}
			}

			for (nums::uint32 i = 0; i < dist.size(); i++)
			{
				if (i == source)
					continue;

				if (dist[i] == INF)
					cout << -1 << ' ';
				else
					cout << dist[i] << ' ';
			}


		}

		vector<int> RestorePath(int source, int target, vector<int>& pred)
		{
			vector<int> path;

			for (int vert = target; vert != source; vert = pred[vert])
				path.push_back(vert);

			path.push_back(source);		//add the source vertex first

			return path;
		}

		void Clear()
		{
			vertices = 0;
			adj_list.clear();
		}

	};
}



int main() {

	ios_base::sync_with_stdio(false);	//make C++ i/o streams faster

	nums::uint32 tests_num = 0;
	nums::uint32 vertices = 0;
	nums::uint32 edges = 0;

	cin >> tests_num;

	for (nums::uint32 i = 0; i < tests_num; i++)
	{
		cin >> vertices;
		cin >> edges;

		fmi::Graph graph(vertices);

		for (nums::uint32 j = 0; j < edges; j++)
		{
			nums::uint32 u_vert = 0;
			nums::uint32 v_vert = 0;
			nums::uint64 cost = 0;

			cin >> u_vert >> v_vert >> cost;

			graph.AddEdge(u_vert - 1, v_vert - 1, cost);	//we add -1 bec in the graph we count the vertices from 0
		}

		nums::uint32 start_from = 0;
		cin >> start_from;

		graph.DijkstraSparse_set(start_from - 1);

		cout << '\n';
	}


	system("pause");
	return 0;
}