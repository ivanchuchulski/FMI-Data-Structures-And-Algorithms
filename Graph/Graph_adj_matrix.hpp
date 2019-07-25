#pragma once


#include <iostream>
#include <vector>
#include <list>
#include <queue>


namespace fmi
{

	//undirected graph
	class Graph_w_matrix
	{
	public:

		int _vertices;
		std::vector<std::vector<int>> _adj_matrix;

		Graph_w_matrix(int N);

		~Graph_w_matrix();

		inline bool HaveEdge(int u, int v)
		{
			return _adj_matrix[u][v] != 0;
		}


		void AddEdge(int u, int v);

		void PrintGraph() const;

		void BFS(int source);

		void DFS(int source);

		void CompleteDFS();	//works on disconected graphs

		bool HasCycle();

	protected:
		void Util_DFS(int source, bool* visited);

		bool Util_HasCycle(int vertex, bool* visited, int parent);

	};


	fmi::Graph_w_matrix::Graph_w_matrix(int N)
		:	_vertices(N),
			_adj_matrix(N)
	{
		for (int i = 0; i < N; i++)
			_adj_matrix[i].resize(N);
	}


	fmi::Graph_w_matrix::~Graph_w_matrix()
	{}

	void fmi::Graph_w_matrix::AddEdge(int u, int v)
	{
		_adj_matrix[u][v] = 1;
		_adj_matrix[v][u] = 1;
	}

	void fmi::Graph_w_matrix::PrintGraph() const
	{
		for (int i = 0; i < _vertices; i++)
		{
			std::cout << "vertex " << i << " : ";
			for (int j = 0; j < _vertices; j++)
			{
				std::cout << _adj_matrix[i][j] << ' ';
			}

			std::cout << '\n';
		}
	}


	void fmi::Graph_w_matrix::BFS(int source)
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

			for (int i = 0; i < _vertices; i++)
			{
				if (HaveEdge(curr, i) && !visited[i])	//neighbour && !visited <=> (_adj_matrix[curr][i] == 1 && !visited[i])
				{
					visited[i] = true;
					que.push(i);
				}
			}
		}

		delete[] visited;
	}

	void fmi::Graph_w_matrix::CompleteDFS()
	{
		bool* visited = new bool[_vertices] {false};

		for (int vert = 0; vert < _vertices; vert++)
		{
			if (!visited[vert])
				Util_DFS(vert, visited);
		}

		delete[] visited;
	}

	void fmi::Graph_w_matrix::DFS(int source)
	{
		bool* visited = new bool[_vertices] {false};

		Util_DFS(source, visited);

		delete[] visited;
	}

	void fmi::Graph_w_matrix::Util_DFS(int source, bool * visited)
	{
		visited[source] = true;

		std::cout << source << ' ';

		for (int i = 0; i < _vertices; i++)
		{
			if (HaveEdge(source, i) && !visited[i])		//neighbour && !visited
			{
				Util_DFS(i, visited);
			}
		}
	}



	bool fmi::Graph_w_matrix::Util_HasCycle(int current, bool* visited, int parent)
	{
		visited[current] = true;

		for (int v = 0; v < _vertices; v++)
		{
			if (HaveEdge(current, v))
			{
				if (!visited[v])
				{
					if (Util_HasCycle(v, visited, current))
						return true;
				}

				else
				{
					if (parent != v)
						return true;
				}
			}
		}

		return false;
	}

	bool fmi::Graph_w_matrix::HasCycle()
	{
		bool* visited = new bool[_vertices] { false };

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

}