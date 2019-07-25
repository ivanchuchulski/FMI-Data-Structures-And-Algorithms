void merge(int* arr, int first, int middle, int last)
{
    int element_count = last - first + 1;
	int* buffer = new int[element_count] {0};
    
    int left = first;
    int right = middle + 1;
    
    for (int i = 0; i < element_count; i++)
    {
        if (left > middle)
            buffer[i] = arr[right++];
        else if (right > last)
            buffer[i] = arr[left++];
        
        else if (arr[left] <= arr[right])
            buffer[i] = arr[left++];
        else
            buffer[i] = arr[right++];         
    }
    
    for (int i = 0; i < element_count; i++)
        arr[first++] = buffer[i];      
   
    delete[] buffer;
}

//first := initialy 0, the first index of the array, last := index equal to (size - 1) 
void MergeSort(int* arr, int first, int last)
{
    if (first < last)
    {
		int middle = first + (last - first) / 2;
        
        MergeSort(arr, first, middle);
        MergeSort(arr, middle + 1, last);
        
        merge(arr, first, middle, last);
    }
    else
        return;
    
}