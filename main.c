
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
#define USAGE_STRING	"[-h] [-i] [-o offset] [-r range] [-s size] [-u] [-v]"

/* control strings for colored text output: */
#define DEFAULT_COLOR_TEXT      "\033[0m"       /* goes back to shell default color */
#define RED_COLOR_TEXT          "\033[1;31m"
#define GREEN_COLOR_TEXT        "\033[1;32m"


#define TEST_SIZE	1024
#define TEST_DATA_RANGE	1024

static int	arr_size = TEST_SIZE;
static int	test_data_range = TEST_DATA_RANGE;
static int	test_data_offset = 0;
static int	be_quiet = 1;

/* UTILITY FUNCTIONS */

/* an structure to test with irregular objects: */
typedef struct {
    int         key;    /* will sort on this key */
    char        crap[3];
    float       val;
} dummy_td;

dummy_td        *funny_array = (dummy_td *)NULL;

static void
FillFunnyArray(int count)
{
    int		i;

    for (i=0; i<count; i++) {
        funny_array[i].key = (rand() % test_data_range) - test_data_offset;
        funny_array[i].crap[0] = i;
        funny_array[i].crap[1] = i+1;
        funny_array[i].crap[2] = i+2;
        funny_array[i].val = (float)i * (float)(test_data_range-test_data_offset);
    }
}

/* test function, prints out an array of my irregular structures */
static void
PrintFunnyArray(dummy_td array[], int size, int verbose)
{
    int i;

    if (verbose) {
        for (i=0; i<size; i++) {
            fprintf(stdout,"\tkey = %d, crap = %02x %02x %02x, val = %f\n",
                    array[i].key, array[i].crap[0], array[i].crap[1], array[i].crap[2], array[i].val);
        }
    } else {
	fprintf(stdout,"\t");
        for (i=0; i<size; i++) {
            fprintf(stdout,"%d ", array[i].key);
        }
	fprintf(stdout,"\n");
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


/* Function to print an array */
static void 
printArray(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        fprintf(stdout,"%d ", A[i]);
    fprintf(stdout,"\n");
}

static int
compareArray(int a[], int b[], int size)
{
    int		i, retval = 1;

    for (i=0; i<size; i++) {
	if (a[i] != b[i])
	    retval = 0;
    }

    return(retval);
}

/* comparison routine to pass to sort algorithms which use the stdlib format */
static int
my_int_compare(const void *a, const void *b)
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

/* tests the *SortINT() versions of the functions */
static void
testINTsorts(int tarr[], int arr[], int gold_arr[], int arr_size)
{
    clock_t	begin, end;
    float	elapsed;
    int 	i;

	/* macro to minimize repeated code... 
         * uses macro-fu to pass the parameter that is the sort routine to call,
         * as well as the text label reporting on that sort
         */
#define TEST_SORT(a) 									\
    {											\
    int alen = strlen(""#a""); 								\
    char *ac = (alen > 15) ? " " : "\t "; 						\
    for (i=0; i<arr_size; i++) { arr[i] = tarr[i]; } 					\
    begin = clock(); 									\
    a(arr, arr_size);					 				\
    end = clock(); 									\
    elapsed = (double)(end - begin) / CLOCKS_PER_SEC; 					\
    if (compareArray(gold_arr, arr, arr_size)) { 					\
        fprintf(stdout,"%s : %s()\t%ssort is %s%s%s\t took %lf seconds.\n", 		\
	    ProgramName,""#a"",ac,GREEN_COLOR_TEXT,"CORRECT",DEFAULT_COLOR_TEXT,elapsed); 	\
    } else { 										\
        fprintf(stdout,"%s : %s()\t%ssort is %s%s%s\t took %lf seconds.\n", 		\
	    ProgramName,""#a"",ac,RED_COLOR_TEXT,"INCORRECT",DEFAULT_COLOR_TEXT,elapsed); 	} }


    TEST_SORT(BubbleSortINT);
    TEST_SORT(HeapSortINT);
    TEST_SORT(InsertionSortINT);
    TEST_SORT(MergeSortINT);
    TEST_SORT(QuickSortINT);

#undef TEST_SORT
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
    int			i, *tarr, *arr, *gold_arr;
    int			use_int = 0, use_funny = 0;

    ProgramName = (char *) malloc(strlen(argv[0])+1);
    strcpy(ProgramName, argv[0]);

    srand((unsigned) time(&t));	/* seed rand() */

	/* check for any program arguments: */
    while ((argc > 1) && (argv[1][0] == '-')) {
	switch(argv[1][1]) {

	  case 'h':
	    fprintf(stderr,"%s : %s\n",ProgramName,USAGE_STRING);
	    exit(EXIT_SUCCESS);
	    break;

          case 'i':	/* also run the *SortINT() tests */
	    use_int = 1;
	    break;
	    
          case 'u':
 	    use_funny = 1;	/* also test the array of structure test */
	    break;

          case 'o':
	    test_data_offset = atoi(argv[2]);
	    argc--;
	    argv++;
	    break;
	    
          case 'v':
 	    be_quiet = 0;	/* verbose, more output, useful for small tests */
	    break;

          case 'r':
	    test_data_range = atoi(argv[2]);
	    argc--;
	    argv++;
	    break;
	    
          case 's':
	    arr_size = atoi(argv[2]);
	    argc--;
	    argv++;
	    break;
	    
	  default:
	    fprintf(stderr,"%s : %s : program option [%s] not recognized. Ignored. (File %s, line %d)\n", 
		    ProgramName,"WARNING",argv[1],__FILE__,__LINE__);
	    fprintf(stderr,"%s : %s\n",ProgramName,USAGE_STRING);
	    break;
	}
	argc--;
	argv++;
    }

	/* initialize some test data, run qsort() to generate golden output */

    funny_array = (dummy_td *) malloc(arr_size*sizeof(dummy_td));
    arr = (int *) malloc(arr_size*sizeof(int));
    tarr = (int *) malloc(arr_size*sizeof(int));
    gold_arr = (int *) malloc(arr_size*sizeof(int));

    fprintf(stdout,"\n%s : Sort Suite algorithm comparison (array of %d integers):\n",ProgramName,arr_size);
    fprintf(stdout,"---------------------------------------------------------------\n");

    for (i=0; i<arr_size; i++) { tarr[i] = (rand() % test_data_range)-test_data_offset; }
    for (i=0; i<arr_size; i++) { gold_arr[i] = tarr[i]; }
    if (!be_quiet) {
        fprintf(stdout,"%s : Test input array is:\n\t",ProgramName);
        printArray(gold_arr, arr_size);
    }
    begin = clock();
    qsort(gold_arr, arr_size, sizeof(int), my_int_compare);
    end = clock();

    if (!be_quiet) {
        fprintf(stdout,"%s : Correct Sorted array is:\n\t",ProgramName);
        printArray(gold_arr, arr_size);
    }
    fprintf(stdout,"\n");

    elapsed = (double)(end - begin) / CLOCKS_PER_SEC;
    if (!be_quiet) {
        fprintf(stdout,"%s : %s\t\t sort is %s%s%s\t took %lf seconds.\n",
	        ProgramName,"qsort() (stdlib)",GREEN_COLOR_TEXT,"CORRECT",DEFAULT_COLOR_TEXT,elapsed);
    }


	/* macro to minimize repeated code... 
         * uses macro-fu to pass the parameter that is the sort routine to call,
         * as well as the text label reporting on that sort
         */
#define TEST_SORT(a) 									\
    { 											\
    int alen = strlen(""#a""); 								\
    char *ac = (alen < 8) ? "\t " : " "; 						\
    for (i=0; i<arr_size; i++) { arr[i] = tarr[i]; } 					\
    begin = clock(); 									\
    a((void *) &(arr[0]), arr_size, sizeof(int), my_int_compare);			\
    end = clock(); 									\
    elapsed = (double)(end - begin) / CLOCKS_PER_SEC; 					\
    if (compareArray(gold_arr, arr, arr_size)) { 					\
        fprintf(stdout,"%s : %s()\t\t%ssort is %s%s%s\t took %lf seconds.\n", 			\
	    ProgramName,""#a"",ac,GREEN_COLOR_TEXT,"CORRECT",DEFAULT_COLOR_TEXT,elapsed); 	\
    } else { 											\
        fprintf(stdout,"%s : %s()\t\t%ssort is %s%s%s\t took %lf seconds.\n", 			\
	    ProgramName,""#a"",ac,RED_COLOR_TEXT,"INCORRECT",DEFAULT_COLOR_TEXT,elapsed); } }


    TEST_SORT(BubbleSort);
    TEST_SORT(heapsort);	/* stdlib version */
    TEST_SORT(HeapSort);
    TEST_SORT(InsertionSort);
    TEST_SORT(mergesort);	/* stdlib version */
    TEST_SORT(MergeSort);
    TEST_SORT(qsort);		/* stdlib version */
    TEST_SORT(QuickSort);

#undef TEST_SORT

    if (use_int) {
        testINTsorts(tarr, arr, gold_arr, arr_size);
    }

    if (use_funny) {
	/* test array of structure data sort */
        FillFunnyArray(arr_size);
        if (!be_quiet) {
            fprintf(stdout,"\nTest QuickSort() with structure data:\n");
            fprintf(stdout,"\tTest input structure array sort keys are:\n\t");
            PrintFunnyArray(funny_array, arr_size, 0);
        }

        begin = clock();
        QuickSort((void *) &(funny_array[0]), arr_size, sizeof(dummy_td), funny_compare);
        end = clock();
        elapsed = (double)(end - begin) / CLOCKS_PER_SEC;
    
	if (!be_quiet) {
            fprintf(stdout,"\n\tSorted structure array sort keys are:\n\t");
            PrintFunnyArray(funny_array, arr_size, 0);
        }
        fprintf(stderr,"%s : %s() of structure array took %lf seconds.\n\n",
 		ProgramName,"QuickSort",elapsed);
    }

    fprintf(stdout,"\n");
    exit(EXIT_SUCCESS);
}

