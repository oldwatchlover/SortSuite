
/*
 * File:	main.c
 *
 * Test driver to exercise some sorting code
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bubblesort.h"
#include "heapsort.h"
#include "insertionsort.h"
#include "mergesort.h"
#include "quicksort.h"

char	*ProgramName;
#define USAGE_STRING	"(no options)"

/* UTILITY FUNCTIONS */

#define TEST_SIZE	32

#if 0
/* an un-aligned structure to test with irregular objects: */
typedef struct {
    int         key;    /* will sort on this key */
    char        crap[3];
    float       val;
} dummy_td;

dummy_td        funny_array[TEST_SIZE];

static void
FillFunnyArray(int count)
{
    int		i;

    for (i=0; i<count; i++) {
        funny_array[i].key = rand() % 100;
        funny_array[i].crap[0] = i;
        funny_array[i].crap[1] = i+1;
        funny_array[i].crap[2] = i+2;
        funny_array[i].val = (float)i * 100.0f;
    }
}

/* test function, prints out an array of my irregular structures */
static void
PrintFunnyArray(dummy_td array[], int size)
{
    int i;

    for (i=0; i<size; i++) {
        fprintf(stdout,"\tkey = %d, crap = %02x %02x %02x, val = %f\n",
                array[i].key, array[i].crap[0], array[i].crap[1], array[i].crap[2], array[i].val);
    }
}

/* compare my irregular structures */
int funny_compare(const void *a, const void *b)
{
    dummy_td    *ad, *bd;

    ad = (dummy_td *) a;
    bd = (dummy_td *) b;

    if (ad->key < bd->key)
        return (-1);
    else if (ad->key > bd->key)
        return (1);
    else
        return (0);
}
#endif


static void
fillTestArray(int array[], int size)
{
    int		i;

    for (i=0; i<size; i++) {
        array[i] = rand() % 100;
    }
}

/* Function to print an array */
static void 
printArray(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        fprintf(stdout,"%d ", A[i]);
    fprintf(stdout,"\n");
}

/* comparison routine to pass to sort algorithms which use the stdlib format */
static int
my_compare(const void *a, const void *b)
{
    int         ai, bi;

    ai = * ((int *) a);
    bi = * ((int *) b);

    if (ai < bi)
        return (-1);
    else if (ai > bi)
        return (1);
    else
        return (0);
}


/*
 * main routine.
 *
 */
int
main(int argc, char *argv[])
{
    clock_t		begin, end;
    time_t		t;
    float		elapsed;
    int			arr[TEST_SIZE];
    int			arr_size = sizeof(arr)/sizeof(arr[0]);

    ProgramName = (char *) malloc(strlen(argv[0])+1);
    strcpy(ProgramName, argv[0]);

    srand((unsigned) time(&t));	/* seed rand() */

    while ((argc > 1) && (argv[1][0] == '-')) {
	switch(argv[1][1]) {

/*
 * check for any program arguments:
 *
          case 'a':
	    break;
	    
          case 'b':
	    val = atoi(argv[2]);
	    argc--;
	    argv++;
	    break;
*/
	    
	  default:
	    fprintf(stderr,"%s : %s : program option [%s] not recognized. Ignored. (File %s, line %d)\n", 
		    ProgramName,"WARNING",argv[1],__FILE__,__LINE__);
	    fprintf(stderr,"%s : %s\n",ProgramName,USAGE_STRING);
	    break;
	}
	argc--;
	argv++;
    }



	/* test bubble sort */
    fprintf(stdout,"Test BubbleSort():\n");
    fprintf(stdout,"\tTest input array is \n\t");
    fillTestArray(arr, arr_size);
    printArray(arr, arr_size);

    begin = clock();
    BubbleSort((void *) &(arr[0]), arr_size, sizeof(int), my_compare);
    end = clock();

    fprintf(stdout,"\n\tSorted array is \n\t");
    printArray(arr, arr_size);

    elapsed = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stderr,"%s : took %lf seconds.\n\n",ProgramName,elapsed);


	/* test heap sort */
    fprintf(stdout,"Test HeapSortINT():\n");
    fprintf(stdout,"\tTest input array is \n\t");
    fillTestArray(arr, arr_size);
    printArray(arr, arr_size);

    begin = clock();
    HeapSortINT(arr, arr_size);
    end = clock();

    fprintf(stdout,"\n\tSorted array is \n\t");
    printArray(arr, arr_size);

    elapsed = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stderr,"%s : took %lf seconds.\n\n",ProgramName,elapsed);

	/* test insertion sort */
    fprintf(stdout,"Test InsertionSortINT():\n");
    fprintf(stdout,"\tTest input array is \n\t");
    fillTestArray(arr, arr_size);
    printArray(arr, arr_size);

    begin = clock();
    InsertionSortINT(arr, arr_size);
    end = clock();

    fprintf(stdout,"\n\tSorted array is \n\t");
    printArray(arr, arr_size);

    elapsed = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stderr,"%s : took %lf seconds.\n\n",ProgramName,elapsed);


	/* test insertion sort */
    fprintf(stdout,"Test InsertionSort():\n");
    fprintf(stdout,"\tTest input array is \n\t");
    fillTestArray(arr, arr_size);
    printArray(arr, arr_size);

    begin = clock();
    InsertionSort((void *) &(arr[0]), arr_size, sizeof(int), my_compare);
    end = clock();

    fprintf(stdout,"\n\tSorted array is \n\t");
    printArray(arr, arr_size);

    elapsed = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stderr,"%s : took %lf seconds.\n\n",ProgramName,elapsed);


	/* test merge sort */
    fprintf(stdout,"Test MergeSortINT():\n");
    fprintf(stdout,"\tTest input array is \n\t");
    fillTestArray(arr, arr_size);
    printArray(arr, arr_size);

    begin = clock();
    MergeSortINT(arr, arr_size);
    end = clock();

    fprintf(stdout,"\n\tSorted array is \n\t");
    printArray(arr, arr_size);

    elapsed = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stderr,"%s : took %lf seconds.\n\n",ProgramName,elapsed);


	/* test quick sort */
    fprintf(stdout,"Test QuickSort():\n");
    fprintf(stdout,"\tTest input array is \n\t");
    fillTestArray(arr, arr_size);
    printArray(arr, arr_size);

    begin = clock();
    QuickSort((void *) &(arr[0]), arr_size, sizeof(int), my_compare);
    end = clock();

    fprintf(stdout,"\n\tSorted array is \n\t");
    printArray(arr, arr_size);

    elapsed = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stderr,"%s : took %lf seconds.\n\n",ProgramName,elapsed);

	/* test quick sort INT*/
    fprintf(stdout,"Test QuickSortINT():\n");
    fprintf(stdout,"\tTest input array is \n\t");
    fillTestArray(arr, arr_size);
    printArray(arr, arr_size);

    begin = clock();
    QuickSortINT(arr, arr_size);
    end = clock();

    fprintf(stdout,"\n\tSorted array is \n\t");
    printArray(arr, arr_size);

    elapsed = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stderr,"%s : took %lf seconds.\n\n",ProgramName,elapsed);


#if 0
	/* test unaligned data sort */
    fprintf(stdout,"Test InsertionSort() with unaligned data:\n");
    fprintf(stdout,"\tTest input array is \n\t");
    FillFunnyArray(arr_size);
    PrintFunnyArray(funny_array, arr_size);

    begin = clock();
    InsertionSort((void *) &(funny_array[0]), arr_size, sizeof(dummy_td), funny_compare);
    end = clock();

    fprintf(stdout,"\n\tSorted array is \n");
    PrintFunnyArray(funny_array, arr_size);

    elapsed = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stderr,"%s : took %lf seconds.\n\n",ProgramName,elapsed);
#endif


    exit(EXIT_SUCCESS);
}

