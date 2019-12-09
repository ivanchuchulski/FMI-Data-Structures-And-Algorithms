#include <iostream>
#include <cstdlib>

#include <forward_list>
//#include "ForwardListTailless.h"
#include "ForwardList.h"

using std::cout;
using std::cin;


ForwardList Merge(ForwardList& list1, ForwardList& list2)
{
	if (list1.Empty() && list2.Empty())
		return ForwardList();

	size_t element_count = list1.Size() + list2.Size();

	ForwardList output;

	Node* left_ptr = list1.Begin();
	size_t l_indx = 0;
	Node* right = list2.Begin();
	size_t r_copied = 0;

	for (size_t i = 0; i < element_count; i++)
	{
		if (l_indx > list1.Size() - 1)
		{
			output.PushBack(right->_data);
			right = right->_next;
			l_indx++;
		}
		else if (r_copied > list2.Size() - 1)
		{
			output.PushBack(left_ptr->_data);
			left_ptr = left_ptr->_next;
			l_indx++;
		}

		else if (left_ptr->_data <= right->_data)
		{
			output.PushBack(left_ptr->_data);
			left_ptr = left_ptr->_next;
			l_indx++;
		}

		else
		{
			output.PushBack(right->_data);
			right = right->_next;
			r_copied++;
		}
	}


	return output;
}


int main() {

	//ForwardList list1, list2;
	//list1.PushBack(1);
	//list1.PushBack(7);
	//list1.PushBack(9);
	//list2.PushBack(5);
	//list2.PushBack(6);
	//ForwardList l3 = Merge(list1, list2);
	//l3.PrintList();

	//ForwardList test_list;

	//for (int i = 0; i < 4; i++)
	//	test_list.PushBack(i + 1);

	//test_list.PrintList();

	//test_list.InsertAt(8, 3);

	//test_list.PrintList();

	//test_list.DeleteAt(4);

	//test_list.PrintList();

	ForwardList lis;

	lis.PushFront(1);
	lis.PushFront(2);
	lis.PushFront(3);
	lis.PushFront(4);
	lis.Reverse_v2();

	lis.PrintList();

	std::system("pause");
	return 0;
}