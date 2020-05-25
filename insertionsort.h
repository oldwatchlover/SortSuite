
/*
 * File:	insertionsort.h
 *
 */

#ifndef __INSERTIONSORT_H__
#define __INSERTIONSORT_H__

extern void     InsertionSort(void *base, size_t nitems, size_t width, int (*compar)(const void *, const void *));
extern void	InsertionSortINT(int arr[], int nitems);


#endif /* __INSERTIONSORT_H__ */


