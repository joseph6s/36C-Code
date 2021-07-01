
#include "utils.hpp"

void insertion_sort(IntSequence A)
{
    /** YOUR CODE HERE
     */
    int j;
    int key;
    for( int i = 1; i < A.length; i++)
    {
        key = A.array[i];
        j = i-1;
        while(j>=0 && A.array[j]>key)
        {
            A.array[j+1]=A.array[j];
            j=j-1;
        }
        A.array[j+1] = key;
    }
}

