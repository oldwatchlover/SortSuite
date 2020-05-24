
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
    const int	value = array[parent];
    int		maxChild = parent * 2 + 1;
    int		otherChild;

    while (maxChild <= end) {

        /* See if the other child is larger */
        if (maxChild < end) {
            otherChild = maxChild + 1;
            maxChild = (array[otherChild] > array[maxChild]) ? otherChild : maxChild;
        }

        /* Stop when the parent is larger than the max child */
        if (value >= array[maxChild]) break;

        array[parent] = array[maxChild];

        parent = maxChild;
        maxChild = parent * 2 + 1;
    }
   
    array[parent] = value;
}

#define SWAP(a, b) {int temp = array[a]; array[a] = array[b]; array[b] = temp; }

/*
 * HeapSortINT() function
 *
 * Sorts an array of integers
 */
void 
HeapSortINT(int *array, const int nitems) 
{ 
    int		i;

    /* Form a max heap */

    for (i = (nitems / 2); i >= 0; i--)
        siftDown(array, i, nitems - 1);

    for (i = nitems - 1; i >= 1; i--) {
        SWAP(0, i);
        siftDown(array, 0, i - 1);
    }
}

#undef SWAP

