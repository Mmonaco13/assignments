#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h> 
#include <assert.h>

#include "graph.h"
#include "graphio.h"
#include "dfs.h"
#include "topocycle.h"

/*************************
 * DFS facts
 * 
 * For either a digraph or even undirected graph, u is a proper ancestor of v
 * in the DFS forest iff discover[u] < discover[v] and finish[v] < finish[u].
 * 
 * A 'back edge' goes from a vertex to an ancestor of that vertex.
 * A graph is cyclic if and only if the DFS forest has a back edge.
 *
 * To topologically sort an acyclic graph, order the vertices in reverse
 * of the 'finish' order.  (Can do that during DFS by pushing finished vertices
 * into an array.  Don't do it later by later by sorting, since that costs more time (O(nlogn).)
 * ************************ */ 

/* whether anc is a proper ancestor of v (i.e., ancestor and anc!=v) 
 * Assume u, v are vertices of di->graph. */
bool proper_ancestor(dfsinfo* di, int anc, int v) {
    return anc!=v &&
        di->discover[anc] < di->discover[v] &&
        di->finish[v] < di->finish[anc];
}


int* topocycle(GraphInfo gi) {
  printf("Not Implemented!\n");
  return NULL;
}
void printTopocycle(GraphInfo gi){
  printf("Not Implemented!\n");
}

bool cyclic(dfsinfo* di, GraphInfo gi){
  int v;
  int* s;
  for (v = 0; v< di->graph->numVerts(); v++){
    s = di->graph->successors(v);
    while (*s!= -1){
      if (proper_ancestor(di, *s, v)){
	return 1;
      }
      s++;
    }
  }
  return 0;
}
void printCycleIfExists(dfsinfo* di, GraphInfo gi){
  printf("Not Implemented!\n");
}


int* getCycleIfExists(dfsinfo* di, GraphInfo gi){
  printf("Not Implemented!\n");
  return NULL;
}
