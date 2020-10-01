#ifndef TESTUTILS_H
#define TESTUTILS_H
#include "dfs.h"
#include "graph.h"
#include <algorithm>

/*call this function to check your dfs numbers and parent pointers*/
bool verifyDFS(dfsinfo* d);

/*call this function to check if a given path is actually a cycle*/
bool isCycle(Graph *g, int *path);

/*call this function to check if a given toposort is correct */
bool isValidTopo(Graph *g, int *order);

#endif
