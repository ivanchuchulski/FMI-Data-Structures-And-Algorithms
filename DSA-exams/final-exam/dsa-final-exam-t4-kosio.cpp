#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAXV = 10024;

const char NOT_SEEN = 0;
const char IN_STACK = 1;
const char COMPLETE = 2;

vector<int> adj[MAXV];
char state[MAXV];

void reset()
{
	for (int i = 0; i < MAXV; i++) adj[i].clear();
	memset(state, 0, MAXV);
}

void input()
{
	int nv, ne;
	cin >> nv >> ne;
	int a, b, c;
	for (int i = 0; i < ne; i++)
	{
		cin >> a >> b >> c;
		a--;
		b--;
		adj[a].push_back(b);
	}
}

bool dfs(int v)
{
	state[v] = IN_STACK;
	for (int nv : adj[v])
	{
		if (state[nv] == IN_STACK) return true;
		if (state[nv] == NOT_SEEN) if (dfs(nv)) return true;
	}
	state[v] = COMPLETE;
	return false;
}

bool cycle()
{
	for (int i = 0; i < MAXV; i++) if (state[i] == NOT_SEEN && dfs(i)) return true;
	return false;
}

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		input();
		if (cycle()) cout << "true ";
		else cout << "false ";
		reset();
	}
	cout << endl;
	return 0;
}