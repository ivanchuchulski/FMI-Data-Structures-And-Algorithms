#pragma once

#include <initializer_list>
#include <iostream>

struct Node
{
	int _data;
	Node* _prev;
	Node* _next;

	Node(int data, Node* prev = nullptr, Node* next = nullptr)
		:	_data(data), _prev(prev), _next(next)
	{}
};


class DoublyLinkedList
{
private:
	Node*_head;
	Node* _tail;
	size_t _size;

private:
	void CopyFrom(const DoublyLinkedList& other);

public:
	DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList& other);
	~DoublyLinkedList();
	DoublyLinkedList& operator=(const DoublyLinkedList& other);

	void Clear();

	void PushBack(int element);				//O(1)
	void PushFront(int element);			//O(1)

	void PopBack();							//O(1)
	void PopFront();						//O(1)

	//access the element at the front, must be called on a non-empty list
	int& Front() { return _head->_data; }

	int& Back() { return _tail->_data; }

	inline bool Empty() const { return _head == nullptr; }

	inline size_t Size() const { return _size; }

	void PrintList(std::ostream& outS = std::cout) const;

	void Reverse();

};

