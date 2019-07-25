#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iterator>

using std::cout;
using std::cin;
using int64 = long long int;


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
		Clear();
	}

	void Clear()
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

class NumPair
{
public:
	int _first;
	int _second;

	NumPair() = default;
	NumPair(const NumPair& other) = default;
	~NumPair() = default;
	NumPair& operator=(const NumPair& other) = default;

	NumPair(int fir, int sec)
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

	//operators == and < are strict weak ordering, which makes them usable in std::sort()
	bool operator==(const NumPair& other)
	{
		return (_first == other._first && _second == other._second);
	}

	bool operator<(const NumPair& other)
	{
		//if (_first == other._first && _second == other._second)
		//	return false;

		if (_first < other._first)
			return true;

		else if (_first > other._first)
			return false;

		else
			return _second < other._second;

	}


};

void PrintPairs(std::vector<NumPair>& pairs)
{
	for (auto& p : pairs)
		cout << p;

	cout << '\n';
}

void CountingLists(ForwList& input, int64* arr, int P)
{
	const int largest_possible_value = 1234;
	int* counts = new int[largest_possible_value + 1] {0};
	Node* it = input.Begin();

	//counting
	while (it != nullptr)
	{
		counts[it->_data]++;
		it = it->_next;
	}

	//for (int i = 0; i < P; i++)
	//{
	//	if (arr[i] <= 1234 && arr[i] >= 1)
	//	{


	//	}
	//}

	delete[] counts;
}

bool FindAppearances(int64* sorted, int size, int smaller, int bigger)
{
	int first = 0;
	int last = size - 1;

	bool found = false;
	int occurrence;

	//first search for the smaller
	while (first <= last)
	{
		int middle = first + (last - first) / 2;

		if (sorted[middle] == smaller)
		{
			occurrence = middle;
			found = true;
			break;
		}

		else if (smaller < sorted[middle])
			last = middle - 1;

		else
			first = middle + 1;
	}

	if (!found)
		return false;

	else
	{
		int under = occurrence;
		int over = size - 1;

		while (under <= over)
		{
			int mid2 = under + (over - under) / 2;

			if (sorted[mid2] == bigger)
			{
				return true;
			}
			else if (bigger < sorted[mid2])
				over = mid2 - 1;
			else
				under = mid2 + 1;
		}

		//smaller was found, but not bigger
		return false;
	}
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

	//cout << "printing list : \n";
	//list.PrintList();

	//CountingLists(list, arr, P);

	std::vector<NumPair> pairs;
	pairs.reserve(N - 1);

	Node* it_prev = nullptr;
	Node* it = list.Begin();

	//cant make any pairs if you have only 0 or 1 one
	if (it == nullptr)
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
	}

	//using the operator < in the NumPairs class
	std::sort(pairs.begin(), pairs.end());

	std::vector<NumPair> unique_pairs;
	std::unique_copy(pairs.begin(), pairs.end(), std::back_inserter(unique_pairs));

//	std::vector<NumPair>::iterator last = std::unique(pairs.begin(), pairs.end());
//	pairs.erase(last, pairs.end());

	std::sort(arr, arr + P);

	int counter = 0;
	for (auto& un_pair : unique_pairs)
	{
		if (FindAppearances(arr, P, un_pair._first, un_pair._second))
			counter++;
		else
			continue;
	}
	
	cout << counter << '\n'; 



	delete[] arr;
	delete[] list_entries;


	std::system("pause");
	return 0;
}