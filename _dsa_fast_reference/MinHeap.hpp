

class MinHeap
{
private:
	std::vector<int> arr;

public:
	MinHeap() : arr()
	{}


	bool Empty() const { return arr.empty(); }

	int Size() const { return arr.size(); }

	int Parent(int ind) { return (ind - 1) / 2; }
	int Left(int ind) { return 2 * ind + 1; }
	int Right(int ind) { return 2 * ind + 2; }

	void SiftUp(int ind)
	{
		while (ind != 0 && arr[Parent(ind)] > arr[ind])
		{
			std::swap(arr[Parent(ind)], arr[ind]);
			ind = Parent(ind);
		}
	}

	void SiftDown(int ind)
	{
		int smallest = ind;
		int left = Left(ind);
		int right = Right(ind);

		if (left < Size() && arr[left] < arr[smallest])
			smallest = left;

		if (right < Size() && arr[right] < arr[smallest])
			smallest = right;

		if (smallest != ind)
		{
			std::swap(arr[smallest], arr[ind]);
			SiftDown(smallest);
		}
	}

	void Insert(int value)
	{
		arr.push_back(value);

		SiftUp(Size() - 1);
	}

	int GetMin()
	{
		return arr[0];
	}

	int ExtractMin()
	{
		if (Empty())
			throw std::out_of_range("out of range");

		int minimal = arr[0];

		arr[0] = arr.back();
		arr.pop_back();

		SiftDown(0);

		return minimal;
	}

	//remove by given value
	void Delete(int x)
	{
		int indx;
		for (int i = 0; i < arr.size(); i++)
		{
			if (arr[i] == x)
			{
				indx = i;
				break;
			}
		}

		int parent = Parent(indx);
		swap(arr[indx], arr[arr.size() - 1]);
		arr.pop_back();

		if (indx == 0 || arr[parent] < arr[indx])
			SiftDown(indx);
		else
			SiftUp(indx);
	}

};
