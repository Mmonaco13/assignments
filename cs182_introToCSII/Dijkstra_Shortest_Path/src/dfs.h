#ifndef DFS_H
#define DFS_H
#include "graph.h"

/* Depth-first search of a graph.  Return an object with
   the discovery and finish numbers in. The parent field is the parent
   vertex, i.e., reverse of a tree edge; otherwise it is -1.
*/

struct dfsinfo {
  Graph* graph; // non-null graph
  int* discover; // these are arrays of length g->numVerts()
  int* finish; // finish[j] is the finish time for vertex j
  int* parent;  //vertex number of the parent
  int* finorder; // vertex numbers in ascending order of finish time
};


/* Given non-null pointer to a graph, perform depth-first search.
   The returned struct and the four arrays it points to are in the
   heap (by using 'new'); freeing them is the caller's responsibility.
*/
dfsinfo* DFS(Graph* g);


#endif
