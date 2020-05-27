
Steve's Sort Suite


A while ago I had to write a quicksort() routine for a graphics program running
on a system withot stdlib...

I have extracted that code and cleaned it up a bit, with a test program.

Then I added several other sorting algorithms. All of them have correct stdlib type
API's, as well as simpler versions that just sort integer arrays.

    bubblesort.h        - header file, for bubble sort functions
    bubblesort.c        - implements BubbleSort() and BubbleSortINT()
    heapsort.h          - header file, for heap sort functions
    heapsort.c          - implements HeapSort() and HeapSortINT()
    insertionsort.h     - header file, for insertion sort
    insertionsort.c     - implements InsertionSort() and InsertionSortINT()
    mergesort.h         - header file for merge sort
    mergesort.c         - implements MergeSort() and MergeSortINT()
    quicksort.h         - header file, for quick sort
    quicksort.c         - implements QuickSort() and QuickSortINT()
    main.c              - simple test program 
    Makefile            - builds the test program against the sorting functions
    README.md           - this file


