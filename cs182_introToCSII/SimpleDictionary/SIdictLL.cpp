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
 * Determines if the key is present in the list 
 * param key: search name of the node
 * Return 1 if key is present
 * Return 0 if key is not present
*/
int Dict::hasKey(string key){
    DictNode *place = first;
    if(first == NULL){
        return 0;
    }
    while(true){
        if(place->key.compare(key) == 0){
            return 1;    
        }else if(place->next == NULL){
            return 0;
        }else{
            place = place->next;   
        }
    }
}

/*  
 * Add or update given key with the given value 
 * param key: search name of the node
 * param val: value of the node
 * Return 1 if key is present
 * Reutrn 0 if key is not present
*/
int Dict::addOrUpdate(string key, int val){
    if(first == NULL){
        first = new DictNode;
        first->value = val;
        first->key = key;
        first->next = NULL;
        return 0;
    }
    DictNode *place = first;
    while(true){
        if(place->key.compare(key) == 0){
            place->value = val;
            return 1;
        }else if(place->next == NULL){
            DictNode *newNode = new DictNode;
            newNode->key = key;
            newNode->value = val;
            newNode->next = NULL;
            place->next = newNode;
            return 0;
        }
        place = place->next;
    }
}
  
/*  
 * Get the value of a node
 * param key: Search name of the node
 * Return value of the node
 * Precondition: key is present 
*/
int Dict::lookup(string key){
    DictNode *place = first;
    while(true){
        if(place->key.compare(key) == 0){
            return place->value;
        }
        place = place->next;
    }
}
  
/* 
 * Remove a node with a given key
 * param key: Search name of the node
 * Return 1 if node was removed
 * Precondition: key is present 
*/
int Dict::remKey(string key){
    if(first->key.compare(key) == 0){
        int num = first->value;
        DictNode *trash = first;
        first = first->next;
        delete(trash);
        return num;
    }
    DictNode *place = first;
    DictNode *prev = first;
    while(true){
        if(place->key.compare(key) == 0){
            int num2 = place->value;
            prev->next = place->next;
            delete(place);
            return num2;
        }
        prev = place;
        place = place->next;
    }
}