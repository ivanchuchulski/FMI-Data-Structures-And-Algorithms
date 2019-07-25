#include <iostream>
#include <vector>
 
using namespace std;
 
const int MAXV = 128;
const int MAXLEN = 16000;
 
struct Edge
{
    int to, cost;
};
 
vector<Edge> adj[MAXV];
bool used[MAXV];
int lenCount[MAXLEN];
 
void dfs(int v, int cost, int len, int maxLen)
{
    if (len == maxLen)
    {
        lenCount[cost]++;
        return;
    }
 
    for (Edge & e : adj[v])
    {
        int nv = e.to;
        if (used[nv]) continue;
        used[nv] = true;
        dfs(nv, cost + e.cost, len + 1, maxLen);
        used[nv] = false;
    }
}
 
int main()
{
    int nv, ne;
    cin >> nv >> ne;
 
    int a, b, c;
    for (int i = 0; i < ne; i++)
    {
        cin >> a >> b >> c;
        adj[a].push_back({ b,c });
    }
 
    int k;
    cin >> k;
 
    for (int i = 0; i < nv; i++)
    {
        used[i] = true;
        dfs(i, 0, 0, k);
        used[i] = false;
    }
 
    int bestCount = 0;
    int bestLen = -1;
 
    for (int i = MAXLEN - 1; i >= 0; i--)
    {
        if (lenCount[i] > bestCount)
        {
            bestCount = lenCount[i];
            bestLen = i;
        }
    }
 
    cout << bestLen << endl;
 
    return 0;
}