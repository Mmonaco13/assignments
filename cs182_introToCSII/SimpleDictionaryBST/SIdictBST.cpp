#include "SIdict.h"
#include <iostream>
//I pledge my honor that I have abided by the Stevens Honor System.
//Matthew Monaco

/*  
 * Node of the Linked List
 * int value: value of the node
 * string key: search name of the node
 * DictNode *next: pointer to the next node in the list
*/
struct Dict::DictNode{
    int value;
    string key;
    DictNode *leftChild;
    DictNode *rightChild;
    bool removed;
};

/* 
 * Constructor
 * makes the first pointer = null
*/
Dict::Dict(){
    first = NULL;
}

/* 
 * Destructor
 * Deallocates all allocated memory
*/
void destructHelper(Dict::DictNode *trash){
    if(trash == NULL){
        return;
    }else{
        destructHelper(trash->leftChild);
        destructHelper(trash->rightChild);
        delete(trash);
        return;
    }
}
Dict::~Dict(){
    destructHelper(first);
}


/* 
 * Determines if the key is present in the list 
 * param key: search name of the node
 * Return 1 if key is present
 * Return 0 if key is not present
*/
int Dict::hasKey(string key){
    if(lookup(key)!=-1){
        return 1;
    }else{
        return 0;
    }
}



/*  
 * Add or update given key with the given value 
 * param key: search name of the node
 * param val: value of the node
 * Return 1 if key is present
 * Return 0 if key is not present / something is null
 */
int dAddOrUpdate(string key, int val, Dict::DictNode *place){
    if(place->key.compare(key) == 0){
        place->value = val;
        place->removed = false;
        return 1;
    }
    //place->key before key
    if(place->key.compare(key) > 0){
        if(place->leftChild == NULL){
            Dict::DictNode *newNode = new Dict::DictNode;
            newNode->key = key;
            newNode->value = val;
            newNode->leftChild = NULL;
            newNode->rightChild = NULL;
            newNode->removed = false;
            place->leftChild = newNode;
            return 0;
        }else{
            return dAddOrUpdate(key, val, place->leftChild);
        }
    }
    //place->key after key
    if(place->key.compare(key) < 0){
        if(place->rightChild == NULL){
            Dict::DictNode *newNode = new Dict::DictNode;
            newNode->key = key;
            newNode->value = val;
            newNode->leftChild = NULL;
            newNode->rightChild = NULL;
            newNode->removed = false;
            place->rightChild = newNode;
            return 0;
        }else{
            return dAddOrUpdate(key, val, place->rightChild);
        }
    }
}
int Dict::addOrUpdate(string key, int val){
    if(first == NULL){
        first = new DictNode;
        first->value = val;
        first->key = key;
        first->removed = false;
        first->leftChild = NULL;
        first->rightChild = NULL;
        return 0;
    }else{
        DictNode *place = first;
        return dAddOrUpdate(key, val, place);
    }
}


  
/*  
 * Get the value of a node
 * param key: Search name of the node
 * Return value of the node
 * Returns -1 if key is not present
*/
int dLookup(string key, Dict::DictNode *place){
    if(place->key.compare(key) == 0){
        if(place->removed){
            return -1;
        }else{
            return place->value;
        }
    }
    //place->key before key
    if(place->key.compare(key) > 0){
        if(place->leftChild == NULL){
            return -1;
        }else{
            return dLookup(key, place->leftChild);
        }
    }
    //place->key after key
    if(place->key.compare(key) < 0){
        if(place->rightChild == NULL){
            return -1;
        }else{
            return dLookup(key, place->rightChild);
        }
    }
    //This should not be hit
    return 0;
}
int Dict::lookup(string key){
    if(first == NULL){
        return -1;
    }
    DictNode *place = first;
    return dLookup(key, place);
}


  
/* 
 * Remove a node with a given key
 * param key: Search name of the node
 * Return 1 if node was removed
 * Return -1 if key is not present
*/
int dRemKey(string key, Dict::DictNode *place){
    if(place->key.compare(key) == 0){
        place->removed = true;
        return 1;
    }
    if(place->key.compare(key) > 0){
        if(place->leftChild == NULL){
            return -1;
        }else{
            return dRemKey(key, place->leftChild);
        }
    }
    //place->key after key
    if(place->key.compare(key) < 0){
        if(place->rightChild == NULL){
            return -1;
        }else{
            return dRemKey(key, place->rightChild);
        }
    }
}
int Dict::remKey(string key){
    if(first == NULL){
        return -1;
    }else if(first->key.compare(key) == 0){
        first->removed = true;
        return 1;
    }else{
        DictNode *place = first;
        return dRemKey(key, place);
    }
}

