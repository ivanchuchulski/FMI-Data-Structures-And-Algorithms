#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;
using sock_t = unsigned long long;

#define newline '\n'

struct SockPair
{
	sock_t shorter;
	sock_t longer;

	SockPair(sock_t sh, sock_t lon)
		:	shorter(sh),
			longer(lon)
	{}

	sock_t Length() const
	{
		return longer - shorter;
	}

	friend bool operator<(const SockPair& p1, const SockPair& p2)
	{
		if (p1.Length() == p2.Length())
		{
			return p1.shorter < p2.shorter;
		}
		else
		{
			return p1.Length() < p2.Length();
		}
	}
};

int main() 
{
	std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr);

	int numberOfSocks;
	int dayNumber;
	vector<sock_t> socks;
	vector<SockPair> pairings;

	cin >> numberOfSocks >> dayNumber;

	for (int i = 0; i < numberOfSocks; i++)
	{
		sock_t val = 0;
		cin >> val;
		socks.emplace_back(val);
	}

	// creating each possible pairing
	pairings.reserve((numberOfSocks * (numberOfSocks - 1)) / 2);
	for (int i = 0; i < numberOfSocks - 1; i++)
	{
		for (int j = i + 1; j < numberOfSocks; j++)
		{
			pairings.emplace_back(socks[i], socks[j]);
		}
	}

	// sorting the pairings
	std::sort(pairings.begin(), pairings.end(), [](SockPair& p1, SockPair& p2) {return p1 < p2; });

	// printing the required pair
	cout << pairings[dayNumber - 1].shorter << ' ' << pairings[dayNumber - 1].longer;

	return 0;
}