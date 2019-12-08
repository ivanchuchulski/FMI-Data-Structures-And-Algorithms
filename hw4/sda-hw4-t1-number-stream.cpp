#include <iostream>
#include <cstdlib>

using std::cout;
using std::cin;


struct Node
{
	int _data;
	Node* _next;
};

class ForwardList
{
private:
	Node* _head;
	Node* _tail;
public:

	ForwardList()
		: _head(nullptr), _tail(nullptr)
	{}

	~ForwardList()
	{
		if (_head == nullptr)

			return;
		Node* prev = nullptr;
		Node* curr = _head;

		while (curr->_next != nullptr)
		{
			prev = curr;
			curr = curr->_next;
			delete prev;
		}
		delete curr;

		_head = nullptr;
		_tail = nullptr;
	}

	void PushBack(int value)
	{
		Node* to_add = new Node;
		to_add->_data = value;
		to_add->_next = nullptr;

		if (_head == nullptr)
		{
			_head = to_add;
			_tail = to_add;
		}
		else
		{
			_tail->_next = to_add;
			_tail = to_add;
		}
	}

	void PrintList(std::ostream& outS = std::cout) const
	{
		Node* it = _head;

		while (it != nullptr)
		{
			outS << it->_data << ' ';
			it = it->_next;
		}

		outS << '\n';
	}

	void TakeData(int& min, int& max, long long& sum) const
	{
	//	if (_head == nullptr)
	//		return;

		min = _head->_data;
		max = _head->_data;
		sum = _head->_data;

		Node* it = _head->_next;

		while (it != nullptr)
		{
			sum += it->_data;
			min = (it->_data < min) ? it->_data : min;
			max = (it->_data > max) ? it->_data : max;

			it = it->_next;
		}

	}

};


int main() {

	//unsync cpp streams with c ones
	std::ios_base::sync_with_stdio(false);

	ForwardList numbers;

	int entry = 0;

	while (cin >> entry)
		numbers.PushBack(entry);

	numbers.PrintList();

	int min = 0, max = 0;
	long long sum = 0;

	numbers.TakeData(min, max, sum);

	cout << min << ' ' << max << ' ' << sum << ' ';



	std::system("pause");
	return 0;
}