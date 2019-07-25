int FindNumberOfOccs(int* sorted, int size, int to_find)
{
    int first = 0, last = size - 1;
    int middle;
    
    int num_of_occurr = 0;
    
    while (first <= last)
    {
        middle = first + (last - first) / 2;
        
        if (sorted[middle] == to_find)
        {
            num_of_occurr = 1;
            break;
        }
        else if (to_find < sorted[middle])
            last = middle -1;
        else
            first = middle +1;
    }
    
    if (num_of_occurr == 0)
        return 0;

    for (int i = middle + 1; i < size; i++)
        if (sorted[i] == to_find)
            num_of_occurr++;
        else
          break;
      
    for (int i = middle - 1; i >= 0; i--)
        if (sorted[i] == to_find)
            num_of_occurr++;
        else
           break;
    
    return num_of_occurr;
}