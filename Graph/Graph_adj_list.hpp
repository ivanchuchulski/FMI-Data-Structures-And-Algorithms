#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include <stack>


namespace fmi
{
	struct Node
	{
		int _vertex_label;

		Node(int vert)
			: _vertex_label(vert)
		{}

		bool operator==(const Node& rhs) const
		{
			return _vertex_label == rhs._vertex_label;
		}

		bool operator!=(const Node& rhs) const
		{
			return !(*this == rhs);
		}
	};


	//undirected graph
	class Graph_w_list
	{
	public:

		int _vertices;	
		std::vector<std::list<int>> _adj_list;

		Graph_w_list(int N = 0);

		~Graph_w_list() = default;


		void AddEdge(int u, int v);

		void PrintGraph() const;

		void BFS(int source);

		void DFS(int source);

		void CompleteDFS();	//works on disconected graphs

		bool HasCycle();

		void TopologicalSort();			// !!must be used on a Directed Acyclic Graph kind of DFS,

		bool IsBipartite(int source);	// !!must be used on a Directed Acyclic Graph

		bool PathExists(int start, int target);

		void FindAllShortestPaths(int source, std::vector<int>& distances, const int edge_weight);

	protected:
		void Util_DFS(int source, bool* visited);

		bool Util_HasCycle(int vertex, bool* visited, int parent);

		void Util_TopologicalSort(int current, bool* visited, std::stack<int>& st);
	};


	fmi::Graph_w_list::Graph_w_list(int N)
		:	_vertices(N),
			_adj_list(N)
	{}

	void fmi::Graph_w_list::AddEdge(int u, int v)
	{
		_adj_list[u].push_back(v);
		_adj_list[v].push_back(u);
	}

	void fmi::Graph_w_list::PrintGraph() const
	{
		for (int i = 0; i < _vertices; i++)
		{
			std::cout << "vertex " << i << " : ";

			for (int node : _adj_list[i])
				std::cout << "-> " << node;

			std::cout << '\n';

		}
	}

	void fmi::Graph_w_list::BFS(int source)
	{
		bool* visited = new bool[_vertices] {false};

		std::queue<int> que;

		visited[source] = true;
		que.push(source);

		while (!que.empty())
		{
			int curr = que.front();
			que.pop();

			std::cout << curr << ' ';

			for (int neigh : _adj_list[curr])
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

	void fmi::Graph_w_list::Util_DFS(int source, bool* visited)
	{
		visited[source] = true;

		std::cout << source << ' ';

		for (int neigh : _adj_list[source])
		{
			if (!visited[neigh])
				Util_DFS(neigh, visited);
		}
	}

	void fmi::Graph_w_list::DFS(int source)
	{
		bool* visited = new bool[_vertices] {false};

		Util_DFS(source, visited);

		delete[] visited;
	}

	void fmi::Graph_w_list::CompleteDFS()
	{
		bool* visited = new bool[_vertices] {false};
		std::fill(visited, visited + _vertices, false);

		for (int i = 0; i < _vertices; i++)
		{
			if (!visited[i])
				Util_DFS(i, visited);
		}

		delete[] visited;
	}

	bool fmi::Graph_w_list::Util_HasCycle(int vertex, bool* visited, int parent)
	{
		visited[vertex] = true;

		for (int neigh : _adj_list[vertex])
		{
			if (!visited[neigh])
			{
				if (Util_HasCycle(neigh, visited, vertex))
					return true;
			}

			else
			{
				//if the graph is acyclic then the only visited neightbour of the vertex should be its parent
				//if that is not the case, then the graph has a cycle
				if (neigh != parent)	
					return true;
			}
		}

		return false;
	}

	bool fmi::Graph_w_list::HasCycle()
	{
		bool* visited = new bool[_vertices] {false};

		for (int vert = 0; vert < _vertices; vert++)
		{
			if (!visited[vert])
			{
				if (Util_HasCycle(vert, visited, -1))
				{
					delete[] visited;
					return true;
				}

			}
		}

		delete[] visited;
		return false;
	}


	void fmi::Graph_w_list::Util_TopologicalSort(int current, bool * visited, std::stack<int>& st)
	{
		visited[current] = true;

		for (int neigh : _adj_list[current])
		{
			if (!visited[neigh])
				Util_TopologicalSort(neigh, visited, st);
		}

		st.push(current);
	}

	void fmi::Graph_w_list::TopologicalSort()
	{
		bool* visited = new bool[_vertices] {false};

		std::stack<int> st;

		for (int vert = 0; vert < _vertices; vert++)
		{
			if (!visited[vert])
				Util_TopologicalSort(vert, visited, st);
		}

		while (!st.empty())
		{
			std::cout << st.top() << ' ';
			st.pop();
		}
	}

	bool fmi::Graph_w_list::IsBipartite(int source)
	{
		enum class Colors : int
		{
			no_color = -1,
			color = 1
		};

		Colors* color_arr = new Colors[_vertices];
		std::fill(color_arr, color_arr + _vertices, Colors::no_color);

		color_arr[source] = Colors::color;

		std::queue<int> que;

		que.push(source);

		while (!que.empty())
		{
			int current = que.front();
			que.pop();

			for (int neigh : _adj_list[current])
			{
				if (neigh == current) // i.e. we have a self-loop
					return false;

				if (color_arr[neigh] == Colors::no_color)
				{
					//assign the oposite color of current
					color_arr[neigh] = (color_arr[current] == Colors::color) ? Colors::no_color : Colors::color;
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

	bool fmi::Graph_w_list::PathExists(int start, int target)
	{
		bool* visited = new bool[_vertices] {false};
		std::queue<int> que;

		que.push(start);
		visited[start] = true;

		while (!que.empty())
		{
			int current = que.front();
			que.pop();

			if (current == target)
			{
				delete[] visited;
				return true;
			}

			for (int neigh : _adj_list[current])
			{
				if (!visited[neigh])
				{
					visited[neigh] = true;
					que.push(neigh);
				}
			}

		}

		delete[] visited;
		return false;	//path doesnt exist
	}

	void fmi::Graph_w_list::FindAllShortestPaths(int source, std::vector<int>& distances, const int edge_weight)
	{
		std::queue<int> que;
		bool* visited = new bool[_vertices] { false };
		std::vector<int> predecessors(_vertices, -1);	// predecessor[i] stores predecessor of i-th vertex in the shortest path

		visited[source] = true;
		distances[source] = 0;
		que.push(source);

		// standard BFS algorithm 
		while (!que.empty()) 
		{
			int current = que.front();
			que.pop();

			for (int neigh : _adj_list[current]) 
			{
				if (!visited[neigh]) 
				{
					distances[neigh] = distances[current] + edge_weight;

					predecessors[neigh] = current;

					visited[neigh] = true;
					que.push(neigh);
				
				//if we search for a destination
				//	if (neigh== destination)
				//		{...}
				}
			}
		}

		//if we have to do some action with the predecessors array
		//...

		delete[] visited;
	}

}