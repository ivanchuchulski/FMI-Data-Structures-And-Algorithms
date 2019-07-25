
void SiftDown(int* arr, int size, int ind)
{
	int largest = ind;
	int left = 2 *ind + 1;
	int right = 2 * ind + 2;

	if (left < size && arr[left] > arr[largest])
		largest = left;

	if (right < size && arr[right] > arr[largest])
		largest = right;

	if (largest != ind)
	{
		std::swap(arr[largest], arr[ind]);
		SiftDown(arr, size, largest);
	}
}

void HeapSort(int* arr, int size)
{
	for (int i = size / 2; i >= 0; i--)
		SiftDown(i);

	for (int i = size - 1; i >= 0; i--)
	{
		std::swap(arr[i], arr[0]);
		SiftDown(arr, i, 0);
	}

}
