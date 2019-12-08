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
	using int64 = long long;
	using uint32 = unsigned int;
}
namespace fmi
{

	class Graph
	{
	private:
		int vertices;
		vector<vector<pair<nums::uint32, nums::int64>>> adj_list;		//	pair<neighbour, weight>

	public:
		Graph(nums::uint32 vert_count)
			:	vertices(vert_count),
				adj_list(vert_count)
		{}

		~Graph() = default;

		void AddEdge(nums::uint32 u, nums::uint32 v, nums::int64 cost)
		{
			adj_list[u].push_back({ v, cost });
		}

		void Longest_DijkstraSparse_set(nums::uint32 source, nums::uint32 target)
		{
			const nums::int64 initial_value = -10'000'000'000;

			//making the set sort the pairs in descending order; pair<distance_from_source, vertex_index>
			set<pair<int, int>, greater<pair<int, int>>> que;
			vector<nums::int64> dist(vertices, initial_value);

			bool* marked = new bool[vertices] { false };

			dist[source] = 0;
			que.insert({ 0, source });

			while (!que.empty())
			{
				nums::uint32 current = que.begin()->second;
				que.erase(que.begin());

				for (auto neigh : adj_list[current])
				{
					nums::uint32 to = neigh.first;
					nums::int64 cost = neigh.second;

					if (dist[current] + cost > dist[to])
					{
						que.erase({ dist[to], to });

						dist[to] = dist[current] + cost;

						que.insert({ dist[to], to });
					}
				}
			}

			//printing the longest distance

			if (dist[target] != initial_value)
				cout << dist[target] << '\n';
			else
				cout << -1 << '\n';

			delete[] marked;
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

	nums::uint32 vertices = 0;
	nums::uint32 edges = 0;

	nums::uint32 start_from = 0;
	nums::uint32 destination = 0;

	cin >> vertices >> edges;
	cin >> start_from >> destination;

	fmi::Graph graph(vertices);

	for (nums::uint32 i = 0; i < edges; i++)
	{
		nums::uint32 u_vert = 0;
		nums::uint32 v_vert = 0;
		nums::int64 cost = 0;

		cin >> u_vert >> v_vert >> cost;

		graph.AddEdge(u_vert - 1, v_vert - 1, cost);	//we add -1 bec in the graph we count the vertices from 0
	}

	graph.Longest_DijkstraSparse_set(start_from - 1, destination - 1);


	system("pause");
	return 0;
}