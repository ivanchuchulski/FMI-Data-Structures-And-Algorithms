#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int main() {

	ios_base::sync_with_stdio(false);

	int arr[] = { 7, 10, 4, 3, 20, 15 };		//3, 4, 7, 10, 15, 20
	int size = 6;
	int k = 3;

	priority_queue<int, vector<int>, greater<int>> min_heap;
	priority_queue<int> max_heap;		//for k-th largest we use max_heap
	for (int i = 0; i < size; i++)
		min_heap.push(arr[i]);

	while (k > 1)
	{
		min_heap.pop();
		k--;
	}

	cout << min_heap.top() << '\n';


	system("pause");
	return 0;
}