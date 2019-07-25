void InsertionSort(int* arr, int size)
{
    for (int i = 1; i < size; i++)
    {
        for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--)
            std::swap(arr[j], arr[j - 1]);
    }
}