class MaxHeap
{
private:
	std::vector<int> arr;

public:
	MaxHeap() : arr()
	{}

	bool Empty() const { return arr.empty(); }

	int Size() const { return arr.size(); }

	int Parent(int ind) { return (ind - 1) / 2; }
	int Left(int ind) { return 2 * ind + 1; }
	int Right(int ind) { return 2 * ind + 2; }

	void SiftUp(int ind)
	{
		while (ind != 0 && arr[Parent(ind)] < arr[ind])
		{
			std::swap(arr[Parent(ind)], arr[ind]);
			ind = Parent(ind);
		}
	}

	void SiftDown(int ind)
	{
		int largest = ind;
		int left = Left(ind);
		int right = Right(ind);

		if (left < Size() && arr[left] > arr[largest])
			largest = left;

		if (right < Size() && arr[right] > arr[largest])
			largest = right;

		if (largest != ind)
		{
			std::swap(arr[largest], arr[ind]);
			SiftDown(largest);
		}
	}

	void Insert(int value)
	{
		arr.push_back(value);

		SiftUp(Size() - 1);
	}

	int GetMax()
	{
		return arr[0];
	}

	int ExtractMax()
	{
		int maximal = arr[0];

		arr[0] = arr.back();
		arr.pop_back();

		SiftDown(0);

		return maximal;
	}
};