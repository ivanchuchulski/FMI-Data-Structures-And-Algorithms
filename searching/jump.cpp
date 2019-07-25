#include <algorithm>
#include <cmath>

bool JumpSearch(int* arr, int size, int to_find)
{
	int step = (int)std::sqrt(size);
	int prev = 0;
	int next = prev + step;

	while (arr[std::min(next, size) - 1] < to_find)
	{
		prev = next;
		next += step;

		if (prev >= size)
			return false;
	}

	while (arr[prev] < to_find)
	{
		prev++;
		if (prev == std::min(step, size))
			return false;
	}

	if (arr[prev] == to_find)
		return true;
	else
		return false;
}