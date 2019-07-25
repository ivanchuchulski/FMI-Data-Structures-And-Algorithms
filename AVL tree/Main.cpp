#include <iostream>
#include <queue>
#include <vector>
#include <functional>

//#include "AVL.hpp"
#include "AVLTree.hpp"

using namespace std;


int main() {



	//{
	//	priority_queue<double, vector<double>, greater<double>> que;

	//	for (double i = 0; i < 5; i++)
	//		que.push(i);

	//	while (!que.empty())
	//	{
	//		cout << que.top() << '\n';
	//		que.pop();

	//	}
	//}

	{

		//AVL a1;

		//a1._root = a1.Insert(a1._root, 9);
		//a1._root = a1.Insert(a1._root, 5);
		//a1._root = a1.Insert(a1._root, 10);
		//a1._root = a1.Insert(a1._root, 0);
		//a1._root = a1.Insert(a1._root, 6);
		//a1._root = a1.Insert(a1._root, 11);
		//a1._root = a1.Insert(a1._root, -1);
		//a1._root = a1.Insert(a1._root, 1);
		//a1._root = a1.Insert(a1._root, 2);

		//a1.Preorder(a1._root);
		//cout << '\n';

		//a1._root = a1.Delete(a1._root, 10);

		//a1.Preorder(a1._root);
		//cout << '\n';
	}

	{
		AVLTree a2;

		 a2.Insert(a2._root, 9);
		 a2.Insert(a2._root, 7);
		 a2.Insert(a2._root, 10);
		 a2.Insert(a2._root, 3);
		 a2.Insert(a2._root, 8);
		 a2.Insert(a2._root, 11);
		 a2.Insert(a2._root, 2);
		 a2.Insert(a2._root, 4);
		 a2.Insert(a2._root, 5);	//causes LR rotation

		 a2.Preorder(a2._root);
		 cout << '\n';

		 a2.Delete(a2._root, 10);

		 a2.Preorder(a2._root);
		 cout << '\n';

	}



	system("pause");
	return 0;
}