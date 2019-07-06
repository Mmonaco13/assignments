#include "SIdict.h"
#include <stdio.h>
#include <stdlib.h>

#define TOTAL_TESTS 13

bool run_test(int test_number) {
switch(test_number) {
  case 1: {
    // test01 : should not have a key that hasn't been added
    Dict* d = new Dict();
    if(d->hasKey("abc")){  //should return false, since doesn't exist
      return false;
    }
    delete d;
    break;
  }
  case 2: {
    // test02 : if you add a key, it should be there
    Dict* d = new Dict();
    if(d->addOrUpdate("abc", 1)!=0){
      return false;
    }
    if(!d->hasKey("abc")){
      return false;
    }
    delete d;
    break;
  }
  case 3: {
    // test03 : if you add a key/value, should get back the value
    Dict* d = new Dict();
    d->addOrUpdate("abc", 42);
    if(d->lookup("abc") != 42) {
      return false;
    } 
    delete d;
    break;
  }
  case 4: {
    // test04 : if you add a key/value, should remove it
    Dict* d = new Dict();
    d->addOrUpdate("abc", 42);
    d->remKey("abc");
    if(d->hasKey("abc") != 0){  //should return 0, key was removed
      return false;
    }
    delete d;
    break;
  }
  case 5: {
    // test05 : Find a key in the middle of a list
    Dict* d = new Dict();
    d->addOrUpdate("abc", 42);
    d->addOrUpdate("def", 30);
    d->addOrUpdate("ghi", 15);
    if(d->hasKey("def") != 1){  //should return 1 if it is in the list
      return false;
    }
    delete d;
    break;
  }
  case 6: {
    // test06 : Find a key at the end of a list
    Dict* d = new Dict();
    d->addOrUpdate("abc", 42);
    d->addOrUpdate("def", 30);
    d->addOrUpdate("ghi", 15);
    if(d->hasKey("ghi") != 1){  //should return 1 if it is in the list
      return false;
    }
    delete d;
    break;
  }
  case 7: {
    // test07 : Find a key at the beginning of a list
    Dict* d = new Dict();
    d->addOrUpdate("abc", 42);
    d->addOrUpdate("def", 30);
    d->addOrUpdate("ghi", 15);
    if(d->hasKey("abc") != 1){  //should return 1 if it is in the list
      return false;
    }
    delete d;
    break;
  }
  case 8: {
    // test08 : Lookup a null list
    Dict* d = new Dict();
    if(d->lookup("abc") != 0){  //should return 0, list is null
      return false;
    }
    delete d;
    break;
  }
  case 9: {
    // test09 : lookup key that isnt in list
    Dict* d = new Dict();
    d->addOrUpdate("abc", 42);
    if(d->lookup("def") != 0){  //should return 0, key not present
      return false;
    }
    delete d;
    break;
  }
  case 10: {
    // test10 : Remove key from null list
    Dict* d = new Dict();
    if(d->remKey("abc") != 0){  //should return 0, list is null
      return false;
    }
    delete d;
    break;
  }
  case 11: {
    // test11 : remove key not in list
    Dict* d = new Dict();
    d->addOrUpdate("abc", 42);
    if(d->remKey("def") != 0){  //should return 0, key is not present
      return false;
    }
    delete d;
    break;
  }
  case 12: {
    // test12 : Empty String
    Dict* d = new Dict();
    d->addOrUpdate("", 42);
    if(d->remKey("") != -1){  //should return -1, key is not present
      return false;
    }
    delete d;
    break;
  }
  case 13: {
    // test13 : Empty int
    Dict* d = new Dict();
    string s;
    d->addOrUpdate(s, 14);
    if(d->lookup(s) != 0){  //should return 0, key is not present
      return false;
    }
    delete d;
    break;
  }

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

  
