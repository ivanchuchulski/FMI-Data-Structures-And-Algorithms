#include <iostream>
#include "Graph.hpp"
#include "MST_Graph.hpp"

#include <vector>
#include <set>

using namespace std;



int main() {


	{
		fmi::Graph graph(9);


		graph.AddEdge(0, 1, 4);
		graph.AddEdge(0, 7, 8);
		graph.AddEdge(1, 2, 8);
		graph.AddEdge(1, 7, 11);
		graph.AddEdge(2, 3, 7);
		graph.AddEdge(2, 8, 2);
		graph.AddEdge(2, 5, 4);
		graph.AddEdge(3, 4, 9);
		graph.AddEdge(3, 5, 14);
		graph.AddEdge(4, 5, 10);
		graph.AddEdge(5, 6, 2);
		graph.AddEdge(6, 7, 1);
		graph.AddEdge(6, 8, 6);
		graph.AddEdge(7, 8, 7);

		graph.DijkstraSparse_set(0);
		graph.DijkstraSparse_pq(0);

	}

	{
		mst::Graph graph(4);

		//graph.AddEdge(0, 1, 4);
		//graph.AddEdge(0, 7, 8);
		//graph.AddEdge(1, 2, 8);
		//graph.AddEdge(1, 7, 11);
		//graph.AddEdge(2, 3, 7);
		//graph.AddEdge(2, 8, 2);
		//graph.AddEdge(2, 5, 4);
		//graph.AddEdge(3, 4, 9);
		//graph.AddEdge(3, 5, 14);
		//graph.AddEdge(4, 5, 10);
		//graph.AddEdge(5, 6, 2);
		//graph.AddEdge(6, 7, 1);
		//graph.AddEdge(6, 8, 6);
		//graph.AddEdge(7, 8, 7);	
		
		graph.AddEdge(0, 1, 10);
		graph.AddEdge(1, 2, 15);
		graph.AddEdge(0, 2, 5);
		graph.AddEdge(3, 1, 2);
		graph.AddEdge(3, 2, 40);

		graph.Prim_set();
	//	graph.Prim_pq();

	}



	std::system("pause");
	return 0;
}
