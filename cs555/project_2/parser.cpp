/* Matthew Monaco
 * I pledge my honor that I have abided by the Stevens Honor System.*/

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <array>
using namespace std;

void validate(string level, string tag, string args){
    
    array<string, 5> l0Tags = {"INDI", "FAM", "HEAD", "TRLR", "NOTE"};
    array<string, 11> l1Tags = {"NAME", "SEX", "BIRT", "DEAT", "FAMC", "FAMS", "MARR", "HUSB", "WIFE", "CHIL", "DIV"};
    array<string, 1> l2Tags = {"DATE"};
       
    bool exists = false;
    if(strcmp(level.c_str(), "0") == 0){
        for(const auto& t : l0Tags){
            if(strcmp(t.c_str(), tag.c_str()) == 0){
                exists = true;
            }
        }
    }else if (strcmp(level.c_str(), "1") == 0){
        for(const auto& t : l1Tags){
            if(strcmp(t.c_str(), tag.c_str()) == 0){
                exists = true;
            }
        }
    }else{
        for(const auto& t : l2Tags){
            if(strcmp(t.c_str(), tag.c_str()) == 0){
                exists = true;
            }
        }
    }
    
    if(exists){
        printf("<-- %s|%s|Y", level.c_str(), tag.c_str());
    }else{
        printf("<-- %s|%s|N", level.c_str(), tag.c_str());
    }

    if(!args.empty()){
        printf("|%s\n", args.c_str());
    }else{
        printf("\n");
    }
}

void parse(string nextLine){
    
    char* line = new char [nextLine.length() + 1];
    strcpy(line, nextLine.c_str());
    
    string args;
    string tag;
    string level = nextLine.substr(0, nextLine.find_first_of(" "));
    nextLine = nextLine.substr(nextLine.find_first_of(" ") + 1);
    if(nextLine.find_first_of(" ") == -1){
        tag = nextLine;
        args = "";
    }else{
        tag = nextLine.substr(0, nextLine.find_first_of(" "));
        args = nextLine.substr(nextLine.find_first_of(" ") + 1);
    }
    

    if(strcmp(args.c_str(), "INDI") == 0 || strcmp(args.c_str(), "FAM") == 0){
        validate(level, args, tag);
    }else if(strcmp(tag.c_str(), "INDI") == 0 || strcmp(tag.c_str(), "FAM") == 0){
        printf("<-- %s|%s|N|%s\n", level.c_str(), tag.c_str(), args.c_str());
    }else{
        validate(level, tag, args);
    }

    return;
}

int main(int argc, char** argv) {
    
    string nextLine;
    ifstream gedcomFile;
    gedcomFile.open(argv[1]);
    
    while(getline(gedcomFile, nextLine)){
        printf("--> %s\n", nextLine.c_str());
        parse(nextLine);
    }
    return 0;
}
