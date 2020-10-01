#ifndef SIDICT_H
#define SIDICT_H

#include <string>

/* Simple interface for dictionaries that map strings to integers. */

/* compare this line to imports in java
 * This makes it so you can use std libraries without using 
 * the fully qualified name ( std::string..., like java.util.Arrays, etc) */
using namespace std;


class Dict{


  
 public:

   /*Our node in our linked list
   * Will contain key, value, and pointer to next node
   * To be implemented in the c++ class 
   * A struct can be thought of like a class*/
  struct DictNode;
  
  /* Constructor; make an empty one, which initializes our first pointer to null */
  Dict();

  /* Destructor; delete the entire structure, and clean up all memory that was allocated
   */
  ~Dict();
  
  /* whether key is present 
     This and the other functions assume 
     d non-null. */
  int hasKey(string key);
  
  /* map key to val; return 1 if 
     key was already present else 0 */
  int addOrUpdate(string key, int val);
  
  /* get value associated with key
     Precondition: key is present */
  int lookup(string key);
  
  /* remove key/val
     Precondition: key is present */
  int remKey(string key);

   private:
  /* The pointer to the first node in the list*/
  DictNode* first;
  
};
#endif
