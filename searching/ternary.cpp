int TernarySearch(int* sorted, int first, int last, int to_find)
{
	if (first > last)
		return -1;

	int mid1 = (2 * first + last) / 3;
	int mid2 = (first + 2 * last) / 3;

	if (sorted[mid1] == to_find)
		return mid1;
	else if (sorted[mid2] == to_find)
		return mid2;

	if (to_find < sorted[mid1])
		return TernarySearch(sorted, first, mid1 - 1, to_find);
	else if (to_find < sorted[mid2])
		return TernarySearch(sorted, mid1 + 1, mid2 - 1, to_find);
	else
		return TernarySearch(sorted, mid2 + 1, last, to_find);
}