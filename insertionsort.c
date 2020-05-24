
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
    int		i, j;
    char	*temp;

    temp = (char *) malloc(width);

    for (i=1; i < nitems; i++) {

	memcpy(temp, base + (i*width), width);
 
        for (j=i; (j>0) && ((compar)(temp, (base+((j-1)*width))) < 0); j--) {

	    memcpy(base + (j*width), base + ((j-1)*width), width);
        }

	memcpy(base + (j*width), temp, width);
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
    int		temp, i, j;

    /* assume array[0, i] is sorted and the rest is moved one at a time */

    for (i = 1; i < N; i++) {

        temp = array[i]; /* get the next element to be inserted */

        for (j = i; (j > 0) && (temp < array[j - 1]); j--) { /* move temp backwards */
            array[j] = array[j - 1];
        }

        array[j] = temp; /* re-insert temp (possibly at it's original location) */
    }
}


