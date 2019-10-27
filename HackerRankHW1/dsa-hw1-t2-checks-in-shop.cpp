#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>

using namespace std;

#define newline '\n';

int main() 
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	int n, k;
	vector<int> productPrices;

	cin >> n >> k;

	for (int i = 0; i < n; i++)
	{
		int price;
		cin >> price;
		productPrices.push_back(price);
	}

	sort(productPrices.begin(), productPrices.end());

	if (k > n)
	{
		cout << accumulate(productPrices.begin(), productPrices.end(), 0) << newline;
		return 0;
	}

	// hacker loop
	//for (int i = n - 1; i - k + 1 >= 0; i -= k)
	//{
	//	productPrices[i - k + 1] = 0;
	//}
	
	// we have to loop backwards, because we null out the least expensive buys
	for (int i = n - k; i >= 0; i-= k)
	{
		productPrices[i] = 0;
	}

	std::cout << accumulate(productPrices.begin(), productPrices.end(), 0) << newline;

 	return 0;
}