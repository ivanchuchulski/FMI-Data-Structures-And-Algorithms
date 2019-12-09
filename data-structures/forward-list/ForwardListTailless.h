#pragma once
#include <iostream>


struct Node
{
	int _data;
	Node* _next;

	Node(const int data, Node* next = nullptr)
		:	_data(data), _next(next)
	{}
};

class ForwardListTailless
{
private:
	Node* _head;
	size_t _size;

private:
	//no clearing is done here, there is a Clear() method
	void CopyFrom(const ForwardListTailless& other);

public:
	ForwardListTailless();
	ForwardListTailless(const ForwardListTailless& other);
	~ForwardListTailless();
	ForwardListTailless& operator=(const ForwardListTailless& other);

	void Clear();

	void PushBack(int value);					// time : O(_entries)
	void PushFront(int value);					// time : O(1)
	void InsertAt(int pos, int value);			// time : O(pos)

	void DeleteLast();							// time : O(_entries)
	void DeleteFirst();							// time : O(1)
	void DeleteAt(int pos);						// time : O(pos)

	void PrintList(std::ostream& outS = std::cout) const;


	inline bool Empty() const { return _head == nullptr; }

	inline size_t Size() const { return _size; }

	inline Node* Begin() const { return _head; }

	void Reverse();

};

