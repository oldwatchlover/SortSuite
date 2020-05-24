
/*
 * File:	heapsort.c
 *
 * C implementation of heap sort algorithm
 *
 *
 * Average case performance:	O(n log n)
 * Best case performance:
 * Worst case performance:	O(n log n)
 *
 * Memory performance:		O(n)
 *
 * Not a stable sort.
 *
 */

#include "heapsort.h"

static void 
siftDown(int *array, int parent, int end) 
{
    int		value,	maxChild, otherChild;

	/* initialize: */
    value = array[parent];
    maxChild = parent * 2 + 1;

    while (maxChild <= end) {

        /* check if the other child is larger */
        if (maxChild < end) {
            otherChild = maxChild + 1;
            maxChild = (array[otherChild] > array[maxChild]) ? otherChild : maxChild;
        }

        /* stop when the parent is larger than the max child */
        if (value >= array[maxChild]) 
	    break;

        array[parent] = array[maxChild];

        parent = maxChild;
        maxChild = parent * 2 + 1;
    }
   
    array[parent] = value;
}

/*
 * HeapSortINT() function
 *
 * Sorts an array of integers
 */
void 
HeapSortINT(int *array, const int nitems) 
{ 
    int		i, temp;

    /* build a max heap */

    for (i = (nitems / 2); i >= 0; i--)
        siftDown(array, i, nitems - 1);

    for (i = nitems - 1; i >= 1; i--) {
	/* swap: */
	temp = array[0]; array[0] = array[i]; array[i] = temp;

        siftDown(array, 0, i - 1);
    }
}

