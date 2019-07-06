#ifndef TOPOCYCLE_H
#define TOPOCYCLE_H

#include "graph.h"
#include "graphio.h"
#include "dfs.h"


/*************************
 * DFS Topological Sorting facts
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

/*
 * Internal use only; returns true if u is a proper ancestor of v
 * assume di, u, and v are all valid parameters 
 */
bool  proper_ancestor(dfsinfo* di, int u, int v);

/* Checks if a given graph is cyclic based on the dfs information.
 * For this purpose, we use Levitin's definition of a cycle, which does not include 
 * self-loops.
 * So the shortest cycle has two vertices: A B where there are edges A->B and B->A.
 * assume di and gi are all valid, as well as their contents
 */
bool cyclic(dfsinfo* di, GraphInfo gi);

/*
  Given a graphinfo struct, create a topological sort using DFS numbers
  Must use DFS to get credit!

  Should first check if a graph is a cycle (using the above method).
  If it is cyclic, return NULL.
  Else, return an array containing a valid topological sort, terminated with a -1.
  Assume gi and its contents are valid
*/
int* topocycle(GraphInfo gi);

/*
 * Print out a topological sort, using graph vertex names, NOT numbers.
 * Can/should use above method for code simplicity
 * Can use any format desired for printing
 * Print nothing/"no possible sort" if there is no topological sort
 * Assume gi and its contents are valid
 */
void printTopocycle(GraphInfo gi);

/*
 * Does multiple things:
 * 1) Check if there is a cycle (using cyclic method).
 *    If there isn't a cycle, return null.
 * 2) If there is a cycle, find it, and store it in an array, terminated with a -1.
 *    Cycle should only include each vertex 1 time in the result array.
 * 3) Return the cycle array
 * 
 * Assume di and gi are both valid, and their contents are valid
 */
int* getCycleIfExists(dfsinfo* di, GraphInfo gi);

/*
 * Does same thing as getCycleIfExists, but instead prints out the vertex names, NOT numbers.
 * Print nothing/"no cycle" if there is not cycle
 * Can use any format desired for printing
 * Can/should reuse above method for code simplicity
 * Assume di and gi, as well as their contents, are valid
 */
void printCycleIfExists(dfsinfo* di, GraphInfo gi);

#endif
