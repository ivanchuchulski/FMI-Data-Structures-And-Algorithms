#pragma once

#include <iostream>


struct Node
{
	int _data;
	Node* _next;

	//Node(const int data, Node* next = nullptr)
	//	:	_data(data), _next(next)
	//{}
};


class ForwardList
{
private:
	Node* _head;
	Node* _tail;
	size_t _size;

protected:
	//no clearing is done here, there is a Clear() method
	void CopyFrom(const ForwardList& other);

public:

	ForwardList();
	ForwardList(const ForwardList& other);
	~ForwardList();
	ForwardList& operator=(const ForwardList& other);

	void Clear();

	void PushBack(int value);						// time : O(1)
	void PushFront(int value);						// time : O(1)
	void InsertAt_cf1(int pos, int value);			// time : O(pos)

	void InsertAt(int val, int pos);

	void DeleteLast();								// time : O(_entries)
	void DeleteFirst();								// time : O(1)
	void DeleteAt_cf1(int pos);						// time : O(pos)

	void DeleteAt(int pos);

	void PrintList(std::ostream& outS = std::cout) const;

	inline bool Empty() const { return _head == nullptr ? true : false; }

	inline Node* Begin() { return _head; }

	inline size_t Size() const { return _size; }

	void Reverse();

	void Reverse_v2();

};

