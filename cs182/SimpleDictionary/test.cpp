#include "SIdict.h"
#include <iostream>
int main(){
    Dict *dictionary = new Dict();
    cout << dictionary->Dict::addOrUpdate("Ozil",11) << endl;;      //0
    cout << dictionary->Dict::addOrUpdate("Cech",33) << endl;;      //0
    cout << dictionary->Dict::addOrUpdate("Lacazette",9) << endl;;  //0
    cout << dictionary->Dict::addOrUpdate("Cech",1) << endl;;       //1
    cout << dictionary->Dict::lookup("Lacazette") << endl;;         //9
    cout << dictionary->Dict::hasKey("Ozil") << endl;;              //1
    cout << dictionary->Dict::hasKey("Sanchez") << endl;;           //0
    cout << dictionary->Dict::addOrUpdate("Wilshere",10) << endl;;  //0
    cout << dictionary->Dict::remKey("Ozil") << endl;;              //11
    cout << dictionary->Dict::remKey("Cech") << endl;;              //1
    cout << dictionary->Dict::hasKey("Cech") << endl;;              //0
    cout << dictionary->Dict::hasKey("Ozil") << endl;;              //0

    return 0;
}