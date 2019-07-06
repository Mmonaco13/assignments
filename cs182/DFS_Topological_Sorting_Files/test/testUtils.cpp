#include <stdio.h>
#include <stdlib.h>
#include "testUtils.h"

/*******************************
 *
 * Utilites for testing correctness of various algorithms
 * (Methods purposely writen 'oddly' and without comments for obscurity)
 *
 * C 2018 Justin Barish and Christopher Hittner
 * 
 * Includes:
 *  Test if a result is a valid DFS  
 *  Test if a result is a valid topological sort
 *  Test if a result is a valid cycle
 */

int c1;
int c2;
int* v;
dfsinfo* my_d;
int p;

int find(int a, int* list, int n){
  for(int i = 0;i<n; i++){
    if(list[i]==a){
      return i;
    }
  }
  return -1;
}

int a1(int* a){
  int i= -1;
  while(a[++i]!=-1);
  return i;
}

bool sortMethod(int i, int j){
  return my_d->discover[i] < my_d->discover[j];
  
}
int verifyDFShelper(int node){
  if(c1 != my_d->discover[node]){
    printf("Wrong discover at node %d. Got %d expecting %d\n", node, my_d->discover[node], c1 );
    return 0;
  }
  if(p!=my_d->parent[node]){
    printf("Wrong parent at node %d. Got %d expecting %d\n", node, my_d->parent[node], p );
    return 0;
  }
  v[node] = c1++;
  int* succs =  my_d->graph->successors(node);
  std::sort(succs, succs+a1(succs), sortMethod);
  for(int i = 0; succs[i] != -1; i++){
    if((p=node)>= 0 && !v[succs[i]] && !verifyDFShelper(succs[i])){
      return 0;
    }
  }
  if(my_d->finish[node] != c2){
    printf("Wrong finish at node %d. Got %d expecting %d\n", node, my_d->finish[node], c2 );
    return 0;
  }
  return c2++;
}

/* Call this method with a dfsinfo to verify its correctnes */
bool verifyDFS(dfsinfo* _d){
  my_d = _d;
  int n = my_d->graph->numVerts();
  c1 = c2 = 1;

  v = (int*)malloc(sizeof(int)*n);
  for(int i = 0; i < n; v[i++] = 0);
  while(c1 < n){
    int fst = find(c1, my_d->discover, n);
    if(!(p=-1) || fst<0 || !verifyDFShelper(fst)){
      return false;
    }
  }
  return true;  
}


bool isCycle(Graph *g, int *path) {
  if(path==NULL) return false;
  if (!path) return false;
  else if (path[0] == -1 || path[1] == -1) return false;

  int i;
  for (i = 1; path[i] >= 0; i++) {
    if (g->edge(path[i-1], path[i]) == INFINITY)
      return false;
  }

  return g->edge(path[i-1], path[0]) != INFINITY;
}

bool isValidTopo(Graph *g, int *order) {
  if(order==NULL) return false;
  for (int i = 0; i < g->numVerts(); i++) {
    int j;
    for (j = 0; j < g->numVerts(); j++)
      if (order[j] == i)
	break;

    if (j >= g->numVerts())
      return false;
  }
  for (int i = 0; i < g->numVerts(); i++) {
    int n = order[i];
    int* ms = g->successors(n);

    int j;
    for (j = 0; ms[j] >= 0; j++) {
      int m = ms[j];

      int k;
      for (k = g->numVerts()-1; k >= i; k--) {
	if (order[k] == m)
	  break;
      }

      if (k < i)
	break;

    }
    
    if (ms[j] >= 0) {
      delete ms;
      return false;
    }
    delete ms;

  }
  return true;
}
