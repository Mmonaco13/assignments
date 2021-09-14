#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include <stdio.h>
#include "graphio.h"
#include "dijkstra.h"
#include "minprio.h"

//Matthew Monaco
//I pledge my honor that I have abided by the Stevens Honor System.
struct content{
    int node;
    float currentDistance;
};

int compare(void* lhs, void* rhs){
    //handle what type of pointer (cast to my struct)
    float left = ((content*)lhs)->currentDistance;
    float right = ((content*)rhs)->currentDistance;
    
    if(left < right){
        return -1;
    }
    else if(left > right){
        return 1;
    }
    else return 0;
}

/*
 * Run dijkstra's algorithm to find the shortest path to all vertices
 * starting from vertex s, and return the populated arrays
 * Assume GI is non-null and valid, and that s is in the graph
 */
dijkstra_result* shortestPaths(GraphInfo GI, int s){
    int numVertices = GI->graph->numVerts();
    
    MinPrio *Q = new MinPrio(&compare, numVertices);
    MinPrio::handle **h = new MinPrio::handle*[numVertices];
    
    dijkstra_result *res = new dijkstra_result;
    res->parent = new int[numVertices];
    res->dst = new float[numVertices];
    res->dst[s] = 0.0;
    
    content *c = new content;
    c->node = s;
    c->currentDistance = res->dst[s];
    h[s] = Q->enqueue(c);
    for(int x=0; x<numVertices; x++){
        if(x != s){
            res->dst[x] = INFINITY;
            //printf("%f\n",res->dst[x]);
            content *ct = new content;
            ct->node = x;
            ct->currentDistance = res->dst[x];
            h[x] = Q->enqueue(ct);
        }
        res->parent[x] = -1;
    }
    while(Q->nonempty()){
        content *con = ((content*)(Q->dequeueMin()));
        int v = con->node;
        res->dst[v] = con->currentDistance;
        h[v] = NULL;
        int* suc = GI->graph->successors(v);
        for(int index=0; suc[index]!=-1; index++){
            if(res->dst[v] + GI->graph->edge(v,suc[index]) < res->dst[suc[index]]){
                res->dst[suc[index]] = res->dst[v] + GI->graph->edge(v,suc[index]);
                res->parent[suc[index]] = v;
                ((content*)h[suc[index]]->content)->currentDistance = res->dst[suc[index]];
                Q->decreasedKey(h[suc[index]]);
            }
        }
    }
    return res;
}



/* Print the lengths and predecessor in a shortest path from s,
 * for each vertex that is reachable from s.  (For vertices that  
 * are not reachable from s, print nothing.)  Also print the 
 * name of the predecessor in a shortest path.
 *
 * Assume GI is non-null and valid.
 * Assume the source number, s, is in the graph GI->graph.
 * Assume that dr is non-null, and valid
 * 
 * Use Dijkstra's algorithm and an implementation of minprio.h.
 * Use a format like this to show length and predecessor:
 * 
 * Shortest paths from vertex A 
 *   to B is 9.000000 via E
 *   to C is 10.000000 via B
 *   to D is 6.000000 via A
 *   to E is 7.000000 via A
 *   to F is 15.000000 via C
 */
void printResult(GraphInfo GI, dijkstra_result* dre, int s){
    dijkstra_result *dr = dre;
    int numVertices = GI->graph->numVerts();
    printf("Shortest paths from vertex %s\n",GI->vertnames[s]);
    for(int x=1; x<numVertices; x++){
        if(dr->dst[x] != INFINITY){
            printf("to %s is %f via %s\n", GI->vertnames[x], dr->dst[x], GI->vertnames[dr->parent[x]]);
        }
    }
    return;
}
