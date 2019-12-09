void BubbleSort(int* arr, int size)
{
    for(int i = 0; i < size -1; i++)
    {
        bool is_sorted = true;
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (arr[j + 1] < arr[j])
            {
                is_sorted = false;
                std::swap(arr[j + 1], arr[j]);
            }     
        }   
        
        if (is_sorted)
            break;
    }
}