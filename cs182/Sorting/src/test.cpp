#include "sorting.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#define TOTAL_TESTS 10

//"I pledge my honor that I have abided by the Stevens Honor System"
//Matthew Monaco and Nicholas Primamore

bool isSorted(std::string arr[], int len){
  for(int i = 1; i < len; i++){
    if(arr[i-1]> arr[i]){
      return false;
    }
  }
  return true;
}


bool run_test(int test_number) 
{
    switch(test_number){
    case 1:{
        //test01: Insertion Sort with One Element
        std::string arr[]={"a"};
        insertionsort(arr, 0, 1);

        if(!isSorted(arr, 1)){
            return false;
        }
        break;
    }

    case 2:{
        //test02: Quicksort with One Element
        std::string arr[]={"z"};
        quicksort(arr, 0, 1);

        if(!isSorted(arr, 1)){
            return false;
        }
        break;
    }

    case 3:{
        //test03: Quicksort+ with One Element
        std::string arr[]={"c"};
        quicksortPlus(arr, 0, 1);

        if(!isSorted(arr, 1)){
            return false;
        }
        break;
    }
    case 4:{
        // test04: Insertion Sort with Duplicates
        std::string arr[]={"z","a","x","z","a","t","s","z","z","m","a","k","a","d","a"};
        insertionsort(arr, 0, 15);

        if(!isSorted(arr, 15)){
            return false;
        }
        break;
    }
    case 5:{
        // test05: Quicksort with Duplicates
        std::string arr[]={"z","a","x","z","a","t","s","z","z","m","a","k","a","d","a"};
        quicksort(arr, 0, 15);

        if(!isSorted(arr, 15)){
            return false;
        }
        break;
    }
    case 6:{
        // test06: Quicksort+ with Duplicates
        std::string arr[]={"z","a","x","z","a","t","s","z","z","m","a","k","a","d","a"};
        quicksortPlus(arr, 0, 15);

        if(!isSorted(arr, 15)){
            return false;
        }
        break;
    }
    case 7:{
        // test07: Insertion Sort with All Same Element
        std::string arr[]={"a","a","a","a","a","a","a","a","a","a","a","a","a","a","a"};
        insertionsort(arr, 0, 15);

        if(!isSorted(arr, 15)){
            return false;
        }
        break;
    } 
    case 8:{
        // test08: Quicksort with All Same Element
        std::string arr[]={"a","a","a","a","a","a","a","a","a","a","a","a","a","a","a"};
        quicksort(arr, 0, 15);

        if(!isSorted(arr, 15)){
            return false;
        }
        break;
    }
    case 9:{
        // test09: Quicksort+ with All Same Element
        std::string arr[]={"a","a","a","a","a","a","a","a","a","a","a","a","a","a","a"};
        quicksortPlus(arr, 0, 15);

        if(!isSorted(arr, 15)){
            return false;
        }
        break;
    }
    case 10:{
      // test10 :Quicksort+ on Already Sorted Array
      std::string arr[]={"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o"};
      quicksortPlus(arr,0,15);

      if(!isSorted(arr, 15)){
            return false;
        }
        break;
    }         

  default: {
    printf("ERROR! Test number %d was not found!\n", test_number);
    exit(1);
  }
    
  }
  // test must have passed.
  return true;
}

int main() {
  int num_fail = 0;
  for (int tn = 1; tn <= TOTAL_TESTS; tn++) {
    printf("- running test # %02d ... ", tn);
    int result = run_test(tn);
    printf("%s\n", (result == true ? "succeed" : "FAIL"));
    if (result == false) num_fail++;
  }
  printf("SUMMARY: %d FAIL, %d succeed\n", num_fail, TOTAL_TESTS - num_fail);
}

