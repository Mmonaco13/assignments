//  graph.cpp
//
//  "I pledge my honor that I've abided by the Stevens Honor System."
//
//  Nicholas Primamore and Matthew Monaco
//

#include <stdio.h>
#include "graph.h"
#include <iostream>
#include <string>
#include <math.h>
using namespace std;


//implementing Node defined in graph.h for adjacency list
struct Graph :: Node{
    int value;
    float edgeWeight;
    Node* next;
};

/* Make an empty graph with n vertices (empty means all edges either set to INFINITY or NULL,
 depending on representation), using either adjacency matrix
 or adjacency lists depending on whether rep==MATRIX or rep==LIST.
 if n <1, set numVertices to 1
 if rep is not MATRIX or LIST, defaults to MATRIX
 */
Graph::Graph(int n, int rep){
    if(n < 1){
        numVertices = 1;
    }
    else{
        numVertices = n;
    }
    if(rep == LIST){
        type = LIST;
        Graph::Node** listArray = new Graph::Node*[numVertices];
        list = listArray;
        for(int index = 0; index < numVertices; index++){
            (*(list + index)) = NULL;
        }
        matrix = NULL;
    }
    else{
        type = MATRIX;
        float* matrixArray = new float[numVertices * numVertices]; // 1D array implementation
        matrix = matrixArray;
        for(int index = 0; index < (numVertices * numVertices); index++){
            (*(matrix + index)) = INFINITY;
        }
        list = NULL;
    }
}

/* free the graph object and ALL its resources.
 */
Graph::~Graph(){
    //for list travel through eaxch node in lists, then delete array
    //for matrix just delete the array
    if(type == MATRIX && matrix != NULL){
        delete matrix;
    }
    else{
        if(list != NULL){
            for(int index = 0; index < numVertices; index++){
                while(*(list + index) != NULL){
                    Graph::Node * temp = *(list + index);
                    *(list + index) = (*(list + index))->next;
                    delete temp;
                }
            }
            delete list;
        }
    }
}

/* make a DEEP copy of g, but using the representation
 specified by rep (which is assumed to be MATRIX or LIST)
 Everything should be copied over, not just references
 I.E. a change in the first graph should not change the second graph
 If rep is not MATRIX or LIST, return NULL
 */
Graph* Graph::cloneGraph(int rep){
    if(rep == MATRIX){
        if(type == MATRIX){
            Graph *repM = new Graph(numVertices, MATRIX); 
            for(int index = 0; index < (numVertices * numVertices); index++){
                if((*(matrix + index)) != INFINITY){
                    //row is the start of the edge
                    int row = index / numVertices;
                    int column = index % numVertices;
                    repM->addEdge(row, column, *(matrix + index));
                }
            }
            return repM;
        }else{
            
            //Make the new matrix
            Graph *newG = new Graph(numVertices, MATRIX);
            
            //Fill in the existing edges
            for(int index = 0; index < numVertices; index++){
                
                if(list[index] != NULL){
                    
                    Graph::Node *current = *(list + index);
                    bool cont = true;
                    while(cont){
                        
                        newG->addEdge(index, current->value, current->edgeWeight);
                        
                         if(current->next != NULL){
                            current = current->next;   
                         }else{
                            cont = false;   
                         }
                    }
                }
            }             
            return newG;
        }
        
    }else if(rep == LIST){
        if(type == LIST){
            Graph *repL = new Graph(numVertices, LIST); 
            for(int index = 0; index < numVertices; index++){
                if(list[index] != NULL){
                    Graph::Node *current = *(list + index);
                    bool cont = true;
                    while(cont){
                         repL->addEdge(index, current->value, current->edgeWeight);
                         if(current->next != NULL){
                            current = current->next;   
                         }else{
                            cont = false;   
                         }
                    }
                }
            }
            return repL;
        }else{
            //Create the list
            Graph *newL = new Graph(numVertices, LIST);
            
            //Transfer existing edges
            for(int index = 0; index < (numVertices * numVertices); index++){
                if((*(matrix + index)) != INFINITY){
                    
                    //row is the start of the edge
                    int row = index / numVertices;
                    int column = index % numVertices;

                    newL->addEdge(row, column, *(matrix + index));
                }
            }
            return newL;
        }
        
    }else{
        return NULL;
    }
}

/* return number of vertices.
 Note that this is needed since the property numVerts is private*/
int Graph :: numVerts(){
    return numVertices;
}

/* add edge from source to target with weight w, and return
 true, if source and target are valid vertex numbers and
 there was no edge from source to target initially.
 Otherwise if source or target are invalid, or the edge already exists,
 make no change and return false. If the edge already exists, DO NOT UPDATE IT! Just return false
 if w is INFINITY or negative, do nothing, and return false.
 */
bool Graph::addEdge( int source, int target, float w){
    //invalid cases:
    if(w == INFINITY || w < 0) return false;
    
    //source = source - 1;
    //target = target - 1;
    if(source < 0 || source > numVertices-1) return false;
    if(target < 0 || target > numVertices-1) return false;
    
    //FOR ADJACENCY LIST:
    //think of each slot in the array as "head" pointers, they are all NULL at first
    //check if NULL first before checking values and traversing list
    //if edge doesnt exist, dont care about NULL
    if(type == LIST && list != NULL){
        if(*(list+source) == NULL){
            list[source] = new Graph::Node;
            list[source]->value = target;
            list[source]->edgeWeight = w;
            list[source]->next = NULL;
            return true;
        }
        Graph::Node *place = *(list+source);
        while(true){
            if(place->value == target){
                return false;
            }else if(place->next == NULL){
                Graph::Node *newNode = new Graph::Node;
                place->next = newNode;
                newNode->value = target;
                newNode->edgeWeight = w;
                newNode->next = NULL;
                return true;
            }else{
                place = place->next;   
            }
        }
    }
    else{ //it's a matrix
        if(matrix != NULL){
            float val = (*(matrix + (numVertices*source+target)));
            //edge already exists
            if(val != INFINITY ){
                return false;
            }
            else{
                (*(matrix + (numVertices*source+target))) = w;
                return true;
            }
        }
    }
}


/* delete edge from source to target, and return
 true, if there was an edge from source to target, and both source and target are valid vertex numbers.
 Otherwise, make no change and return false.
 */
bool Graph::delEdge(int source, int target){
    //invalid vertices:
    if(source < 0 || source > numVertices - 1) return false;
    if(target < 0 || target > numVertices - 1) return false;
    
    if(type == LIST && list != NULL){
        if(*(list+source)==NULL){
            return false;
        }
        if(list[source]->value == target){
            Graph::Node *temp = list[source];
            list[source] = list[source]->next;
            delete temp;
            return true;
        }
        Graph::Node *place = list[source];
        Graph::Node *prevPlace = new Graph::Node;
        while(true){
            if(place->value == target){
                prevPlace->next = place->next;
                delete place;
                return true;
            }else if(place->next == NULL){
                return false;
            }else{
                prevPlace = place;
                place = place->next;
            }
        }
    }
    else{ //it's a matrix
        if(matrix != NULL){
            float val = (*(matrix + (numVertices*source+target)));
            if(val != INFINITY){
                (*(matrix + (numVertices*source+target))) = INFINITY;
                return true;
            }
            else{
                return false;
            }
        }
    }
}

/* return weight of the edge from source to target,
 if there is one; otherwise return INFINITY. (part of the math.h library)
 Return -1.0 if source or target are not valid vertex numbers.
 */
float Graph::edge( int source, int target){
    //invalid vertices:
    if(source < 0 || source > numVertices - 1) return -1.0;
    if(target < 0 || target > numVertices - 1) return -1.0;
    
    if(type == LIST && list != NULL){
       if(*(list + source) == NULL){
            return INFINITY;   
       }
       Graph::Node *place = *(list+source);
       while(true){
            if(place->value == target){
                return place->edgeWeight;
            }else if(place->next == NULL){
                return INFINITY;
            }else{
                place = place->next;
            }
       }
    }
    else{ //it's a matrix
        if(matrix != NULL){
            float val = (*(matrix + (numVertices*source+target)));
            if(val == INFINITY){
                return INFINITY;
            }
            else{
                return val;
            }
        }
    }
    return INFINITY;
}
/* return a freshly new'd array with the successor
 vertices of source, if any, followed by an entry with -1
 to indicate end of sequence.
 Make sure your returned array has enough spots for the number of successors, and the -1.
 If there are no successors, the array should only contain a -1
 If source is not a valid vertex number, return NULL
 Ownersip: the caller is responsible for deleting the array in their file.
 You should not make any delete call in your file graph relating to successors, but rather in your test file
 */
int* Graph::successors( int source){
    if(source < 0 || source > numVertices - 1) return NULL;
    
    int *sucArray = new int[numVertices+1];
    if(type == LIST && list != NULL){
        int arrCount = 0;
        if(*(list+source) == NULL){
            sucArray[0] = -1;
            return sucArray;   
        }else{
            Graph::Node *place = *(list + source);
            while(true){
                sucArray[arrCount] = place->value;
                arrCount++;
                if(place->next == NULL){
                    sucArray[arrCount] = -1;
                    return sucArray;   
                }else{
                    place = place->next;   
                }
            }
        }
    }else if(matrix != NULL){
        int *matSuc = new int[numVertices+1];
        int arrCount = 0;
        for(int i = (numVertices * source); i < (numVertices * (source+1)); i++){
            if(matrix[i] != INFINITY){
                matSuc[arrCount] = i % numVertices;
                arrCount++;
            }
        }
        matSuc[arrCount] = -1;
        return matSuc;
    }
    sucArray[0] = -1;
    return sucArray;
    
}

/*  return a freshly new'd array with the predecessor
 vertices of source, if any, followed by an entry with -1
 to indicate end of sequence.
 Make sure your returned array has enough spots for the number of successors, and the -1.
 If there are no successors, the array should only contain a -1
 If source is not a valid vertex number, return NULL
 Ownersip: the caller is responsible for deleting the array in their file.
 You should not make any delete call in your file relating to successors
 */
int* Graph::predecessors( int target){
    if(target < 0 || target > numVertices - 1) return NULL;
    int arrCount = 0;
    int *predArray = new int[numVertices+1];
    
    if(type == LIST && list != NULL){
        for(int index = 0; index < numVertices; index++){
            if(list[index] != NULL){
                Graph::Node *place = list[index];
                bool cont = true;
                while(cont){
                    if(place->value == target){
                        predArray[arrCount] = index;
                        arrCount++;
                        cont = false;
                    }else if(place->next == NULL){
                        cont = false;
                    }
                    place = place->next;
                } 
            }
        }
        predArray[arrCount] = -1;
        return predArray;
    }else if(matrix != NULL){
        int arrCount = 0;
        for(int index = 0; index < numVertices; index++){
            int current = (numVertices * index) + target;
            if(matrix[current] != INFINITY){
                predArray[arrCount] = index;
                arrCount++;
            }
        }
        predArray[arrCount] = -1;
        return predArray;
    }
    predArray[0] = -1;
    return predArray;
}