
/*
 * File:	insertionsort.c
 *
 *
 * C implementation of insertion sort algorithm
 *
 * Average case performance:	O(n^2)
 * Best case performance:	O(n)
 * Worst case performance:	O(n^2)
 *
 * Memory performance:		O(n)
 *
 *
 * Stable, works well for nearly-sorted input (best case) and can stream (sort a list as it receives it)
 *
 */

#include <stdlib.h>
#include <string.h>
#include "insertionsort.h"

/*
 * InsertionSort() function
 *
 */
void
InsertionSort(void *base, size_t nitems, size_t width, int (*compar)(const void *, const void *))
{
    int		i, numSorted;
    char	*temp;

    temp = (char *) malloc(width);

    for (numSorted=1; numSorted < nitems; numSorted++) {

	memcpy(temp, base + (numSorted*width), width);
 
        for (i=numSorted; (i>0) && ((compar)(temp, (base+((i-1)*width))) < 0); i--) {

	    memcpy(base + (i*width), base + ((i-1)*width), width);
        }

	memcpy(base + (i*width), temp, width);
    }

    free(temp);
}
  
/*
 * insertionSortINT() function
 *
 * Original algorithm that just sorts an array of integers, easier to read than the stdlib API
 * version with all the pointer math...
 *
 */
void InsertionSortINT(int *array, const int N) 
{ 
    int		temp, numSorted, i;

    /*
     * Treat array [0, numSorted) as sorted and the rest to be a
     * bucket of values awaiting sorting.
     */

    for (numSorted = 1; numSorted < N; numSorted++) {

        temp = array[numSorted]; /* Get the next element to be inserted */

        for (i = numSorted; (i > 0) && (temp < array[i - 1]); i--) { /* Drag temp backwards */
            array[i] = array[i - 1];
        }

        array[i] = temp; /* Re-insert temp (possibly at the location where it started!) */
    }
}


