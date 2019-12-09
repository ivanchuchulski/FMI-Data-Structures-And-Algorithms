#include <iostream>

#include "Graph_adj_list.hpp"
#include "Graph_adj_matrix.hpp"


int main() {


	{
		fmi::Graph_w_list graph_list(4);


		graph_list.AddEdge(0, 1);
		graph_list.AddEdge(0, 2);
		graph_list.AddEdge(1, 2);
		graph_list.AddEdge(2, 3);

		graph_list.PrintGraph();

		graph_list.BFS(1);
		std::cout << '\n';

		graph_list.DFS(1);
		std::cout << '\n';

		std::cout << graph_list.HasCycle() << '\n'; 

	}

	{
		//graph_matr.AddEdge(0, 1);
		//graph_matr.AddEdge(0, 4);
		//graph_matr.AddEdge(1, 2);
		//graph_matr.AddEdge(1, 3);
		//graph_matr.AddEdge(1, 4);
		//graph_matr.AddEdge(2, 3);
		//graph_matr.AddEdge(3, 4);

		fmi::Graph_w_matrix graph_matr(4);

		graph_matr.AddEdge(0, 1);
		graph_matr.AddEdge(0, 2);
		graph_matr.AddEdge(1, 2);
		graph_matr.AddEdge(2, 3);


		graph_matr.PrintGraph();

		graph_matr.BFS(2);
		std::cout << '\n';

		graph_matr.DFS(2);
		std::cout << '\n';

		std::cout << graph_matr.HasCycle() << '\n';

	}

	{
		//testing for Directed Acyclic Graph, change the AddEdge()
		//fmi::Graph_w_list g(6);

		//g.AddEdge(5, 2);
		//g.AddEdge(5, 0);
		//g.AddEdge(4, 0);
		//g.AddEdge(4, 1);
		//g.AddEdge(2, 3);
		//g.AddEdge(3, 1);

		//g.TopologicalSort();
	}





	std::system("pause");
	return 0;
}