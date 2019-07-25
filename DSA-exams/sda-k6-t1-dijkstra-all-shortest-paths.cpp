#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>


using namespace std;

class Graph
{
private:
    int vertices;
    vector<vector<pair<int, long long>>> adj_list;        // pair<neighbour, weight>

public:
    Graph(int vert_count)
        :    vertices(vert_count),  adj_list(vert_count)
    {}

    ~Graph() = default;

    void AddEdge(int u, int v, long long cost)
    {
        adj_list[u].push_back({v, cost});
        adj_list[v].push_back({u, cost});
    }
        
    
    void DisplayAllShortest(int source)
    {
        const long long INF = 11000000000;

        vector<long long> dist(vertices, INF);
        set<pair<long long, int>> que;      //pair<dist_from_source, vertex_label>

        dist[source] = 0;
        que.insert({ 0, source });

        while (!que.empty())
        {
            int current = que.begin()->second;
            que.erase(que.begin());

            for (auto neigh : adj_list[current])
            {
                int to = neigh.first;
                long long cost = neigh.second;

                if (dist[current] + cost < dist[to])
                {
                    que.erase({ dist[to], to });

                    dist[to] = dist[current] + cost;

                    que.insert({ dist[to], to });
                }
            }
        }

        for (int i = 0; i < dist.size();i++)
        {
            if (i == source)        //we dont print the source
                continue;
            
            if (dist[i] == INF)
            {//we dont the unreachable vertices
                cout << -1 << ' ';
            }
            else
            {
                cout << dist[i] << ' ';
            }
        }

    }


};

int main() {
    
    ios_base::sync_with_stdio(false);
    
    int vertices = 0;
    int edges = 0;
    
    cin >> vertices >> edges;

    int u = 0;
    int v = 0;
    long long  cost = 0;
    
    Graph graph(vertices);
    
    for (int i  = 0; i < edges; i++)
    {
        cin >> u >> v >> cost;
        
        graph.AddEdge(u - 1, v - 1, cost);    
    }
    
    int start_from = 0;
    
    cin >> start_from;
    
    graph.DisplayAllShortest(start_from -1);
    
    return 0;
}
