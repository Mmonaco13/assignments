/* Interface for dictionaries that map strings to "void pointers".
 *
 * A key is a null-terminated string.  The associated value has 
 * type void*, so it can be any pointer type and is not dereferenced 
 * by the dictionary implementation code.
 * 
 * The implementation must use AVL trees, as discussed in class and Levitin 6.3.
 */

#ifndef SVDDICT_H
#define SVDDICT_H

#include <string>

#define EMPTY_PRINT "."  /* character to indicate empty tree when printing */
#define INDENT 3         /* number of spaces to indent when printing subtrees */

class SVDict {

  
 public:

  /*To be implemented in SVDict.cpp
   * Should contain:
   *   std::string key
   *   void* value
   *   balance number
   *   left and right children
   */
  struct tnode;
  
  /* make an empty dictionary, with root = null */
  SVDict();

  /* Free the dictionary object and all its resources.
   * Alert: the dictionary owns its copies of the keys, but does not own
   * the values so those are not freed. Caller must free them.
   */
  ~SVDict();



  /* whether key is present 
   * Return 1 if present else 0.
   */
  int hasKey(std::string key);


  /* map key to val; 
   * If key not present, add it and return 0
   * If key is present, update it to have value val, and return 1
   */
  int addOrUpdate(std::string key, void* val);


  /* return value associated with key, or NULL if key not present
   */
  void* lookup(std::string key);


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
  int remKey(std::string key);


  /* Print the keys, in pre-order, to standard output. 
   * Print each key, preceded by some spaces (specified below), and followed by \n.  
   * If a subtree is empty, print EMPTY_PRINT. (not the word, but the variable).
   * Nothing else should be printed. *IMPORTANT* 
   * The number of preceding spaces should indicate the depth of the
   * tree, INDENT spaces per level, with no spaces for the root. 
   * Hint: write a recursive helper function that has an integer 
   * parameter for the depth.
   */
  void preorderKeys();

 private:
  
  tnode* root;
};

#endif 
