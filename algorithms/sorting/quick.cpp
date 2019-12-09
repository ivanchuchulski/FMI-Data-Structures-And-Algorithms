int partition(int* arr, int first, int last)
{
    int pivot = arr[last];
    int border = first;
    
    for (int i = first; i < last; i++)
    {
        if (arr[i] <= pivot)
        {
            std::swap(arr[border], arr[i]);
            border++;
        }
    }
    
    std::swap(arr[border], arr[last]);
    
    return border;
}


void QuickSort(int* arr, int first, int last)
{
    if (first < last)
    {
        int piv_indx = partition(arr, first, last);
        
        QuickSort(arr, first, piv_indx - 1);
        QuickSort(arr, piv_indx +1, last);
    }
}