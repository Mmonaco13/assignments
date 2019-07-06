/* Interface for dictionaries that map strings to "void pointers".
 *
 * A key is a null-terminated string.  The associated value has 
 * type void*, so it can be any pointer type and is not dereferenced 
 * by the dictionary implementation code.
 * 
 * The implementation must use AVL trees, as discussed in class and Levitin 6.3.
 */

#include "SVDict.h"
#include <string>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cstdio>
#include <cstring>

#define EMPTY_PRINT "."  /* character to indicate empty tree when printing */
#define INDENT 3         /* number of spaces to indent when printing subtrees */

/*To be implemented in SVDict.cpp
 * Should contain:
 *   std::string key
 *   void* value
 *   balance number
 *   left and right children
 */
struct SVDict::tnode{
    std::string key;
    void *value;
    int balance;
    SVDict::tnode *leftChild;
    SVDict::tnode *rightChild;
};

/* make an empty dictionary, with root = null */
SVDict::SVDict(){
    root = NULL;
}

/* Free the dictionary object and all its resources.
* Alert: the dictionary owns its copies of the keys, but does not own
* the values so those are not freed. Caller must free them.
*/
void destructHelper(SVDict::tnode *trash){
    if(trash == NULL){
        return;
    }else{
        destructHelper(trash->leftChild);
        destructHelper(trash->rightChild);
        delete(trash);
        return;
    }
}
SVDict::~SVDict(){
    destructHelper(root);
}

/* whether key is present 
 * Return 1 if present else 0.
 */
int SVDict::hasKey(std::string key){
    if(lookup(key)!=NULL){
        return 1;
    }else{
        return 0;
    }
}

int height(SVDict::tnode *n){
    if(n == NULL){
        return 0;
    }else{
        int left = height(n->leftChild);
        int right = height(n->rightChild);
        if(left > right){
            return left+1;
        }else{
            return right+1;
        }
    }
}

int balFac(SVDict::tnode *n){
    if(n == NULL){
        return 0;
    }else{
        return height(n->leftChild) - height(n->rightChild);
    }
}

/* Returns the critical node after adding a new node
 * Returns null is the tree is empty
 */
SVDict::tnode* criticalParent(std::string key, SVDict::tnode *root){
    SVDict::tnode *place = root;
    SVDict::tnode *curCrit = NULL;
    SVDict::tnode *parent = NULL;
    if(root == NULL){
        return NULL;
    }
    while(place != NULL){
        if(place->key.compare(key) == 0){
            return curCrit;
        }else if(place->key.compare(key) > 0){
            if(place->balance != 0){
                curCrit = parent;
            }
            parent = place;
            place = place->leftChild;
        }else{
            if(place->balance != 0){
                curCrit = parent;
            }
            parent = place;
            place = place->rightChild;
        }
    }
}

SVDict::tnode* balance(std::string key, SVDict::tnode *root){
    //Find the parent of the critical node
    SVDict::tnode *CP = criticalParent(key, root);
    //Determine the critical node
    SVDict::tnode *CN;
    bool parentLeft;
    if(CP == NULL){
        CN = root;
    }else{
        if(CP->key.compare(key) > 0){
            CN = CP->leftChild;
            parentLeft = true;
        }else{
            CN = CP->rightChild;
            parentLeft = false;
        }
    }
    //Update balance factors from critical node to inserted node
    SVDict::tnode *cur = CN;
    while(cur->key.compare(key) != 0){
        cur->balance = balFac(cur);
        if(cur->key.compare(key) > 0){
            cur = cur->leftChild;
        }else{
            cur = cur->rightChild;
        }
    }
    SVDict::tnode *CC;
    SVDict::tnode *sCC;
    if(!(CN->balance>1 || CN->balance<-1)){
        return root;
    }
    
    //Get the different nodes to find out which transition to use
    if(CN->key.compare(key) > 0){
        CC = CN->leftChild;
        if(CC->key.compare(key) > 0){
            sCC = CC->leftChild;
            //left left rotation
            
            CN->leftChild = CC->rightChild;
            CC->rightChild = CN;
            if(CN != root){
                if(parentLeft){
                    CP->leftChild = CC;
                }else{
                    CP->rightChild = CC;
                }
            }else{
                return CC;
            }
        }else{
            sCC = CC->rightChild;
            //left right rotation
            
            CN->leftChild = sCC->rightChild;
            sCC->rightChild = CN;
            CC->rightChild = sCC->leftChild;
            sCC->leftChild = CC;
            
            if(CN != root){
                if(parentLeft){
                    CP->leftChild = sCC;
                }else{
                    CP->rightChild = sCC;
                }
            }else{
                return sCC;
            }
        }
    }else{
        CC = CN->rightChild;
        if(CC->key.compare(key) > 0){
            sCC = CC->leftChild;
            //right left rotation
            
            CN->rightChild = sCC->leftChild;
            sCC->leftChild = CN;
            CC->leftChild = sCC->rightChild;
            sCC->rightChild = CC;
            
            if(CN != root){
                if(parentLeft){
                    CP->leftChild = sCC;
                }else{
                    CP->rightChild = sCC;
                }
            }else{
                return sCC;
            }
        }else{
            sCC = CC->rightChild;
            //right right rotation
            
            CN->rightChild = CC->leftChild;
            CC->leftChild = CN;
            
            if(CN != root){
                if(parentLeft){
                    CP->leftChild = CC;
                }else{
                    CP->rightChild = CC;
                }
            }else{
                return CC;
            }
        }
    } 
    CN->balance = balFac(CN);
    CC->balance = balFac(CC);
    sCC->balance = balFac(sCC);
    return root;
}

/* map key to val; 
 * If key not present, add it and return 0
 * If key is present, update it to have value val, and return 1
 */
SVDict::tnode* dAddOrUpdate(std::string key, void *val, SVDict::tnode *place, bool exists, SVDict::tnode *root){
    if(place->key.compare(key) == 0){
        place->value = val;
        return root;
    }
    //place->key before key
    if(place->key.compare(key) > 0){
        if(place->leftChild == NULL){
            SVDict::tnode *newNode = new SVDict::tnode;
            newNode->key = key;
            newNode->value = val;
            newNode->leftChild = NULL;
            newNode->rightChild = NULL;
            newNode->balance = 0;
            place->leftChild = newNode;
            return balance(key, root);
        }else{
            /*if(exists){
                place->balance = place->balance + 1;
            }*/
            return dAddOrUpdate(key, val, place->leftChild, exists, root);
        }
    }
    //place->key after key
    if(place->key.compare(key) < 0){
        if(place->rightChild == NULL){
            SVDict::tnode *newNode = new SVDict::tnode;
            newNode->key = key;
            newNode->value = val;
            newNode->leftChild = NULL;
            newNode->rightChild = NULL;
            newNode->balance = 0;
            place->rightChild = newNode;
            return balance(key, root);
        }else{
            /*if(exists){
                place->balance = place->balance - 1;
            }*/
            return dAddOrUpdate(key, val, place->rightChild, exists, root);
        }
    }
}
int SVDict::addOrUpdate(std::string key, void* val){
    bool exists = hasKey(key);
    if(root == NULL){
        root = new SVDict::tnode;
        root->value = val;
        root->key = key;
        root->balance = 0;
        root->leftChild = NULL;
        root->rightChild = NULL;
        return 0;
    }else{
        SVDict::tnode *place = root;
        root = dAddOrUpdate(key, val, place, exists, root);
        if(exists){
            return 1;
        }else{
            return 0;
        }
    }
}


/* return value associated with key, or NULL if key not present
 */
void* dlookup(std::string key, SVDict::tnode *place){
    //Key is Located
    if(place->key.compare(key) == 0){
            return place->value;
    }
    
    //place->key before key
    if(place->key.compare(key) > 0){
        if(place->leftChild == NULL){
            return NULL;
        }else{
            return dlookup(key, place->leftChild);
        }
    }
    
    //place->key after key
    if(place->key.compare(key) < 0){
        if(place->rightChild == NULL){
            return NULL;
        }else{
            return dlookup(key, place->rightChild);
        }
    }
    
    //This should not be hit
    return 0;
}
void* SVDict::lookup(std::string key){
    if(root == NULL){
        return NULL;
    }
    SVDict::tnode *place = root;
    return dlookup(key, place);
}



/* Remove key/val; return 1 if key was already present else 0
 * If key is present, delete it from the tree. 
 * Because this is a valid tree, you must actually remove it, and 
 * not mark it with a flag. 
 *
 * OPTIONAL. This method is optional to implement, but it MUST appear in your
 * cpp file regardless. If you don't implement it, just have an almost empty body
 * that just prints "Not Implemented" and returns -1.
 * This is extremely important, or it will not compile on our end.
 *
 * This method is very difficult if done correctly, and thus will carry 10 bonus 
 * points for a successful implementation.
 */
int SVDict::remKey(std::string key){
    printf("Not Implemented");
    return -1;
}


/* Print the keys, in pre-order, to standard output. 
 * Print each key, preceded by some spaces (specified below), and followed by \n.  
 * If a subtree is empty, print EMPTY_PRINT. (not the word, but the variable).
 * Nothing else should be printed. *IMPORTANT* 
 * The number of preceding spaces should indicate the depth of the
 * tree, INDENT spaces per level, with no spaces for the root. 
 * Hint: write a recursive helper function that has an integer 
 * parameter for the depth.
 */
void preorderHelper(SVDict::tnode *currentNode, int depth){
    for(int i = 0; i < INDENT; i++){
        printf("%s", " ");
    }
    if(depth == 0){
        printf("%s\n", currentNode->key.c_str());
    }
    else{
        for(int i = 0; i < depth; i++){
            printf("%s", " ");
        }
        if(currentNode == NULL){
            printf("%s\n", EMPTY_PRINT);
            return;
        }
        else{
            printf("%s\n", currentNode->key.c_str());
        }
    }
    depth++;
    preorderHelper(currentNode->leftChild, depth);
    preorderHelper(currentNode->rightChild, depth);
}

/* Print the keys, in pre-order, to standard output.
 * Print each key, preceded by some spaces (specified below), and followed by \n.
 * If a subtree is empty, print EMPTY_PRINT. (not the word, but the variable).
 * Nothing else should be printed. *IMPORTANT*
 * The number of preceding spaces should indicate the depth of the
 * tree, INDENT spaces per level, with no spaces for the root.
 * Hint: write a recursive helper function that has an integer
 * parameter for the depth.
 */
void SVDict::preorderKeys(){
    preorderHelper(root, 0);
}