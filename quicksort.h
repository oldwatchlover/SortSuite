/*
 * File:	quicksort.h
 *
 */

#ifndef __QUICKSORT_H__
#define __QUICKSORT_H__

extern void QuickSort(void *base, size_t nitems, size_t width, int (*compar)(const void *, const void *));

#endif /* __QUICKSORT_H__ */
