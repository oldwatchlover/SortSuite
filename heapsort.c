
/*
 * File:	heapsort.c
 *
 * C implementation of heap sort algorithm
 *
 *
 * Average case performance:	O(n log n)
 * Best case performance:	O(n log n)
 * Worst case performance:	O(n log n)
 * Additional memory required:	O(1)
 *
 * Not a stable sort.
 *
 */

#include <stdlib.h>
#include <string.h>
#include "heapsort.h"

static void 
siftDown(char *base, int parent, int end, size_t width, int (*compar)(const void *, const void *))
{
    int		maxChild, otherChild;
    char	*temp;

	/* initialize: */
    temp = (char *) malloc(width);
    memcpy(temp, base + (parent*width), width);
    maxChild = parent * 2 + 1;

    while (maxChild <= end) {

        /* check if the other child is larger */
        if (maxChild < end) {
            otherChild = maxChild + 1;

	    if ((compar)((base + (otherChild*width)), (base + (maxChild*width))) > 0) {
	        maxChild = otherChild;
            }
        }

        /* stop when the parent is larger than the max child */
	if ((compar)(temp, (base + (maxChild*width))) >= 0)
	    break;

        memcpy(base + (parent*width), base + (maxChild*width), width);
        parent = maxChild;
        maxChild = parent * 2 + 1;
    }
   
    memcpy(base + (parent*width), temp, width);
}

/*
 * HeapSortINT() function
 *
 * Sorts an array of integers
 */
void 
HeapSort(void *base, size_t nitems, size_t width, int (*compar)(const void *, const void *))
{ 
    int		i;
    char	*temp;

    /* build a max heap (heapify) */
    temp = (char *) malloc(width);

    for (i = (nitems / 2); i >= 0; i--)
        siftDown(base, i, nitems - 1, width, compar);

    for (i = nitems - 1; i >= 1; i--) {
	/* swap: */
        memcpy(temp, base + (0*width), width);
        memcpy(base, base + (i*width), width);
        memcpy(base + (i*width), temp, width);

        siftDown(base, 0, i - 1, width, compar);
    }
}

/*
 * integer array version, a little clearer to implement
 *
 */

static void 
siftDownINT(int *array, int parent, int end) 
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

    /* build a max heap (heapify) */

    for (i = (nitems / 2); i >= 0; i--)
        siftDownINT(array, i, nitems - 1);

    for (i = nitems - 1; i >= 1; i--) {
	/* swap: */
	temp = array[0]; array[0] = array[i]; array[i] = temp;

        siftDownINT(array, 0, i - 1);
    }
}

