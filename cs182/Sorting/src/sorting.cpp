/********************************************************************
 "I pledge my honor that I have abided by the Stevens Honor System."
 Nicholas Primamore and Matthew Monaco
 
 sorting.cpp
 *******************************************************************/

#include "sorting.hpp"
#include <string>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <cstdio>
#include <cstring>

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
int binarySearch(std::string arr[], string word, int left, int right){
    //base case: found insertion point b/c left and right are equal
    if(left >= right){
        if(word.compare(arr[left]) > 0){
            return left + 1;
        }
        else return left;
    }
    
    //word is at the midpoint
    int midpoint = (left+right)/2;
    if(word.compare(arr[midpoint]) == 0){
        return midpoint + 1;
    }
    
    //word is less than the midpoint
    if(word.compare(arr[midpoint]) < 0){
        return binarySearch(arr, word, left, midpoint - 1);
    }
    else{
        //word is greater than the midpoint
        return binarySearch(arr, word, midpoint + 1, right);
    }
}

void insertionsort(std::string arr[], int l, int r){
    for(int index = l+1; index < r; index++){
        int temp = index - 1; // we care about words to the left of current position
        string word = arr[index];
        int insertionPoint = binarySearch(arr, word, l, temp);
        
        //shifting strings
        while(temp >= insertionPoint){
            arr[temp+1] = arr[temp];
            temp--;
        }
        
        //putting the current word in correct position
        arr[temp+1] = word;
    } 
}

void quicksort(std::string arr[], int l, int r){
    if(l>=r-1){
        return;
    }
    string partString = arr[l];
    string temp;
    int i = l;
    int j = r;
    
    do{
        do{
            i++;
        }while(i<r-1 && arr[i]<partString);
        do{
            j--;
        }while(j>l && arr[j]>=partString);
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;

    }while(i<j);

    temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    
    temp = arr[l];
    arr[l] = arr[j];
    arr[j] = temp;
    quicksort(arr, l, j);
    quicksort(arr, j+1, r);
}
void quicksortPlus(std::string arr[], int l, int r){
    if(r-l<=10){
        insertionsort(arr, l, r);
    }else{
        //pivot picking
        string low = arr[l];
        string mid = arr[(l+r)/2];
        string high = arr[r-1];
        string median;
        int medlocation;

        //low mid
        if(low<=mid){
            if(mid.compare(high)<=0){
                //low mid high
                medlocation = (l+r)/2;
            }else{
                if(low.compare(high)<=0){
                    //low high mid
                    medlocation = r-1;
                }else{
                    //high low min
                    medlocation = l;
                }
            }
            //mid low
        }else{
            if(low.compare(high)<=0){
                //mid low high
                medlocation = l;
            }else{
                if(mid.compare(high)<=0){
                    //mid high low
                    medlocation = r-1;
                }else{
                    //high mid low
                    medlocation = (l+r)/2;
                }
            }
        }

        median = arr[medlocation];
        string temp = arr[medlocation];
        arr[medlocation] = arr[l];
        arr[l] = temp;


        int i = l;
        int j = r;

        do{
            do{
                i++;
            }while(i<r-1 && arr[i]<median);
            do{
                j--;
            }while(j>l && arr[j]>=median);
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

        }while(i<j);

        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        temp = arr[l];
        arr[l] = arr[j];
        arr[j] = temp;
        quicksortPlus(arr, l, j);
        quicksortPlus(arr, j+1, r);
    }
}

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
void compareSorts(std::string arr[], int len){
    //Insertion Sort:
    clock_t insertionStart = clock();
    for(int i = 0; i < 10; i++){
        insertionsort(arr, 0, len);
    }
    clock_t insertionEnd = clock();
    double insertionTime = ((double)(insertionEnd - insertionStart)) / CLOCKS_PER_SEC;
    printf("Insertion Sort: %f seconds total, %f seconds per iteration.\n", insertionTime, insertionTime/10);
    
    
    //Quick Sort:
    clock_t quickStart = clock();
    for(int i = 0; i < 10; i++){
        quicksort(arr, 0, len);
    }
    clock_t quickEnd = clock();
    double quickTime = ((double)(quickEnd - quickStart)) / CLOCKS_PER_SEC;
    printf("Quick Sort: %f seconds total, %f seconds per iteration.\n", quickTime, quickTime/10);
    
    
    //Quick Sort Plus:
    clock_t quickPlusStart = clock();
    for(int i = 0; i < 10; i++){
        quicksortPlus(arr, 0, len);
    }
    clock_t quickPlusEnd = clock();
    double quickPlusTime = ((double)(quickPlusEnd - quickPlusStart)) / CLOCKS_PER_SEC;
    printf("Quick Sort Plus: %f seconds total, %f seconds per iteration.\n", quickPlusTime, quickPlusTime/10);
}