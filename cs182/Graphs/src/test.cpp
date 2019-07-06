// test.cpp
//
// "I pledge my honor that I've abided by the Stevens Honor System."
//
// Nicholas Primamore and Matthew Monaco
//


#include "graph.h"
#include "ArrayEq.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define TOTAL_TESTS 10

bool run_test(int test_number) {
    switch(test_number) {
        case 1: {
            // test01 : Add edges for both matrix and list. Calling edge(source, target) should return the correct value. -1.0 for invalid inputs and INFINITY for nonexistent edges.
            
            Graph * matrix = new Graph(5, MATRIX);
            matrix->addEdge(0,1,10.0);
            matrix->addEdge(4,2,14.5);
            matrix->addEdge(1,3,100.2);
            matrix->addEdge(2,1,98.7);
            matrix->addEdge(3,4,2.0);
            
            if(matrix->edge(0,1) != 10.0f) return false;
            if(matrix->edge(4,2) != 14.5f) return false;
            if(matrix->edge(1,3) != 100.2f) return false;
            if(matrix->edge(2,1) != 98.7f) return false;
            if(matrix->edge(3,4) != 2.0f) return false;
            if(matrix->edge(3,1) != INFINITY) return false;
            if(matrix->edge(-1,14) != -1.0f) return false;
            
            
            Graph * list = new Graph(5, LIST);
            list->addEdge(0,1,10.0);
            list->addEdge(4,2,14.5);
            list->addEdge(1,3,100.2);
            list->addEdge(2,1,98.7);
            list->addEdge(3,4,2.0);
            
            if(list->edge(0,1) != 10.0f) return false;
            if(list->edge(4,2) != 14.5f) return false;
            if(list->edge(1,3) != 100.2f) return false;
            if(list->edge(2,1) != 98.7f) return false;
            if(list->edge(3,4) != 2.0f) return false;
            if(list->edge(3,1) != INFINITY) return false;
            if(list->edge(-1,14) != -1.0f) return false;
            
            
            delete matrix;
            delete list;
            break;
        }
            
        case 2: {
            // test 02: Construct matrices and lists and check if they have the right number of vertices (constructed correctly).
            
            Graph * defaultMatrix = new Graph(-5, 28);
            if(defaultMatrix->numVerts() != 1) return false;
            
            Graph * defaultMatrix2 = new Graph(10, 28);
            if(defaultMatrix2->numVerts() != 10) return false;
            
            Graph * matrix = new Graph(14, MATRIX);
            if(matrix->numVerts() != 14) return false;
            
            Graph * list = new Graph(2, LIST);
            if(list->numVerts() != 2) return false;
            
            delete defaultMatrix;
            delete matrix;
            delete list;
            break;
        }
            
        case 3: {
            // test03 : Delete edges from both matrix and list. Returns true if an edge was removed and if input is valid. If no edge exists, return false. Calling edge(source, target) on a deleted edge should return INFINITY.
            
            
            Graph * matrix = new Graph(5, MATRIX);
            matrix->addEdge(0,1,10.0);
            matrix->addEdge(4,2,14.5);
            matrix->addEdge(1,3,100.2);
            
            if(matrix->delEdge(4,2) != true) return false;
            if(matrix->delEdge(-3,14) != false) return false;
            if(matrix->edge(4,2) != INFINITY) return false;
            
            Graph * list = new Graph(5, LIST);
            list->addEdge(0,1,10.0);
            list->addEdge(4,2,14.5);
            list->addEdge(1,3,100.2);
            
            if(list->delEdge(4,2) != true) return false;
            if(list->delEdge(-3,14) != false) return false;
            if(list->edge(4,2) != INFINITY) return false;
            
            delete matrix;
            delete list;
            break;
        }
            
            
        case 4: {
            // test04 : Checks predecessors for a matrix graph.
            
            Graph * matrix = new Graph(5, MATRIX);
            matrix->addEdge(0,1,10.0);
            matrix->addEdge(4,2,14.5);
            matrix->addEdge(1,3,100.2);
            matrix->addEdge(2,1,98.7);
            matrix->addEdge(3,1,2.0);
            
            int* preds = new int[4];
            preds[0]= 0;
            preds[1]= 2;
            preds[2]= 3;
            preds[3]= -1;
            if(eq(matrix->predecessors(1), preds) != true) return false;
            
            delete matrix;
            break;
        }
            
            
            
        case 5: {
            // test05 : Checks predecessors for an adjacency list graph.
            
            Graph * list = new Graph(5, LIST);
            list->addEdge(0,4,10.0);
            list->addEdge(4,4,14.5);
            list->addEdge(1,4,100.2);
            list->addEdge(2,4,98.7);
            list->addEdge(3,1,2.0);
            
            int* preds = new int[5];
            preds[0]= 0;
            preds[1]= 4;
            preds[2]= 1;
            preds[3]= 2;
            preds[4]= -1;
            
            if(eq(list->predecessors(4), preds) != true) return false;
            
            delete list;
            break;
        }
            
            
            
        case 6: {
            // test06 : Checks successors for an adjacency list graph.
            
            Graph * list = new Graph(5, LIST);
            list->addEdge(0,4,10.0);
            list->addEdge(0,3,14.5);
            list->addEdge(0,2,100.2);
            list->addEdge(2,4,98.7);
            list->addEdge(3,1,2.0);
            
            int* preds = new int[5];
            preds[0]= 4;
            preds[1]= 3;
            preds[2]= 2;
            preds[3]= -1;
            preds[4]= 0;
            
            if(eq(list->successors(0), preds) != true) return false;
            
            delete list;
            break;
        }
         
        case 7: {
            // test07 : Checks successors for a matrix graph.
            
            Graph * matrix = new Graph(5, MATRIX);
            matrix->addEdge(0,4,10.0);
            matrix->addEdge(0,3,14.5);
            matrix->addEdge(0,2,100.2);
            matrix->addEdge(2,4,98.7);
            matrix->addEdge(3,1,2.0);
            
            int* preds = new int[5];
            preds[0]= 4;
            preds[1]= 3;
            preds[2]= 2;
            preds[3]= -1;
            preds[4]= 0;
            
            if(eq(matrix->successors(0), preds) != true) return false;
            
            delete matrix;
            break;
        }

        case 8: {
            // test08 :  Testing different types of cloning
            
            Graph * matrix = new Graph(5, MATRIX);
            matrix->addEdge(0,4,10.0);
            matrix->addEdge(0,3,14.5);
            matrix->addEdge(0,2,100.2);
            matrix->addEdge(2,0,98.7);
            matrix->addEdge(3,0,2.0);
            Graph *MaMa = matrix->cloneGraph(MATRIX);
            Graph *MaLi = matrix->cloneGraph(LIST);
            Graph *LiMa = matrix->cloneGraph(MATRIX);
            Graph *LiLi = matrix->cloneGraph(LIST);
            if(eq(matrix->predecessors(0), MaMa->predecessors(0)) != true) return false;
            if(eq(matrix->predecessors(0), MaLi->predecessors(0)) != true) return false;
            if(eq(matrix->predecessors(0), LiMa->predecessors(0)) != true) return false;
            if(eq(matrix->predecessors(0), LiLi->predecessors(0)) != true) return false;
            
            delete matrix;
            delete MaMa;
            delete MaLi;
            delete LiMa;
            delete LiLi;
            break;
        }

        case 9: {
            // test09 :  Trying to use functions on a null matrix
            
            Graph * matrix = new Graph(5, MATRIX);
            if(matrix->addEdge(0,4,10.0) != true) return false;
            if(matrix->delEdge(0,4) != true) return false;
            if(matrix->edge(0,4) != INFINITY) return false;
            
            int* preds = new int[5];
            preds[0]= -1;
            preds[1]= 0;
            preds[2]= 0;
            preds[3]= 0;
            preds[4]= 0;
            
            if(eq(matrix->predecessors(0), preds) != true) return false;
            if(eq(matrix->successors(0), preds) != true) return false;
            
            delete matrix;
            break;
        }
            
        case 10: {
            // test10 :  Trying to use functions on a null list
            
            Graph * list = new Graph(5, LIST);
            if(list->addEdge(0,4,10.0) != true) return false;
            if(list->delEdge(0,4) != true) return false;
            if(list->edge(0,4) != INFINITY)return false;
            
            int* preds= new int[5];
            preds[0]= -1;
            preds[1]= 0;
            preds[2]= 0;
            preds[3]= 0;
            preds[4]= 0;
            
            if(eq(list->predecessors(0), preds) != true) return false;
            if(eq(list->successors(0), preds) != true) return false;
            
            delete list;
            break;
        }
            
            
        default: {
            printf("ERROR! Test number %d was not found!\n", test_number);
            exit(1);
        }
            
    }
    // test must have passed
    return true;
}

int main() {
    int num_fail = 0;
    for (int tn = 1; tn <= TOTAL_TESTS; tn++) {
        printf("- running test # %02d ... ", tn);
        int result = run_test(tn);
        printf("%s\n", (result == true ? "succeed" : "FAIL"));
        if (result == false) num_fail++;
    }
    printf("SUMMARY: %d FAIL, %d succeed\n", num_fail, TOTAL_TESTS - num_fail);
}