
/*
 * File:	quicksort.c
 *
 * A qsort() implementation I wrote for an embedded system that didn't have one.
 *
 * Average case performance: 	O(n log n)
 * Best case performance:	O(n log n)
 * Worst case performance:	O(n^2)
 *
 * Memory usage:		O(n)
 *
 * Choice of pivot impacts the algorithm. This implementation uses the last element, which can
 * lead to poor performance on already-sorted input.
 *
 */
#include <stdlib.h>
#include <string.h>

#include "quicksort.h"

static void
Swap(char *a, char *b, size_t width)
{
    char *tmp;

    tmp = (char *) malloc(width);

    memcpy(tmp, a, width);
    memcpy(a, b, width);
    memcpy(b, tmp, width);

    free(tmp);
}

static int
Partition(char *array, int low, int high, size_t width, int (*compar)(const void *, const void *))
{
    int 	i, j;
    char	*pivot;

    pivot = array + (width * high);
    i = low - 1;

    for (j=low; j<= (high-1); j++) {

        /* if current element is <= to the pivot */

	if ((compar)((void *)(array + (width * j)), (void *)pivot) <= 0) {
            i++;
	    Swap((array + (i * width)), (array + (j * width)), width);
        }
    }

    Swap((array + ((i+1) * width)), (array + (high * width)), width);

    return (i+1);
}

/*
 * internal func, with parameters so it can be called recursively
 *
 */
static void
_quicksort(char *array, int low, int high, size_t width, 
		int (*compar)(const void *, const void *))
{
    int		pi;

    if (low < high) {
	/* pi is partition index. array[pi] is at the right place */
	pi = Partition(array, low, high, width, compar);

        /* partition before and after */

        _quicksort(array, low, pi-1, width, compar);
        _quicksort(array, pi+1, high, width, compar);
    }
}

/*
 * QuickSort()
 *
 * Public API, same as stdlib qsort()
 *
 */
void
QuickSort(void *array, size_t nitems, size_t width, int (*compar)(const void *, const void *))
{
    _quicksort((char *) array, 0, nitems-1, width, compar);
}


/******* INT version, just to be thorough ******/


static int
PartitionINT(int *array, int low, int high)
{
    int 	i, j, temp, pivot;

    pivot = array[high];
    i = low - 1;

    for (j=low; j<= (high-1); j++) {

        /* if current element is <= to the pivot */

	if (array[j] < pivot) {
            i++;
	    temp = array[i]; array[i] = array[j]; array[j] = temp;
        }
    }

    temp = array[i+1]; array[i+1] = array[high]; array[high] = temp;

    return (i+1);
}

static void
_quicksortINT(int *array, int low, int high)
{
    int		pi;

    if (low < high) {
	/* pi is partition index. array[pi] is at the right place */
	pi = PartitionINT(array, low, high);

        /* partition before and after */

        _quicksortINT(array, low, pi-1);
        _quicksortINT(array, pi+1, high);
    }
}

/*
 * QuickSortINT()
 *
 * Public API
 *
 */
void
QuickSortINT(int *array, int nitems)
{
    _quicksortINT(array, 0, nitems-1);
}


