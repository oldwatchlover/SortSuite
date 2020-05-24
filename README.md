
Steve's Sort Suite


A while ago I had to write a quicksort() routine for a graphics program running
on a system withot stdlib...

I have extracted that code and cleaned it up a bit, with a test program.

Then I added several other sorting algorithms... some of them have correct stdlib type
API's, others are just toys, and can only sort an array of integers (see the source code).

    bubblesort.h	- header file, for bubble sort functions
    bubblesort.c	- implements BubbleSort() and BubbleSortINT()
    heapsort.h		- header file, for heap sort functions
    heapsort.c		- implements HeapSortINT()
    insertionsort.h	- header file, for insertion sort
    insertionsort.c	- implements InsertionSort() and InsertionSortINT()
    mergesort.h		- header file for merge sort
    mergesort.c		- implements MergeSortINT()
    quicksort.h		- header file, for quick sort
    quicksort.c		- implements QuickSort(), a stdlib compatible qsort() routine
    main.c		- simple test program 
    Makefile		- builds all of this


