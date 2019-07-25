#pragma once

struct Node
{
	int data;
	Node* next;
};

class Queue
{
private:
	Node* head;
	Node* tail;
	size_t size;

	void CopyFrom(const Queue& other)
	{
		if (other.Empty())  return;
	
		head = new Node{other.head->data, nullptr};
	
		Node* from = other.head;
		Node* to = head;
	
		while (from->next != nullptr)
		{
			from = from->next;
			to->next = new Node{from->data, nullptr};
			to = to->next;
		}
		tail = to;
		size = other.size;
	}

public:
	Queue() : head(nullptr), tail(nullptr), size(0) 
	{}
	~Queue() { Clear(); }
	
	size_t Size() const { return size; }
	
	bool Empty() const { return head == nullptr; }
	
	void Clear()
	{
		if (Empty())  return;
		
		Node* destroy = head;
		while (head != nullptr)
		{
			destroy = head;
			head = head->next;
			delete destroy;
		}
		head = tail = nullptr;
		size = 0;
	}
	
	void Enqueue(int x)	//like PushBack
	{
		Node* entry = new Node{x, nullptr};
		size++;
		
		if (Empty()) 
		{
			head = tail = entry; 
			return;
		}
		
		tail->next = entry;
		tail = entry;
	}
	
	void Dequeue() //like DeleteFront
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
	
	int Front() 
	{ 
		return head->data; 
	}

	int Back()
	{ 
		return tail->data; 
	}
};
