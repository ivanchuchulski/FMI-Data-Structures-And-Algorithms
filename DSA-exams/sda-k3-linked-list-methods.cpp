#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

struct Node 
{
	int data;
	Node* next;
};

class LinkedList 
{
private:
	Node* head;
	Node* tail;
	int size;

public:
	LinkedList() : head(nullptr), tail(nullptr), size(0) {}

	~LinkedList() 
	{
		if (Empty())
			return;

		Node* destoy = head;
		while (head != nullptr)
		{
			destoy = head;
			head = head->next;
			delete destoy;
		}
		head = tail = nullptr;
		size = 0;
	}

	bool Empty() const { return head == nullptr; }
	int Size() { return size; }

	void PushBack(int value)
	{
		Node* entry = new Node{value, nullptr};
		size++;

		if (Empty()) { head = tail = entry; return; }

		tail->next = entry;
		tail = entry;
	}

	void PushFront(int value)
	{
		Node* entry = new Node{value, nullptr};
		size++;

		if (Empty()) { head = tail = entry; return; }

		entry->next = head;
		head = entry;
	}

	void DeleteFirst()
	{
		if (Empty())
			return;

		if (size == 1)
		{
			delete head;
			head = tail = nullptr;
			size = 0;
			return;
		}

		Node* destroy = head;

		head = head->next;
		delete destroy;
		size--;
	}

	void DeleteLast()
	{
		if (Empty())
			return;

		if (size == 1)
		{
			delete head;
			head = tail = nullptr;
			size = 0;
			return;
		}

		Node* penult = head;

		while (penult->next != tail)
			penult = penult->next;

		delete tail;
		size--;

		tail = penult;
		tail->next = nullptr;
		
	}

	void add(int val, int pos)	//positions are counted from 0
	{
		if (pos < 0 || pos > size)
		{
			PushBack(val);
			cout << "add_last";
			return;
		}

		if (pos == 0) //if we are adding in the 0-th position
		{ 
			PushFront(val); 
			return; 
		}

		Node* entry = new Node{ val, nullptr };
		size++;

		Node* prev = nullptr;
		Node* curr = head;

		for (int i = 0; i < pos; i++)
		{
			prev = curr;
			curr = curr->next;
		}

		prev->next = entry;
		entry->next = curr;
	}

	void print() 
	{
		if (Empty())
			return;

		Node* it = head;

		while (it != nullptr)
		{
			cout << it->data << '#';
			it = it->next;
		}
	}

	void remove(int pos) 
	{
		if (pos < 0 || pos > size - 1)
		{
			cout << "remove_failed";
			return;
		}

		if (pos == 0)
		{ 
			DeleteFirst();
			return; 
		}

		Node* prev = nullptr;
		Node* curr = head;

		for (int i = 0; i < pos; i++)
		{
			prev = curr;
			curr = curr->next;
		}

		prev->next = curr->next;
		delete curr;
		size--;

		if (size == 1)	//we had 2 Nodes and we deleted 1 of them 
			head = tail = prev;
	}

	void reverse() 
	{
		if (Empty() || size == 1)
			return;

		Node* prev = nullptr;
		Node* curr = head;
		Node* after = nullptr;

		tail = head;

		while (curr != nullptr)
		{
			after = curr->next;

			curr->next = prev;

			prev = curr;
			curr = after;
		}
		head = prev;

	}

	void remove_all(int val) 
	{
		if (Empty())
			return;

		Node* it = head;
		int position = 0;

		while (it != nullptr)
		{
			if (it->data == val)
			{
				it = it->next;
				remove(position);
			}
			else
			{
				it = it->next;
				position++;
			}
		}


	}

	void group(int start_pos, int end_pos) 
	{
		//correctness of indeces
		if (start_pos < 0 || end_pos < 0 || start_pos > end_pos || start_pos > size - 1 || end_pos > size - 1)	
		{
			cout << "fail_grouping";
			return;
		}
		
		if (start_pos == end_pos)
			return;

		Node* before_start = nullptr;
		Node* start = head;		//start of the group
		int group_sum = 0;

		if (start_pos == 0)
		{
			for (int i = start_pos; i <= end_pos; i++)
			{
				group_sum += start->data;

				start = start->next;
				DeleteFirst();
			}

			PushFront(group_sum);
			return;
		}
		else 
		{
			int pos_to_insert = start_pos;

			for (int i = 0; i < start_pos; i++)
			{
				before_start = start;
				start = start->next;
			}

			for (int i = start_pos; i <= end_pos; i++)
			{
				group_sum += start->data;

				before_start->next = start->next;

				delete start;

				start = before_start->next;
			}

			add(group_sum, pos_to_insert);
		}
	}

	void count(int val) {
		int counter = 0;

		Node* it = head;

		while (it != nullptr)
		{
			if (it->data == val)
				counter++;

			it = it->next;
		}

		cout << counter;
	}

	void is_palindrome() 
	{
		if (Empty() || size == 1)
		{
			cout << "true";
			return;
		}

		LinkedList* reversed = new LinkedList;
		Node* it = head;

		while (it != nullptr)				//copying the current list
		{
			reversed->PushBack(it->data);
			it = it->next;
		}

		reversed->reverse();				//reversing it

		it = head;
		Node* it_rev = reversed->head;

		while (it != nullptr)		//compating the reversed with the current one
		{
			if (it->data != it_rev->data)
			{
				delete reversed;
				
				cout << "false";
				return;
			}
			else
			{
				it = it->next;
				it_rev = it_rev->next;
			}

		}

		cout << "true";
	}
};

int main() {


	LinkedList list1;
	//for (int i = 0; i < 9; i++)
	//	list1.PushBack(i + 1);

	//list1.group(2, 4);
	//list1.print();

	//list1.is_palindrome();
	//list1.remove_all(1);
	//list1.print();

	for (int i = 0; i < 10; i++)
		list1.add(i + 1, 0);

	list1.print();

	list1.group(8, 9);

	list1.print();

//#define OPA

#ifdef OPA

	int cases;
	std::cin >> cases;
	for (int i = 0; i < cases; i++) {
		LinkedList ll;
		int operations_number;
		std::string operation;

		std::cin >> operations_number;
		for (int j = 0; j < operations_number; j++) {
			std::cin >> operation;

			if (operation == "count") {
				int arg1;
				std::cin >> arg1;
				ll.count(arg1);
			}

			else if (operation == "add") {
				int arg1, arg2;
				std::cin >> arg1 >> arg2;
				ll.add(arg1, arg2);
			}

			else if (operation == "print") {
				ll.print();
			}

			else if (operation == "remove") {
				int arg1;
				std::cin >> arg1;
				ll.remove(arg1);
			}

			else if (operation == "reverse") {
				ll.reverse();
			}

			else if (operation == "remove_all") {
				int arg1;
				std::cin >> arg1;
				ll.remove_all(arg1);
			}

			else if (operation == "group") {
				int arg1, arg2;
				std::cin >> arg1 >> arg2;
				ll.group(arg1, arg2);
			}

			else if (operation == "is_palindrom") {
				ll.is_palindrome();
			}
			else 
			{
				cout << "wrong command!\n";
				return 0;
			}
		}

		std::cout << std::endl;

	}
#endif OPA

	std::system("pause");
	return 0;
}