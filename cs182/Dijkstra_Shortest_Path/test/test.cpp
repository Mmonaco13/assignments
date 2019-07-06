
#include "topocycle.h"
#include "dijkstra.h"
#include "stdio.h"
#include "dfs.h"
bool isCyclic(Graph *g) {
    dfsinfo* di = DFS(g);
    
    struct graphinfo gi;
    gi.graph = g;
    bool res = cyclic(di, &gi);

    delete di;

    return res;
}

/**
 * Checks the correctness of a solution developed w/ Dijkstra's algorithm.
 *
 * @param g The graph used to create the solution.
 * @param res The result.
 * @param s The starting index.
 */
bool isValidDijkstra(Graph *g, struct dijkstra_result res, int s) {

    if (res.parent[s] >= 0) {
        return false;
    }

    // We expect that the given parent pointers give us a tree.
    Graph *tree = new Graph(g->numVerts(), MATRIX);

    for (int i = 0; i < g->numVerts(); i++) {
        if (i == s) continue;
        int j = res.parent[i];
    
        // Parent is out of bounds; illegal!
        if (j < 0 && !(i == s || res.dst[i] == INFINITY)) {
            printf("Vertex w/ parent pointer must have finite value\n");
        } else if (j >= g->numVerts()) {
            printf("Parent pointer %i of node %i is impossible\n", j, i);
            delete tree;
            return false;
        }
        
        float f = g->edge(j,i);
        if (f == INFINITY) {
            printf("Edge from %i to %i does not exist\n", j, i);
            // They added a non-existent edge
            delete tree;
            return false;
        }
        
        // Add the edge
        tree->addEdge(j, i, 1);
    }
    
    // Forbid cycles
    bool cyclic = isCyclic(tree);
    delete tree;
    if (cyclic) {
        printf("Parent pointers are cyclic!\n");
        return false;
    }
    
    // Now, we check for correctness of the edges
    for (int i = 0; i < g->numVerts(); i++) {
        float d = res.dst[i];
        
        int *preds = g->predecessors(i);
        for (int j = 0; preds[j] >= 0; j++) {
            // If we find a path that is better, then the solution is invalid
            if (d > g->edge(preds[j], i) + res.dst[preds[j]]) {
                printf("There exists a more optimal path from %i to %i\n", preds[j], i);
                delete preds;
                return false;
            }
        }
        delete preds;
    }

    return true;
}
int main(int argc, char* argv[]){
  if(argc < 2){
    printf("Error! Must provide 1 file argument!\n");
    return 1;
  }
  printf("\n***************************************\nTesting %s\n", argv[1]);
  char* filepath = argv[1];
  GraphInfo gi;
  gi = readGraphMakeSymm(filepath, MATRIX ); //could also be list
  
  //uncomment to print original graph
  /*printf("Original Graph:\n");
    writeGraph(gi);*/
    
  /* compute the shortest paths */
  Graph* orig = gi->graph; 
  dijkstra_result* dr = shortestPaths(gi, 0);
  //uncomment out to print shortest paths
  
    /*printf("\n A shortest path for %s:\n", filepath);
    printResult(gi, dr, 0);*/
  
  
  if (isValidDijkstra(orig, *dr, 0))
    printf("Dijkstra Verification: PASSED\n");
  else
    printf("Dijkstra Verification: FAILED\n");

  delete orig;
}


