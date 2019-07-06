#ifndef _SORTING_HPP_
#define _SORTING_HPP_

#include <string>

/****************************************************************
Comparison of sorting algorithms.

For simplicity, only string arrays are considered,
although the sorting algorithms are not specific to strings.
 
Hints:
Some large test files are provided, but of course you should 
start by testing very small examples.
See sortTimeDemo.cpp for sample code for timing measurements.

******************************************************************/

/* All sorting algorithms should sort the data in non-decreasing order
 * https://stackoverflow.com/questions/1963474/is-a-non-decreasing-sequence-increasing 
 */
 
 /* For all sorting algorithms, assume the inital l and r values are valid. That is, 
  * 0<=l<=r<=len, and assume that arr is valid.
  * In your test cases, do not test any values for l, r, or arr that are not valid.
  */
  
  
  /* All algorithms sort IN-PLACE */

using namespace std;

/* Insertion sort
 *
 * Sort an array segment, in place:
 * Assume 0 <= l <= r and arr has length at least r.
 * Assume the elements of arr point to null-terminated strings.
 * Permute the elements, in place, to put them in non-decreasing order
 * 
 * Use the insertion sort algorithm, with binary search to find the insertion point.
 */
void insertionsort(std::string arr[], int l, int r);


/* Quicksort: same specification, but use the recursive quicksort algorithm.
 * Use a two-sided partition algorithm, as discussed in class (such a Hoare Partition).
 * You can use the one in the textbook, or some variation.
 */
void quicksort(std::string arr[], int l, int r);


/* QuicksortPlus: same specification, but use the following form of recursive quicksort:
 * 
 * If r - l <= 10, use insertionsort.
 * Otherwise, use quicksort, choosing the pivot element as the median value of 
 * arr[l], arr[r-1], and arr[(l+r)/2].
 */
void quicksortPlus(std::string arr[], int l, int r);


/* Assume arr has length at least len.
 * For each of the three sort functions, run it 10 times on arr, and print the total time 
 * for each of the three functions in a format simlar to the one below:
 * (it doesn't need to be identical to the below output or in the same order as below,
 *  but it should print the sort name, total time, and time per each iteration)
     QuickSort: 100ms total, 5ms per iteration
	 QuickSortPlus: 80ms total, 4ms per iteration
	 Insertion Sort: 600ms total, 30ms per iteration
	 
 * Reference sortTimeDemo for an example of using timings.
 */ 
void compareSorts(std::string arr[], int len);

#endif
