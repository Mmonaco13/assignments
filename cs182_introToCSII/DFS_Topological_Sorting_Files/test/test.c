#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "dfs.h"
#include "graph.h"
#include "graphio.h"
#include "topocycle.h"
#include "testUtils.h"


//simple test function
//Doesn't do the memory frees it should, so has memory leaks (feel free to add them if you want)
int main(int argc, char* argv[]){
  if(argc < 2){
    printf("Error! Must provide 1 file argument!\n");
    return 1;
  }
  printf("\n*************************\nTesting %s\n", argv[1]);
    
  char* filepath = argv[1];
  GraphInfo gi;
  gi = readGraph(filepath, MATRIX ); //could also be list
    
  dfsinfo* d = DFS(gi->graph);
  if(verifyDFS(d)){
    printf("DFS verification: PASSED\n");
  }else{
    printf("DFS verification: FAILED\n");
  }
  int * res = topocycle(gi);
  
  printf("Topological Sort: ");
  if(res == NULL){
    printf("NULL\n");
  }else{
    printTopocycle(gi);
  }
  
  
  if(res== NULL){
    printf("Topological Sort returned false! Checking cycle...\n");
    //cyclic if null
    int* cycle = getCycleIfExists(d, gi);

    //uncomment out to print cycle found
    
      printf("Cycle: ");
      if(cycle == NULL){
      printf("NULL\n");
      }else{
      printCycleIfExists(d,gi);
      }
    
    
    if(isCycle(gi->graph, cycle)){
      printf("Cycle Verification: PASSED\n");
    }else{
      printf("Cycle Verification: FAILED\n");
    }
  }else{
    if(isValidTopo(gi->graph, res)){
      printf("Topological Sort Verification: PASSED\n");
    }else{
      printf("Topological Sort Verification: FAILED\n");
    }
  }
  return 0;
}
