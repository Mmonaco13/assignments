#ifndef SIDICT_H
#define SIDICT_H

#include <string>

/* Simple interface for dictionaries that map strings to integers. */

using namespace std;


class Dict{


  
 public:

   /*To be implemented in the c++ class*/
  struct DictNode;
  
  /* Constructor; make an empty one, which initializes our first pointer to null */
  Dict();

  /* Destructor; delete the entire structure, and clean up all memory that was allocated
   */
  ~Dict();
  
  /* whether key is present. 
     Returns 1 if key is present, 0, if not present*/
  int hasKey(string key);
  
  /* map key to val; return 1 if 
     key was already present (and update the node with the new val) 
     else 0 (and insert the new node) 
     An empty key *is* considered a valid input, and can be inserted into the data structure,
     just like any other key. You shouldn't return an error for the empty string "".
  */
  int addOrUpdate(string key, int val);
  
  /* get value associated with key
     Precondition: key is present 
     Returns value of the key. You do not need to check the precondition, but
     if you do, return -1 if the key is not found
  */
  int lookup(string key);
  
  /* remove key/val, and return 1 if the node is successfully removed
     Precondition: key is present. You do not need to check the precondition, but
     if you do, return -1 if the key is not found */
  int remKey(string key);

   private:
  
  /* The pointer to the first node in the list*/
  DictNode* first;
  
};
#endif
