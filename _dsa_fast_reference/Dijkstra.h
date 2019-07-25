
class Graph
{
private:
	int vertices;
	vector<vector<pair<int, int>>> adj;		//	pair<neighbour, weight>

public:
	Graph(int vert_count) :	vertices(vert_count), adj(vert_count)
	{}

	void AddEdge(int u, int v, int w)
	{
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}
		
	void Dijkstra(int source)
	{
		const int INF = 1000000;
		vector<int> dist(vertices, INF);
		vector<int> pred(vertices, -1);
		set<pair<int, int>> que;		// pair<distance_from_source, vertex_index>

		dist[source] = 0;
		que.insert({ dist[source], source });

		while (!que.empty())
		{
			int current = que.begin()->second;
			que.erase(que.begin());

			for (auto neigh : adj[current])
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

	//	for (int i = 0; i < dist.size();i++)
	//		cout << "vertex " << i << " distance : " <<  dist[i] << '\n';

	}

	vector<int> RestorePath(int source, int target, vector<int>& pred)
	{
		vector<int> path;

		for (int vert = target; vert != source; vert = pred[vert])
			path.push_back(vert);

		path.push_back(source);

		return path;
	}

};

