#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using int64 = long long int;

class NumPair
{
public:
	int _first;
	int _second;

	NumPair() = default;
	NumPair(const NumPair& other) = default;
	~NumPair() = default;
	NumPair& operator=(const NumPair& other) = default;

	NumPair(int& fir, int& sec)
		: _first(), _second()
	{
		//making the first element to be less than the second
		if (fir <= sec)
		{
			_first = fir;
			_second = sec;
		}
		else
		{
			_first = sec;
			_second = fir;
		}
	}

	friend std::ostream& operator<<(std::ostream& outS, NumPair& p)
	{
		outS << "f : " << p._first << ", s : " << p._second << '\n';

		return outS;
	}
};


struct Node
{
	int _data;
	Node* _next;
};

class ForwList
{
private:
	Node* _head, *_tail;

public:
	ForwList()
		: _head(nullptr), _tail(nullptr)
	{}
	
	~ForwList()
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
		Node* entry = new Node;
		entry->_data = value;
		entry->_next = nullptr;

		if (_head == nullptr)
			_tail = _head = entry;

		else
		{
			_tail->_next = entry;
			_tail = entry;
		}
	}

	Node* Begin()
	{
		return _head;
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
};

void PrintPairs(std::vector<NumPair>& pairs)
{
	for (auto& p : pairs)
		cout << p;

	cout << '\n';
}

int main() {

	std::ios_base::sync_with_stdio(false);

	ForwList list;

	int N, P;
	int* list_entries = nullptr;
	int64* arr = nullptr;

	cin >> N;
	list_entries = new int[N] {0};
	for (int i = 0; i < N; i++)
	{
		cin >> list_entries[i];
		list.PushBack(list_entries[i]);
	}

	cin >> P;
	arr = new int64[P]{0};
	for (int i = 0; i < P; i++)
		cin >> arr[i];


	std::vector<NumPair> pairs;
	pairs.reserve(N / 2);

	Node* it = list.Begin();
	Node* it_prev = nullptr;

	//cant make any pairs if you have only 0 or 1 one
	if (it == nullptr || it->_next == nullptr)
	{
		cout << 0 << '\n';
		return 0;
	}

	//making pairs
	while (it->_next != nullptr)
	{
		it_prev = it;
		it = it->_next;

		pairs.emplace_back(NumPair(it_prev->_data, it->_data));

		if (it->_next == nullptr)
			break;
		else
			it = it->_next;	
	}

	list.PrintList();
	PrintPairs(pairs);


	delete[] arr;
	delete[] list_entries;


	std::system("pause");
	return 0;
}