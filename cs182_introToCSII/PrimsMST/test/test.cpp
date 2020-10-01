#include "primmst.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//Indicates the error when the test case fails

/* Do NOT test Prim's MST algorithm from this test file
 * Only test your priority queue.
 */
#define TOTAL_TESTS 5

//float comparison
int compareFloat(void* lhs, void* rhs){
  float* a = (float*) lhs;
  float* b = (float*) rhs;
  if(*a > *b) return 1;
  else if (*a < *b) return -1;
  return 0;
}


bool run_test(int test_number) {
  switch(test_number) {
  case 1: { //Tests if queue is empty after adding a float

    MinPrio* q = new MinPrio(&compareFloat, 1);
    
    float a = 0;

    q->enqueue(&a);


    if(!q->nonempty()){
      return false;
    }

    delete q;
    
    break;
  }

  case 2: {
    // test02 : dequeueMin will return the min
    MinPrio* q = new MinPrio(&compareFloat, 3);
    
    float a = 1;
    float b = 0;
    float c = -1;
    
    q->enqueue(&a);
    q->enqueue(&b);
    q->enqueue(&c);

    //Should dequeue in correct order
    if(compareFloat(q->dequeueMin(), &c) != 0){
      return false;
    }
    if(compareFloat(q->dequeueMin(), &b) != 0){
      return false;
    }

    delete q;
    
    break;
  }
    
  case 3: {
    // test03 : Test that the value does not change after becoming a void* and then coverted back.
    MinPrio* q = new MinPrio(&compareFloat, 1);
    float a = 0;
    
    MinPrio::handle* h;
    h = q->enqueue(&a);
    
    if(compareFloat(q->dequeueMin(), h->content) != 0){
      return false;
    }
 
    //delete h;
    delete q;
    break;
  }
    
    
  case 4: {
    // test04 : //A queue initialized with a size of less than one should have a size of one
    MinPrio* q = new MinPrio(&compareFloat, 0);
    float a = 0;
    float b = 1;
  

    MinPrio::handle* h;
    //Assumes enqueue() works
    if(q->enqueue(&a) == NULL){
      return false;
    }
    if(q->enqueue(&b) != NULL){
      return false;
    }

    delete q;
    break;
  }
    
  case 5: {
    // test05 : Changed values do not update the queue unless told to
    MinPrio* q = new MinPrio(&compareFloat, 2);
    float a = 0;
    float b = 1;

    MinPrio::handle* h;
    q->enqueue(&a);
    h = q->enqueue(&b);
    *((float*)h->content) = -1;
    if(compareFloat(q->dequeueMin(), h->content) == 0){
      return false;
    }

    //delete h;
    delete q;

    q = new MinPrio(&compareFloat, 2);
    q->enqueue(&b);
    h = q->enqueue(&a);
    *((float*)h->content) = -2;
    q->decreasedKey(h);
    if(compareFloat(q->dequeueMin(), h->content) != 0){
      return false;
    }

    //delete h;
    delete q;
    
    break; // if your test suceeds, break
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


