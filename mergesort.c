
/*
 * File:	mergesort.c
 *
 *
 * C implementation of merge sort algorithm
 *
 * Average case performance:	O(n log n)
 * Best case performance:	O(n log n)
 * Worst case performance:	O(n log n)
 * Additional memory required:	O(n)
 *
 * Stable sort. Highly parallelizable if desired (divide and conquer approach).
 *
 */

#include <stdlib.h>
#include <string.h>
#include "mergesort.h"

  
/*
 * Merges two subarrays of width-wide items pointed to by base
 *
 * First subarray is base+(l*width) ... base+(m*width)
 * Second subarray is base+((m+1)*width) ... base+(r*width)
 *
 */
static void 
merge(char *base, int l, int m, int r, size_t width, int (*compar)(const void *, const void *)) 
{ 
    char	*L, *R;
    int 	i, j, k, n1, n2; 
  
    /* calc size of temp arrays and create them */
    n1 = m - l + 1; 
    n2 = r - m; 
    L = (char *) malloc(width * n1);
    R = (char *) malloc(width * n2);
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
	memcpy(L + (i*width), base + ((l+i)*width), width);
    for (j = 0; j < n2; j++) 
	memcpy(R + (j*width), base + ((m+1+j)*width), width);
  
    /* Merge the temp arrays back into base+(l*width)...base+(r*width) */
    i = 0; /* Initial index of first subarray  */ 
    j = 0; /* Initial index of second subarray */ 
    k = l; /* Initial index of merged subarray */ 

    while (i < n1 && j < n2) { 
	if ((compar)(L+(i*width), R+(j*width)) <= 0) {
	    memcpy(base+(k*width), L+(i*width), width);
	    i++;
        } else {
	    memcpy(base+(k*width), R+(j*width), width);
	    j++;
        }
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if any */
    while (i < n1) { 
	memcpy(base+(k*width), L+(i*width), width);
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if any */
    while (j < n2) { 
	memcpy(base+(k*width), R+(j*width), width);
        j++; 
        k++; 
    } 

    free(L);	/* release memory of the temporary arrays */
    free(R);
} 
  
/*
 * Internal MergeSort2() function
 *
 * l is for left index and r is right index of the 
 * sub-array of array to be sorted (pointed to by base) 
 */
static void 
MergeSort2(char *base, int l, int r, size_t width, int (*compar)(const void *, const void *)) 
{ 
    if (l < r) { 
        int m = (l+r)/2;
  
        /* Sort first and second halves */ 
        MergeSort2(base, l, m, width, compar); 
        MergeSort2(base, m+1, r, width, compar); 
  
        merge(base, l, m, r, width, compar); 
    } 
} 

/*
 * MergeSort()
 *
 * External API, same API as stdlib
 *
 */
void 
MergeSort(void *base, size_t nitems, size_t width, int (*compar)(const void *, const void *))
{ 
    MergeSort2(base, 0, nitems-1, width, compar);
} 


/*
 * Merges two subarrays of array[]
 *
 * First subarray is array[l...m]
 * Second subarray is array[m+1...r]
 *
 */
static void 
mergeINT(int array[], int l, int m, int r) 
{ 
    int 	i, j, k; 
    int 	n1 = m - l + 1; 
    int 	n2 =  r - m; 
    int		L[n1], R[n2];
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = array[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = array[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; /* Initial index of first subarray  */ 
    j = 0; /* Initial index of second subarray */ 
    k = l; /* Initial index of merged subarray */ 

    while (i < n1 && j < n2) { 
        if (L[i] <= R[j]) { 
            array[k] = L[i]; 
            i++; 
        } else { 
            array[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if any */
    while (i < n1) { 
        array[k] = L[i]; 
        i++; k++; 
    } 
  
    /* Copy the remaining elements of R[], if any */
    while (j < n2) { 
        array[k] = R[j]; 
        j++; k++; 
    } 
} 
  
/*
 * Internal MergeSort2() function
 *
 * l is for left index and r is right index of the 
 * sub-array of arr to be sorted 
 */
static void 
MergeSort2INT(int array[], int l, int r) 
{ 
    if (l < r) { 
        int m = (l+r)/2;
  
        /* Sort first and second halves */ 
        MergeSort2INT(array, l, m); 
        MergeSort2INT(array, m+1, r); 
  
        mergeINT(array, l, m, r); 
    } 
} 

/*
 * MergeSortINT()
 *
 * External API, takes an array of ints and a count, sorts in place
 *
 */
void 
MergeSortINT(int array[], int nitems) 
{ 
    MergeSort2INT(array, 0, nitems-1);
} 


