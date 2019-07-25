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

void PrintLabirynth(int** lab, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << lab[i][j] << ' ';
        }
        cout << '\n';
    }
}

bool ValidPosition(int maze_rows, int maze_cols, int x, int y)
{
    return (x >= 0) && (y >= 0) && (x < maze_rows) && (y < maze_cols);
}

int FindShortestDistance(int** maze, int rows, int cols, Point& source, Point& destination)
{
    //check for valid starting and end point
    if (maze[source._x][source._y] == 1 || maze[destination._x][destination._y] == 1)
        return -1;

    //movement in the maze : up, left, right, down from the current position
    const int possible_movements = 4;
    int row_move[possible_movements] = {-1, 0, 0, 1};
    int column_move[possible_movements] = {0, -1, 1, 0};

    std::queue<Node> nodes;

    //2d array for marking visited points
    bool* visited_positions = new bool[rows * cols];

    for    (int i = 0; i < rows * cols; i++)
        visited_positions[i] = false;

    visited_positions[source._x * cols + source._y] = true;

    Node starting{source, 0};    //distance from source to source is 0
    nodes.push(starting);

    while (!nodes.empty())
    {
        Node current_node{nodes.front()};

        Point curr_point{nodes.front()._point};

        if (curr_point._x == destination._x && curr_point._y == destination._y)
        {
            delete[] visited_positions;        //free dynamic memory
            return current_node._dist_from_source;
        }

        nodes.pop();

        for (int k = 0; k < possible_movements; k++)
        {
            int row = curr_point._x + row_move[k];
            int col = curr_point._y + column_move[k];

            Point neighbor{ curr_point._x + row_move[k],  curr_point._y + column_move[k]};

            if (ValidPosition(rows, cols, neighbor._x, neighbor._y) && 
                                maze[neighbor._x][neighbor._y] == 0 && 
                                    visited_positions[neighbor._x * cols + neighbor._y] == false)
            {
                visited_positions[neighbor._x * cols + neighbor._y] = true;
                nodes.push({neighbor, current_node._dist_from_source + 1});
            }
        }

    }


    delete[] visited_positions;
    //if there is no path
    return -1;
}


int main () {

    int rows;
    int cols;
    int queries;
    int** labyrinth = nullptr;

    cin >> rows >> cols >> queries;

    labyrinth = new int*[rows];
    for (int i = 0; i < rows; i++)
    {
        labyrinth[i] = new int[cols];

        for (int j = 0; j < cols; j++)
            cin >> labyrinth[i][j];
    }

//    PrintLabirynth(labyrinth, rows, cols);

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
    for (int i = 0; i < rows; i++) { delete[] labyrinth[i]; }
    delete[] labyrinth;


    std::system("pause");
    return 0;
}