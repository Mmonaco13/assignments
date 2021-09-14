/*
 * C Justin Barish 2016-18
 *
 * minprio.c
 * Creates a minimum priority queue of max size, with external comparison function
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "minprio.h"

/* make an empty queue
 * Items will be compared using comp.
 *
 * It' the client's responsibility to ensure size is never exceeded.
 */
MinPrio::MinPrio(Comparator compFunc, int maxsize){
  comp = compFunc;
  MAXSIZE = maxsize+1;
  handles = new handle*[MAXSIZE];//+1 b/c not including 0
  for (int i =0; i< MAXSIZE; i++){
    handles[i] = NULL;
  }
  currentSize = 0;
}

/* dispose of memory owned by the queue
 * Namely: the queue object, the array, and the Handles.
 * The Handle contets are the responsibility of the client.
 */
MinPrio::~MinPrio(){
  for(int i = 0; i< MAXSIZE; i++){
    if( handles[i]!= NULL){
      delete handles[i];
      handles[i] = NULL;
    }
  }

  delete[] handles;
  handles = NULL;
  currentSize = 0;
  MAXSIZE = 0;  
}

void swap(MinPrio::handle** arr,  MinPrio::handle* h1,  MinPrio::handle* h2){
  int h1Pos = h1->pos;
  int h2Pos = h2->pos;
  arr[h1Pos] = h2;
  arr[h1Pos]->pos = h1Pos;
  arr[h2Pos] = h1;
  arr[h2Pos]->pos = h2Pos;
}

/* enqueue 
 * Assumes queue currently contains less than maxsize elements.
 * Assumes qp and item non-null. 
 * Returns a Handle containing the item, for use with decreaseKey.
 */
MinPrio::handle* MinPrio::enqueue( void* item){
  currentSize++; //currsize now points to spot in array for new item
  handle* hand =  new handle;
  hand->pos = currentSize;
  hand->content = item;
  handles[currentSize] = hand;
  handle* parent = handles[hand->pos/2];
  
  while(hand->pos/2 >0 && comp(parent->content, hand->content)>0){
    swap(handles, parent, hand);
    
    // implicit hand = hand
    parent = handles[hand->pos/2];
  }
  return hand;
}

/* 1 if queue has elements, else 0 (assuming qp non-null) */
bool MinPrio::nonempty(){
  return currentSize > 0;
}


/* dequeue and return a minimum element according to the comparator.
 * Assumes qp non-null and queue nonempty */
void* MinPrio::dequeueMin(){
  void* returnContent =  handles[1]->content;
  handle* removed  = handles[1];
  delete removed;
  
  if(currentSize ==1){ //if only was one thing left in queue, just return the one thing
    currentSize--;
    handles[currentSize] = NULL;
    return returnContent;
  }
  
  handles[1]= handles[currentSize];
  handles[currentSize] = NULL;
  handles[1]->pos = 1;
    
  currentSize--;
  
  handle* parent = handles[1];
  handle* child1;
  handle* child2;
  if(parent->pos*2 +1 <=currentSize){
    child1= handles[parent->pos*2];
    child2 = handles[parent->pos*2 +1];
  }
    
  while((parent->pos*2 +1 <=currentSize) && //ensures children won't be out of bounds
	(comp(parent->content, child1->content) >0 ||
	 comp(parent->content, child2->content) >0 )){
    
    child1 = handles[parent->pos*2];
    child2 = handles[parent->pos*2 +1];

    if(comp(child1->content, child2->content) >0){ //childleft< child right, so use right child
      swap(handles, child2, parent);
      parent = child2;
    }else { //childright< child left, so use child left
      swap(handles, child1, parent);
      parent = child1;
    }
  }
  
  /*since while loop does not check orderings if size =2, need this check*/
  if(currentSize ==2 && comp(parent->content, handles[parent->pos*2]->content) >0){
    swap(handles, parent,  handles[parent->pos*2]);
  }
  return returnContent;
}

/* decrease the item's key
 * Must be called whenever comparison value may have changed.
 * Must only decrease comparison value (i.e. raise priority).
 *
 * Assumes qp non-null and hand is in the queue. 
 */
void MinPrio::decreasedKey(handle* hand){
  handle* parent = handles[hand->pos/2];
  while(hand->pos/2 >0 && comp(parent->content, hand->content)>0){
    swap(handles, parent, hand);
    parent = handles[hand->pos/2];
  }
  if( currentSize ==2&& comp(handles[1]->content, handles[2]->content) >0){
    swap(handles, handles[1],  handles[2]);  
  }
}



