#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>

using std::cout;
using std::cin;

namespace fmi
{
	//undirected graph
	class Graph_w_list
	{
	public:

		int _vertices;
		std::vector<std::list<int>> _adj_list;

		Graph_w_list(int N = 0);

		~Graph_w_list() = default;

		bool IsIsolatedVertex(int v);

		void AddEdge(int u, int v);

		void PrintGraph() const;

		void FindConnectivityComponents(std::vector<int>& parts);	//i.e. complete DFS

	protected:
		void Util_Connectivity(int source, bool* visited, int& part_counter);

	};


	fmi::Graph_w_list::Graph_w_list(int N)
		:	_vertices(N),
			_adj_list(N)
	{}

	bool fmi::Graph_w_list::IsIsolatedVertex(int v)
	{
		return _adj_list[v].empty();
	}

	void fmi::Graph_w_list::AddEdge(int u, int v)
	{
		_adj_list[u - 1].push_back(v - 1);
		_adj_list[v - 1].push_back(u - 1);
	}

	void fmi::Graph_w_list::PrintGraph() const
	{
		for (int i = 0; i < _vertices; i++)
		{
			std::cout << "vertex " << i + 1 << " : ";

			for (int vertex : _adj_list[i])
				std::cout << "-> " << vertex + 1;

			std::cout << '\n';

		}
	}

	void fmi::Graph_w_list::FindConnectivityComponents(std::vector<int>& parts)
	{
		bool* visited = new bool[_vertices] {false};
		int part_counter = 0;

		for (int vert = 0; vert < _vertices; vert++)
		{
			if (!visited[vert])
			{
				Util_Connectivity(vert, visited, part_counter);
				parts.push_back(part_counter);
				part_counter = 0;	//for next iteration
			}
		}

		delete[] visited;
	}

	void fmi::Graph_w_list::Util_Connectivity(int source, bool* visited, int& part_counter)
	{
		visited[source] = true;

	//	std::cout << source << ' ';
		if (!IsIsolatedVertex(source))
			part_counter++;

		for (int neigh : _adj_list[source])
		{
			if (!visited[neigh])
				Util_Connectivity(neigh, visited, part_counter);
		}
	}



}


int main()
{
	std::ios_base::sync_with_stdio(false);   //making i/o faster

	int N;

	cin >> N;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	int gi = 0;
	int bi = 0;

	fmi::Graph_w_list graph(2 * N);

	for (int i = 0; i < N; i++)
	{
		cin >> gi >> bi;

		graph.AddEdge(gi, bi);
	}

	graph.PrintGraph();

	std::vector<int> parts_sizes;

	graph.FindConnectivityComponents(parts_sizes);

	int max_component_size = *std::max_element(parts_sizes.begin(), parts_sizes.end());

	int min_component_size = *std::find_if(parts_sizes.begin(), 
											parts_sizes.end(),
											[](int value) {return value > 1;});

	for (int size : parts_sizes)
	{
		if (size > 1)
			min_component_size = std::min(min_component_size, size);
	}


	std::cout << min_component_size << ' ' << max_component_size << '\n';

	std::system("pause");
	return 0;
}
