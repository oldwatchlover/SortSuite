
/*
 * File:	mergesort.h
 *
 */

#ifndef __MERGESORT_H__
#define __MERGESORT_H__

extern void     MergeSort(void *base, size_t nitems, size_t width, int (*compar)(const void *, const void *));
extern void	MergeSortINT(int arr[], int nitems);

#endif /* __MERGESORT_H__ */


