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
    DictNode *next;
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
        Dict::DictNode *temp = trash;
        trash = trash->next;
        delete temp;
        destructHelper(trash);
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
int dHasKey(string key, Dict::DictNode *place){
    if(place->key.compare(key) == 0){
        return 1;    
    }else if(place->next == NULL){
        return 0;
    }else{
        return dHasKey(key, place->next);   
    }
}
int Dict::hasKey(string key){
    if(key.compare("")==0){
        return 0;
    }
    DictNode *place = first;
    if(first == NULL){
        return 0;
    }else{
        return dHasKey(key, place);
    }
}



/*  
 * Add or update given key with the given value 
 * param key: search name of the node
 * param val: value of the node
 * Return 1 if key is present
 * Return 0 if key is not present / something is null
 * Return -1 if key is empty or val is null
 */
int dAddOrUpdate(string key, int val, Dict::DictNode *place){
    if(place->key.compare(key) == 0){
        place->value = val;
        return 1;
    }else if(place->next == NULL){
        Dict::DictNode *newNode = new Dict::DictNode;
        newNode->key = key;
        newNode->value = val;
        newNode->next = NULL;
        place->next = newNode;
        return 0;
    }else{
        return dAddOrUpdate(key, val, place->next);
    }
}
int Dict::addOrUpdate(string key, int val){
    if(key.compare("")==0){
        return -1;
    }
    if(first == NULL){
        first = new DictNode;
        first->value = val;
        first->key = key;
        first->next = NULL;
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
 * Returns 0 if key is not present
*/
int dLookup(string key, Dict::DictNode *place){
    if(place->key.compare(key) == 0){
        return place->value;
    }else if(place->next == NULL){
        return 0;
    }else{
        return dLookup(key, place->next);
    }   
}
int Dict::lookup(string key){
    if(key.compare("")==0){
        return 0;
    }
    if(first == NULL){
        return 0;
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
int dRemKey(string key, Dict::DictNode *prev, Dict::DictNode *place){
    if(place->key.compare(key) == 0){
        int num2 = place->value;
        prev->next = place->next;
        delete place;
        return 1;
    }else if(place->next == NULL){
        return 0;
    }else{
        prev = place;
        place = place->next;  
        return dRemKey( key, prev, place);
    }
}
int Dict::remKey(string key){
    if(key.compare("")==0){
        return -1;
    }
    if(first == NULL){
        return 0;
    }else if(first->key.compare(key) == 0){
        int num = first->value;
        DictNode *trash = first;
        first = first->next;
        delete trash;
        return 1;
    }else{
        DictNode *place = first;
        DictNode *prev = first;
        return dRemKey(key, prev, place);
    }
}

