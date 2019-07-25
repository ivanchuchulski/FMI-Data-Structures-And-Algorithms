#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>

using sock_t = unsigned long long;

struct SockPair
{
	sock_t shorter;
	sock_t longer;

	SockPair(sock_t sh, sock_t lon)
		:	shorter(sh),	longer(lon)
	{}

	sock_t Length() const
	{
		return longer - shorter;
	}

	friend std::ostream& operator<<(std::ostream& outS, const SockPair& p)
	{
		outS << p.shorter << ' ' << p.longer << "; len : " << p.Length() << '\n';

		return outS;
	}

	friend bool operator<(const SockPair& p1,const SockPair& p2)
	{
		if (p1.Length() < p2.Length())
			return true;
		else if (p1.Length() == p2.Length())
			return p1.shorter < p2.shorter;
		else
			return false;
	}
};

bool ValidateInput(int n, int k)
{
	if (n < 3 || n > 1000)
		return false;

	else if (k < 1 || k >(n * (n - 1)) / 2)
		return false;

	else
		return true;
}

void Print(const sock_t* arr, size_t len)
{
	for (size_t i = 0; i < len; i++)
		std::cout << arr[i] << ' ';

	std::cout << '\n';
}

void PrintVector(const std::vector<SockPair>& vec)
{
	for (auto& v : vec)
		std::cout << v;

	std::cout << '\n';
}

void PrintKPair(int k, std::vector<SockPair>& vec)
{
	if (k <= vec.size())
		std::cout << vec[k - 1].shorter << ' ' << vec[k - 1].longer << '\n';
}


int main() {
	
	int n, k;
	sock_t* socks = nullptr;

	std::cin >> n >> k;

	bool valid = ValidateInput(n, k);

	if (!valid)
		return 0;

	socks = new sock_t[n] {};

	for (size_t i = 0; i < n; i++)
		std::cin >> socks[i];

	Print(socks, n);
	std::vector<SockPair> pairings;
	pairings.reserve((n * (n - 1)) / 2);

	for (size_t i = 0; i < n - 1; i++)
	{
		for (size_t j = i + 1; j < n; j++)
		{
			pairings.emplace_back(socks[i], socks[j]);
		}
	}

	//free memory
	delete[] socks;

	PrintVector(pairings);

	//std::sort(pairings.begin(), pairings.end(), [](SockPair& p1, SockPair& p2)
	//	{
	//		if (p1.Length() < p2.Length())
	//			return true;
	//		else if (p1.Length() == p2.Length())
	//			return p1.shorter < p2.shorter;
	//		else
	//			return false;
	//	}
	//);

	std::sort(pairings.begin(), pairings.end(), [](SockPair& p1, SockPair& p2) {return p1 < p2; });

	PrintVector(pairings);

	PrintKPair(k, pairings);

	std::system("pause");
	return 0;
}