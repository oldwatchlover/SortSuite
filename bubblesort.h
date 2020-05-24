
/*
 * File:	bubblesort.h
 *
 */

#ifndef __BUBBLESORT_H__
#define __BUBBLESORT_H__

extern void 	BubbleSort(void *base, size_t nitems, size_t width, int (*compar)(const void *, const void *));
extern void 	BubbleSortINT(int *array, int nitems);

#endif /* __BUBBLESORT_H__ */

