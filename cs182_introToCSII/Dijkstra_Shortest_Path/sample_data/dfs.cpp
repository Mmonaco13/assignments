/*
 * Justin Barish
 *
 * dfs.cpp
 * Depth-first search through a graph
 */
#include "dfs.h"
#include <stdlib.h>
#include <stdio.h>

int counter;
int  finCounter ;
dfsinfo* d;

void dfsVisit(int v);

dfsinfo* DFS(Graph* g){

  d = (dfsinfo*) malloc(sizeof(struct dfsinfo));
  d->graph = g;
  int numV = d->graph->numVerts();
  
  d->discover = (int*) malloc(sizeof(int)*numV);
  d->finish = (int*) malloc(sizeof(int)*numV);
  d->parent = (int*) malloc(sizeof(int)*numV);
  d->finorder = (int*) malloc(sizeof(int)*numV);


  /*for each v in V */
  int i;
  for(i = 0; i< numV; i++){
    d->discover[i] = -1;
    d->finish[i] = -1;
    d->parent[i] = -1;
    d->finorder[i] = -1;
  }

 counter = 0;
 finCounter= 0;
  for(i = 0; i< numV; i++){
    if( d->discover[i] == -1){
      // printf("Vertex num: %i\n", i);
      dfsVisit(i);
    }
  }
  return d;
}

void dfsVisit(int v){
  counter++;
  d->discover[v] = counter;
  int* s = d->graph->successors(v);
  while(*s != -1){
    //printf("Successor: %i\n", *s);
    if(d->discover[*s]== -1 ){
      d->parent[*s] = v;
      dfsVisit(*s);
    }
    s++;
  }
  // counter++;
  finCounter ++;
  d->finish[v] = finCounter;
  d->finorder[finCounter-1] = v;

}
