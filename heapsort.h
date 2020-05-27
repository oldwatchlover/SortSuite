
/*
 * File:	heapsort.h
 *
 */

#ifndef __HEAPSORT_H__
#define __HEAPSORT_H__

extern void     HeapSort(void *base, size_t nitems, size_t width, int (*compar)(const void *, const void *));
extern void	HeapSortINT(int *array, int nitems);

#endif /* __HEAPSORT_H__ */

