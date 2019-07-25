
class Graph
{
public:

	int vertices;
	vector<vector<int>> adj_list;

	Graph(int N) : vertices(N), adj_list(N)
	{}

	void AddEdge(int u, int v)
	{
		adj_list[u].push_back(v);
		adj_list[v].push_back(u);
	}


	void BFS(int source)
	{
		bool* visited = new bool[vertices] {false};
		std::queue<int> que;

		visited[source] = true;
		que.push(source);

		while (!que.empty())
		{
			int curr = que.front();
			que.pop();

			for (int neigh : adj_list[curr])
			{
				if (!visited[neigh])
				{
					visited[neigh] = true;
					que.push(neigh);
				}
			}
		}

		delete[] visited;
	}



	void Util_DFS(int source, bool* visited)
	{
		visited[source] = true;

		for (int neigh : adj_list[source])
		{
			if (!visited[neigh])
				Util_DFS(neigh, visited);
		}
	}

	void DFS(int source)
	{
		bool* visited = new bool[vertices] {false};

		Util_DFS(source, visited);
	}

	void CompleteDFS()
	{
		bool* visited = new bool[vertices] {false};

		for (int i = 0; i < vertices; i++)
		{
			if (!visited[i])
				Util_DFS(i, visited);
		}

	}

	bool Util_HasCycle(int vertex, bool* visited, int parent)
	{
		visited[vertex] = true;

		for (int neigh : adj_list[vertex])
		{
			if (!visited[neigh])
			{
				if (Util_HasCycle(neigh, visited, vertex))
					return true;
			}

			else
			{
				if (neigh != parent)
					return true;
			}
		}

		return false;
	}

	bool HasCycle()
	{
		bool* visited = new bool[vertices] {false};

		for (int vert = 0; vert < vertices; vert++)
		{
			if (!visited[vert])
			{
				if (Util_HasCycle(vert, visited, -1))
					return true;
			}
		}

		return false;
	}

	void Util_TopologicalSort(int current, bool* visited, std::stack<int>& st)
	{
		visited[current] = true;

		for (int neigh : adj_list[current])
		{
			if (!visited[neigh])
				Util_TopologicalSort(neigh, visited, st);
		}

		st.push(current);
	}

	void TopologicalSort()
	{
		bool* visited = new bool[vertices] {false};
		std::stack<int> st;

		for (int vert = 0; vert < vertices; vert++)
		{
			if (!visited[vert])
				Util_TopologicalSort(vert, visited, st);
		}

		//while (!st.empty())
		//{
		//	std::cout << st.top() << ' ';
		//	st.pop();
		//}
	}

	bool IsBipartite(int source)
	{
		int red = 1;
		int blue = 0;
		int no_color = -1;
		int* color_arr = new int[vertices] { -1 };
		std::queue<int> que;

		color_arr[source] = red;
		que.push(source);

		while (!que.empty())
		{
			int current = que.front();
			que.pop();

			for (int neigh : adj_list[current])
			{
				if (color_arr[neigh] == no_color)
				{
					color_arr[neigh] = (color_arr[current] == red) ? blue : red;			//assign the oposite color of current
					que.push(neigh);
				}
				else
				{
					if (color_arr[neigh] == color_arr[current])
						return false;
				}
			}
		}

		return true;
	}

	bool PathExists(int start, int target)
	{
		bool* visited = new bool[vertices] {false};
		std::queue<int> que;

		que.push(start);
		visited[start] = true;

		while (!que.empty())
		{
			int current = que.front();
			que.pop();

			if (current == target)
				return true;

			for (int neigh : adj_list[current])
			{
				if (!visited[neigh])
				{
					visited[neigh] = true;
					que.push(neigh);
				}
			}
		}

		return false;	//path doesnt exist
	}

	void FindAllShortestPaths(int source, std::vector<int>& distances, int edge_weight)
	{
		std::queue<int> que;
		bool* visited = new bool[vertices] { false };
		std::vector<int> pred(vertices, -1);

		visited[source] = true;
		distances[source] = 0;
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
					pred[neigh] = current;

					visited[neigh] = true;
					que.push(neigh);
				}
			}
		}

		delete[] visited;
	}

	void restore_path(int source, int targ, vector<int> const& pred)
	{
		vector<int> path;

		for (int v = targ; v != source; v = pred[v])
			path.push_back(v);

		path.push_back(source);

		reverse(path.begin(), path.end());
	}

};
