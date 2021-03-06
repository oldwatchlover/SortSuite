
/*
 * File:	quicksort.c
 *
 * A qsort() implementation I wrote for an embedded system that didn't have one.
 *
 * Average case performance: 	O(n log n)
 * Best case performance:	O(n log n)
 * Worst case performance:	O(n^2)
 * Additional memory required:	O(log n)
 *
 * Not a stable sort. Recurisive algorithm, hence the additional memory usage (stack).
 *
 * Choice of pivot impacts the algorithm. This implementation uses the "median of 3" appraoch,
 * recommended by Segewick, which chooses as pivot the median of: array[low], array[(low+high)/2], array[high]
 * This avoids the worst case performance when the list is already or nearly sorted (or reverse sorted), which
 * can be a common situation.
 *
 */
#include <stdlib.h>
#include <string.h>

#include "quicksort.h"

static void
Swap(char *a, char *b, size_t width)
{
#define QSORT_TEMP_BUFFER_SZ	64
    char *tmp, buffer[QSORT_TEMP_BUFFER_SZ];

/* if the size of the thing to swap is "small", let's use stack space and avoid the malloc() & free() calls... */
    if (width < QSORT_TEMP_BUFFER_SZ)
	tmp = &(buffer[0]);
    else
        tmp = (char *) malloc(width);

    if (tmp == (char *) NULL)
	return;		/* can't allocate space for the swap */

    memcpy(tmp, a, width);
    memcpy(a, b, width);
    memcpy(b, tmp, width);

    if (width >= QSORT_TEMP_BUFFER_SZ)
        free(tmp);
#undef QSORT_TEMP_BUFFER_SZ
}

static int
Partition(char *array, int low, int high, size_t width, int (*compar)(const void *, const void *))
{
    int 	i, j, mid;
    char	*pivot;

    /* use the "median of 3" optimization to choose the pivot: */
    mid = (low + high) / 2;
    if ((compar)((void *)(array + (mid * width)), (void*)(array + (low * width)))) {
	Swap((array + (low * width)), array + (mid * width), width);
    }
    if ((compar)((void *)(array + (high * width)), (void*)(array + (low * width)))) {
	Swap((array + (low * width)), array + (high * width), width);
    }
    if ((compar)((void *)(array + (mid * width)), (void*)(array + (high * width)))) {
	Swap((array + (mid * width)), array + (high * width), width);
    }

    pivot = array + (high * width);
    i = low - 1;
    
    for (j=low; j<= (high-1); j++) {

        /* if current element is <= to the pivot */

	if ((compar)((void *)(array + (j * width)), (void *)pivot) <= 0) {
            i++;
	    Swap((array + (i * width)), (array + (j * width)), width);
        }
    }

    Swap((array + ((i+1) * width)), (array + (high * width)), width);

    return (i+1);
}

/*
 * internal entry point, with parameters organized so it can be called recursively
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
    int 	i, j, mid, temp, pivot;

    /* use the "median of 3" optimization to choose the pivot: */
    mid = (low + high) / 2;
    if (array[mid] < array[low]) {
	temp = array[low]; array[low] = array[mid]; array[mid] = temp;
    }
    if (array[high] < array[low]) {
	temp = array[low]; array[low] = array[high]; array[high] = temp;
    }
    if (array[mid] < array[high]) {
	temp = array[mid]; array[mid] = array[high]; array[high] = temp;
    }

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


