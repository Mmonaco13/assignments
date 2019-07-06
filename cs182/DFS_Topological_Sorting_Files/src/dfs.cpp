#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "dfs.h"

//I pledge my honor that I have abided by the Stevens Honor System
//Matthew Monaco and Nicholas Primamore

/* Depth-first search of a graph.  Return an object with
 the discovery and finish numbers in. The parent field is the parent
 vertex, i.e., reverse of a tree edge; otherwise it is -1.
 */

/*struct dfs::dfsinfo{
 Graph* graph; // non-null graph
 int* discover; // these are arrays of length g->numVerts()
 int* finish; // finish[j] is the finish time for vertex j
 int* parent;  //vertex number of the parent
 int* finorder; // vertex numbers in ascending order of finish time
 }*/


/* Given non-null pointer to a graph, perform depth-first search.
 The returned struct and the four arrays it points to are in the
 heap (by using 'new'); freeing them is the caller's responsibility.
 */
void DFSHelp(dfsinfo *di, Graph *g, int v){
    
    int high = -99;
    for(int w = 0; w < g->numVerts(); w++){
        if(di->discover[w]>high){
            high = di->discover[w];
        }
    }
    di->discover[v] = high+1;
    
    //Search through successors and search any undiscovered nodes
    int* suc = g->successors(v);
    for(int x = 0; suc[x] != -1; x++){
        if(di->discover[suc[x]] == 0){
            di->parent[suc[x]] = v;
            DFSHelp(di, g, suc[x]);
        }
    }
    int t = 0;
    while(di->finorder[t] != -1){
        t++;
    }
    di->finish[v] = t+1;
    di->finorder[t] = v;
}

dfsinfo* DFS(Graph* g){
    //initialization

    dfsinfo *di = new dfsinfo;
    di->graph = g;
    di->discover = new int[g->numVerts()];
    di->finish = new int[g->numVerts()];
    di->parent = new int[g->numVerts()];
    di->finorder = new int[g->numVerts()];
    
    //set all value to -1, used to check if something has been discovered
    for(int x = 0; x<g->numVerts(); x++){
        di->discover[x] = 0;
        di->parent[x] = -1;
        di->finorder[x] = -1;
    }
    
    //initialize counters
    int vNum = 0;
    
    //cycles through every vertex if necessary
    while(di->finorder[g->numVerts()-1] < 0){
        
        //Im not sure if the counters should be reset to 0 here
        
        //If start node is not discovered, start a search
        if(di->discover[vNum] == 0){
            DFSHelp(di, g, vNum);
        }
        vNum++;
    }
    return di;
}
