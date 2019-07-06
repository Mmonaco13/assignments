#include "SVDict.h"
#include <stdio.h>
#include <stdlib.h>

#define TOTAL_TESTS 6

bool run_test(int test_number) {
  switch(test_number) {
  case 1: {
    // test01 : A not-quite ordered insertion
    int* val=NULL;
    SVDict* steve;
    steve=new SVDict();
    std::string strings[10]={"a", "b", "A", "d", "q", "f", "g", "h", "i", "j"};
    for(int ii=0; ii<10; ii++){
      printf("%i",steve->addOrUpdate(strings[ii], NULL));
    }
    for(int jj=0; jj<10; jj++){
      if(!steve->hasKey(strings[jj])){
	delete steve;
	return false;
      }
    }
    delete steve;
    break;
  }

  case 2: {
    // test02: Test update
    char* a=(char*)"one";
    char* b=(char*)"two";
    SVDict* steve;
    steve=new SVDict();
    std::string strings[10]={"a", "b", "A", "d", "q", "f", "g", "h", "i", "j"};
    for(int ii=0; ii<10; ii++){
      steve->addOrUpdate(strings[ii], a);
    }
    steve->addOrUpdate("q", b);
    if(steve->lookup("q")!=b){
      delete steve;
      return false;
    }
    delete steve;
    break;
  }

  case 3: {
    // test03 : Add elements in reverse order
    int* val=NULL;
    SVDict* steve;
    steve=new SVDict();
    std::string strings[10]={"j", "i", "h", "g", "f", "e", "d", "c", "b", "a"};
    for(int ii=0; ii<10; ii++){
      steve->addOrUpdate(strings[ii], NULL);
    }
    for(int jj=0; jj<10; jj++){
      if(!steve->hasKey(strings[jj])){
	delete steve;
	return false;
      }
    }
    delete steve;
    break;
  }

    
  case 4: {
    // test04 : Check for keys that do not exist
    int* val=NULL;
    SVDict* steve;
    steve=new SVDict();
    std::string strings[10]={"a", "b", "A", "d", "q", "f", "g", "h", "i", "j"};
    for(int ii=0; ii<10; ii++){
      steve->addOrUpdate(strings[ii], NULL);
    }
    if(steve->hasKey("B")){
      delete steve;
      return false;
    }
    if(steve->hasKey("ab")){
      delete steve;
      return false;
    }
    delete steve;
    break; // if your test suceeds, break
  }
  case 5: {
    // test05 : Insertion order that should require no rotations
    int* val=NULL;
    SVDict* steve;
    steve=new SVDict();
    std::string strings[7]={"d", "b", "e", "a", "c", "f", "g"};
    for(int ii=0; ii<7; ii++){
      steve->addOrUpdate(strings[ii], NULL);
    }
    for(int jj=0; jj<7; jj++){
      if(!steve->hasKey(strings[jj])){
	delete steve;
	return false;
      }
    }
    delete steve;
    break;
  }

  case 6: {
    //test06 : Check presence on an empty tree
    int* val;
    val=NULL;
    SVDict* steve;
    steve=new SVDict();
    if(steve->hasKey("bob")){
      //Mostly just testing if it segfaults, a false positive seems really unlikely
      delete steve;
      return false;
    }
    delete steve;
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

  


