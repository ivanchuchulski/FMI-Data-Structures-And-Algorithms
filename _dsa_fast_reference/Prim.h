
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
	vector <vector<Edge>> adj;

public:
	Graph(int vert_count) :	vertices(vert_count), adj(vert_count)
	{}

	void AddEdge(int u, int v, int w)
	{
		adj[u].push_back({ v, w });
		adj[v].push_back({ u, w });
	}

	void Prim(int source)
	{
		int total_weight = 0;
		const int INF = 1000000;

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

		//	if (key[current].to != -1)
		//		cout << current << ' ' << key[current].to << '\n';

			for (Edge& edg : adj[current])
			{
				int to = edg.to;
				int price_curr = edg.cost;
				int old_price = key[edg.to].cost;

				if (price_curr < old_price && !inMST[to])
				{
					que.erase({ to, old_price });

					key[to] = { current, price_curr };

					que.insert({ to, price_curr });
				}
			}
		}

	//	cout << total_weight << '\n';

		delete[] inMST;
	}

};

