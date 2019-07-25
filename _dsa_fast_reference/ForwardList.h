struct Node
{
	int data;
	Node* next;
};

class ForwardList
{
private:
	Node* head;
	Node* tail;
	int size;

private:
	void CopyFrom(const ForwardList& other)
	{
		if (other.Empty())
			return;

		head = new Node{ other.head->data, nullptr };

		Node* from = other.head;
		Node* to = head;

		while (from->next != nullptr)
		{
			from = from->next;
			to->next = new Node{ from->data, nullptr };
			to = to->next;
		}
		tail = to;
		size = other.size;
	}

public:
	ForwardList() : head(nullptr), tail(nullptr), size(0)
	{}

	ForwardList(const ForwardList& other) : head(nullptr), tail(nullptr), size(0)
	{
		CopyFrom(other);
	}

	~ForwardList() { Clear(); }

	int Size() const { return size; }

	bool Empty() const { return head == nullptr; }

	void Clear()
	{
		if (Empty()) return;

		Node* destroy = nullptr;

		while (head != nullptr)
		{
			destroy = head;
			head = head->next;
			delete destroy;
		}

		head = tail = nullptr;
		size = 0;
	}

	void PushFront(int x)
	{
		Node* entry = new Node{ x, nullptr };
		size++;

		if (Empty())
		{
			head = tail = entry;
			return;
		}

		entry->next = head;
		head = entry;
	}

	void PushBack(int x)
	{
		Node* entry = new Node{ x, nullptr };
		size++;

		if (Empty())
		{
			head = tail = entry;
			return;
		}

		tail->next = entry;
		tail = entry;
	}
	void InsertAt(int x, int pos) //list positions are counted from 1
	{
		if (pos < 1 || pos > size)
			return;

		if (Empty())
		{
			PushFront(x);
			return;
		}

		Node* entry = new Node{ x, nullptr };
		size++;

		Node* prev = nullptr;
		Node* curr = head;

		for (size_t i = 1; i < pos; i++)
		{
			prev = curr;
			curr = curr->next;
		}

		prev->next = entry;
		entry->next = curr;
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

	void DeleteAt(int pos) //list positions are counted from 1
	{
		if (pos < 1 || pos > size)
			return;

		if (Empty())
			return;

		if (pos == 1) { DeleteFirst(); return; }
		if (pos == size) { DeleteLast(); return; }

		Node* prev = nullptr;
		Node* curr = head;

		for (size_t i = 1; i < pos; i++)
		{
			prev = curr;
			curr = curr->next;
		}

		prev->next = curr->next;
		delete curr;
		size--;

		if (size == 1)
			head = tail = prev;
	}

	void Reverse()
	{
		if (Empty() || size == 1)
			return;

		Node* reversed = nullptr;
		Node* temp = nullptr;

		tail = head;
		while (head != nullptr)
		{
			temp = head->next;
			head->next = reversed;

			reversed = head;
			head = temp;
		}
		head = reversed;
	}

	Node*& Head()
	{
		return head;
	}

	ForwardList Merge(ForwardList& list1, ForwardList& list2)
	{
		if (list1.Empty() && list2.Empty())
			return ForwardList();

		int element_count = list1.Size() + list2.Size();

		ForwardList output;

		Node* left = list1.Head();
		int l_indx = 0;
		Node* right = list2.Head();
		int r_indx = 0;

		for (int i = 0; i < element_count; i++)
		{
			if (l_indx > list1.Size() - 1)
			{
				output.PushBack(right->data);
				right = right->next;
				l_indx++;
			}
			else if (r_indx > list2.Size() - 1)
			{
				output.PushBack(left->data);
				left = left->next;
				l_indx++;
			}

			else if (left->data <= right->data)
			{
				output.PushBack(left->data);
				left = left->next;
				l_indx++;
			}

			else
			{
				output.PushBack(right->data);
				right = right->next;
				r_indx++;
			}
		}

		return output;
	}

};