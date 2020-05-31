
/*
 * File:	bubblesort.c
 *
 * C implementation of bubble sort algorithm
 *
 * Average case peformance:	O(n^2)
 * Best case performance:	O(n)	(if list is already sorted, with extra logic to detect (not in here))
 * Worst case performance:	O(n^2)
 * Additional memory required:	O(1)
 *
 * Stable sort, very small code size.
 *
 * Rarely used in practice due to it's performance, but it can make sense to use if compact code size is desired or if 
 * you know the size of the set to sort is small and you can unroll the loop.
 *
 */

#include <stdlib.h>
#include <string.h>
#include "bubblesort.h"

static void
Swap(char *a, char *b, size_t size)
{
    char *tmp;

    tmp = (char *) malloc(size);

    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);

    free(tmp);
}
  
/*
 * BubbleSort() function
 *
 */
void
BubbleSort(void *base, size_t nitems, size_t width, int (*compar)(const void *, const void *))
{ 
    int		i, j;

    for (i=0; i< nitems-1; i++) {
	for (j=0; j < nitems-i-1; j++) {

	    if ((compar)((void *)(base + (width * j)), (void *)(base + (width * (j+1)))) > 0) {
		Swap((base + (j * width)), (base + (width * (j+1))), width);
	    }
	}
    }
}


/*
 * BubbleSortINT() function
 *
 * Simple version of the algorithm that just sorts an array of integers, rather than the general-purpose
 * stdlib API version, where the pointer math makes it nearly unreadable... :-)
 *
 */
void
BubbleSortINT(int *array, int nitems)
{ 
    int		i, j, temp;

    for (i=0; i< nitems-1; i++) {
	for (j=0; j < nitems-i-1; j++) {

	    if (array[j] > array[j+1]) {
	 	temp = array[j];
		array[j] = array[j+1];
		array[j+1] = temp;
            }
	}
    }
}

