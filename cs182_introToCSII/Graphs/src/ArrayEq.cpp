#include "ArrayEq.h"
bool findIn(int a, int* arr){
   for(int i = 0; arr[i]!= -1; i++){
     if(arr[i] ==a){
       return true;
     }
   }
   return false;
}
bool test(int* arr1, int* arr2) {
  if(!arr1 || !arr2 ){
    return false;
  }  
  for(int i = 0; arr1[i]!= -1; i++){
    if(!findIn(arr1[i],arr2)){
      return false;
    }
  }
  return true;
}

//Call this function to check if all elements in arr1 are in arr2, and vice-verca
//note that this does not work if the arrays can have duplicate elements, but we know succs/preds will not.
bool eq(int* arr1, int* arr2){
  //test only tests 1-direction, need to check they are equal, not subsets, so do both ways
  return test(arr1, arr2) & test(arr2, arr1);
}

