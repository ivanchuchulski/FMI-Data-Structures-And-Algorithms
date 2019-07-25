#include <iostream>
#include <queue>
#include <any>

#include "Heap.hpp"
#include "TemplateHeap.hpp"
#include "MinHeap_MaxHeap.hpp"

using std::cout;
using std::cin;


int main() {

//	Heap myheap(Smaller);

	MinHeap<int> min_heap;
	MaxHeap<int> max_heap;

	//auto* bigger = min_heap.Size() > max_heap.Size() ? min_heap : max_heap;

	std::priority_queue<int> maxi;
	std::priority_queue<int, std::vector<int>, std::greater<int>> mini;

	try
	{
		min_heap.GetTop();
	}
	catch (const std::exception& exc)
	{
		cout << exc.what() << '\n';
	}

	min_heap.Insert(3);
	min_heap.Insert(2);
	min_heap.Insert(15);

	cout << min_heap.GetTop() << '\n';

	cout << min_heap.ExtractTop() << '\n';
	cout << min_heap.GetTop() << '\n';



	std::system("pause");
	return 0;
}