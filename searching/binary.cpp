int BinaryRecursive(int* sorted, int first, int last, int to_find)
{
	if (first > last)	//recursion bottom
		return -1;

	int middle = first + (last - first) / 2;

	if (sorted[middle] == to_find)
		return middle;
	else if (to_find < sorted[middle])
		return BinaryRecursive(sorted, first, middle - 1, to_find);
	else
		return BinaryRecursive(sorted, middle + 1, last, to_find);
}

int BinaryIterative(int* sorted, int size, int to_find)
{
	int first = 0, last = size - 1;

	while (first <= last)
	{
		int middle = first + (last - first) / 2;

		if (sorted[middle] == to_find)
			return middle;
		else if (to_find < sorted[middle])
			last = middle - 1;
		else
			first = middle + 1;
	}

	return -1;		//if not found
}