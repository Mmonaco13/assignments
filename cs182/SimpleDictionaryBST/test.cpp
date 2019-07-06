#include "SIdict.h"
#include <stdio.h>
#include <stdlib.h>

#define TOTAL_TESTS 12

bool run_test(int test_number) {
  switch(test_number) {
  case 1: {
    // test01 : if a key is removed, it should not be present
    Dict* d = new Dict();
    d->addOrUpdate("abc", 42);
    d->remKey("abc");
    if(d->hasKey("abc") != 0){  //should return 0, key is not present
      return false;
    }
    delete d;
    break;
  }
  case 2: {
    // test02 : Find a key in the middle of a tree
    Dict* d = new Dict();
    d->addOrUpdate("abc", 42);
    d->addOrUpdate("def", 30);
    d->addOrUpdate("ghi", 15);
    if(d->hasKey("def") != 1){  //should return 1, key is present
      return false;
    }
    delete d;
    break;
  }
  case 3: {
    // test03 : Find a key that is a leaf
    Dict* d = new Dict();
    d->addOrUpdate("abc", 42);
    d->addOrUpdate("def", 30);
    d->addOrUpdate("ghi", 15);
    if(d->hasKey("ghi") != 1){  //should return 1, key is present
      return false;
    }
    delete d;
    break;
  }
  case 4: {
    // test04 : Find a key at the beginning of a list
    Dict* d = new Dict();
    d->addOrUpdate("abc", 42);
    d->addOrUpdate("def", 30);
    d->addOrUpdate("ghi", 15);
    if(d->hasKey("abc") != 1){  //should return 1, key is present
      return false;
    }
    delete d;
    break;
  }
  case 5: {
    // test05 : Lookup a null tree
    Dict* d = new Dict();
    if(d->lookup("abc") != -1){  //should return -1, tree is null
      return false;
    }
    delete d;
    break;
  }
  case 6: {
    // test06 : lookup key that isnt in list
    Dict* d = new Dict();
    d->addOrUpdate("abc", 42);
    if(d->lookup("def") != -1){  //should return -1, key not present
      return false;
    }
    delete d;
    break;
  }
  case 7: {
    // test07 : Remove key from null tree
    Dict* d = new Dict();
    if(d->remKey("abc") != -1){  //should return -1, tree is null
      return false;
    }
    delete d;
    break;
  }
  case 8: {
    // test08 : remove key not in tree
    Dict* d = new Dict();
    d->addOrUpdate("abc", 42);
    if(d->remKey("def") != -1){  //should return -1, key not present
      return false;
    }
    delete d;
    break;
  }
  case 9: {
    // test09 : Empty String
    Dict* d = new Dict();
    d->addOrUpdate("", 42);
    if(d->remKey("") != 1){  //should return 1, key is present
      return false;
    }
    delete d;
    break;
  }
  case 10: {
    // test10: Access a node whose parent was removed  
    Dict* d = new Dict();
    d->addOrUpdate("abc", 42);
    d->addOrUpdate("def", 13);
    d->remKey("abc");
    if(d->lookup("def") != 13){  //should return 13, key is present
      return false;
    }
    delete d;
    break;
  }
  case 11: {
    // test11 : Re-add a key
    Dict* d = new Dict();
    d->addOrUpdate("abc", 42);
    d->remKey("abc");
    d->addOrUpdate("abc", 13);
    if(d->lookup("abc") != 13){  //should return 13, key is present
      return false;
    }
    delete d;
    break;
  }
  case 12: {
    // test12 : Add a key to a flagged node
    Dict* d = new Dict();
    d->addOrUpdate("abc", 42);
    d->remKey("abc");
    d->addOrUpdate("def", 13);
    if(d->lookup("def") != 13){  //should return 13, key is present
      return false;
    }
    delete d;
    break;
  }

  //Check functions for empty string
  default: {
    printf("ERROR! Test number %d was not found!\n", test_number);
    exit(1);
  }
    
  }
  // test must have passed.
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

  
