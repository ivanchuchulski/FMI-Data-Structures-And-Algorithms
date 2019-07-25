#pragma once

struct Node
{
  int data;
  Node* next;
};

class Stack
{
private:
	Node* head;
	size_t size;

	void CopyFrom(const Stack& other)
	{
		if (other.Empty()) 
			return;
		
		head = new Node{other.head->data, nullptr};
		
		Node* from = other.head;
		Node* to = head;
		
		while (from->next != nullptr)
		{
		  from = from->next;
		  to->next = new Node{from->data, nullptr};
		  to = to->next;
		}
		size = other.size;
	}

public:
	Stack() : head(nullptr), size (0)
	{}
	~Stack() { Clear(); }
	
	size_t Size() const { return size; }
	
	bool Empty() const { return head == nullptr; }
	
	void Clear()
	{
		if (Empty())
			return;
		
		Node* destroy = nullptr;
		while (head != nullptr)
		{
			destroy = head;
			head = head->next;
			delete destroy;
		}
		head = nullptr;
		size = 0;
	}
	
	void Push(int x)		//like PushFront
	{
		Node* entry = new Node{x, nullptr};
		size++;
		
		if (Empty())
		{
			head = entry; 
			return; 
		}
		
		entry->next = head;
		head = entry;
	}
	
	void Pop()
	{
		if (Empty())
		  return;
		
		if (size == 1)
		{
			delete head;
			head = nullptr;
			size = 0;
		}

		Node* destroy = head;
		
		head = head->next;
		delete destroy;
		size--;
	}
	
	int Peek()
	{
	  return head->data;
	}
  
};