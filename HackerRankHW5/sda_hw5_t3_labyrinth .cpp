#include <iostream>
#include <queue>
#include <vector>

using std::cout;
using std::cin;


struct Point
{
	int _x;
	int _y;
};

struct Node
{
	Point _point;
	int _dist_from_source;
};


bool ValidPosition(int maze_rows, int maze_cols, int x, int y)
{
	return (x >= 0) && (y >= 0) && (x < maze_rows) && (y < maze_cols);
}

int FindShortestDistance(int* maze, int rows, int cols, Point& source, Point& destination)
{
	//check for valid starting and end point
	if (maze[source._x * cols + source._y] == 1 || maze[destination._x * cols + destination._y] == 1)
		return -1;

	//movement in the maze : up, left, right, down from the current position
	const int directions = 4;
	int row_move[directions] = {-1, 0, 0, 1};
	int column_move[directions] = {0, -1, 1, 0};

	std::queue<Node> visited;

	//2d array for marking visited points := false - not visited, true - visited
	bool* pos_marker = new bool[rows * cols];

	for	(int i = 0; i < rows * cols; i++) { pos_marker[i] = false; }	//mark all positions as not visited

	visited.push({source, 0});								//distance from source to source is 0
	pos_marker[source._x * cols + source._y] = true;		//mark starting point as visited

	while (!visited.empty())
	{
		Node current{visited.front()};

		if (current._point._x == destination._x && current._point._y == destination._y)
		{
			delete[] pos_marker;		//free dynamic memory
			return current._dist_from_source;
		}

		visited.pop();

		for (int k = 0; k < directions; k++)
		{
			int row = current._point._x + row_move[k];
			int col = current._point._y + column_move[k];

			Point neighbor{ current._point._x + row_move[k],  current._point._y + column_move[k]};

			if (ValidPosition(rows, cols, neighbor._x, neighbor._y) && 
								maze[neighbor._x * cols + neighbor._y] == 0 && 
								pos_marker[neighbor._x * cols + neighbor._y] == false)
			{
				visited.push({neighbor, current._dist_from_source + 1});
				pos_marker[neighbor._x * cols + neighbor._y] = true;
			}
		}
	}


	delete[] pos_marker;
	//if there is no path
	return -1;
}

void PrintLabyrinth(int* labyr, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << labyr[i * cols + j] << ' ';
		}
		cout << '\n';
	}
}


int main () {

	int rows;
	int cols;
	int queries;
	int* labyrinth = nullptr;

	cin >> rows >> cols >> queries;

	labyrinth = new int[rows * cols];

	for (int i = 0; i < rows; i++)
		for (int j= 0; j < cols; j++)
			cin >> labyrinth[i * cols + j];

	PrintLabyrinth(labyrinth, rows, cols);

	std::vector<int> distances;
	Point starting_point{ 0, 0 };
	Point destination {0, 0};

	distances.reserve(queries);

	for (int i = 0; i < queries; i++)
	{
		int x = 0;
		int y = 0;

		cin >> x >> y;
		destination._x = x;
		destination._y = y;

		distances.push_back(FindShortestDistance(labyrinth, rows, cols, starting_point, destination));
	}

	//output
	for (int& dist : distances)
		cout << dist << '\n';


	//free memory
	delete[] labyrinth;

	std::system("pause");
	return 0;
}