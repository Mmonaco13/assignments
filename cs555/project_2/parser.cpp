/* Matthew Monaco
 * I pledge my honor that I have abided by the Stevens Honor System.*/

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <array>
#include <unordered_map>
#include <list>
#include <iterator>

using namespace std;

struct individual{
    string name;
    char gender;
    string birthday;
    int age;
    bool alive;
    string death;
    list<string> child;
    list<string> spouse;
}
curIndi = {"", '\0', "N/A", 0, false, "N/A", {}, {}};

struct family{
    string married;
    string divorced;
    string husbandID;
    string wifeID;
    list<string> children;
}
curFam = {"", "N/A", "N/A", "N/A", {}};

string curID;
string curTag;
unordered_map<string, individual> indiMap;
unordered_map<string, family> famMap;

void store(string level, string tag, string args){
    if(strcmp(tag.c_str(), "NOTE") == 0 || strcmp(tag.c_str(), "HEAD") == 0){
        return;
    }
    
    if(strcmp(tag.c_str(), "INDI") == 0){
        if(strcmp(curIndi.name.c_str(), "")){
            indiMap[curID.c_str()] = curIndi;
        }
        individual temp = {"N/A", '\0', "N/A", 0, false, "N/A", {}, {}};
        curIndi = temp;
        curID = args;
    }else if(strcmp(tag.c_str(), "NAME") == 0){
        curIndi.name = args.c_str();
    }else if(strcmp(tag.c_str(), "SEX") == 0){
        curIndi.gender = *args.c_str();
    }else if(strcmp(tag.c_str(), "BIRT") == 0){
        curTag = tag.c_str();
    }else if(strcmp(tag.c_str(), "DEAT") == 0){
        curTag = tag.c_str();
    }else if(strcmp(tag.c_str(), "FAMC") == 0){
        curIndi.child.push_back(args);
    }else if(strcmp(tag.c_str(), "FAMS") == 0){
        curIndi.spouse.push_back(args);
    }else if(strcmp(tag.c_str(), "FAM") == 0){
        if(strcmp(curFam.married.c_str(), "")){
            famMap[curID.c_str()] = curFam;
        }
        family ftemp = {"N/A", "N/A", "N/A", "N/A", {}};
        curFam = ftemp;
        curID = args;
    }else if(strcmp(tag.c_str(), "MARR") == 0){
        curTag = tag.c_str();
    }else if(strcmp(tag.c_str(), "HUSB") == 0){
        curFam.husbandID = args.c_str(); 
    }else if(strcmp(tag.c_str(), "WIFE") == 0){
        curFam.wifeID = args.c_str();
    }else if(strcmp(tag.c_str(), "CHIL") == 0){
        curFam.children.push_back(args);
    }else if(strcmp(tag.c_str(), "DIV") == 0){
        curTag = tag.c_str();
    }else if(strcmp(tag.c_str(), "DATE") == 0){
        if(strcmp(curTag.c_str(), "BIRT") == 0){
            curIndi.birthday = args.c_str();
        }else if(strcmp(curTag.c_str(), "DEAT") == 0){
            curIndi.death = args.c_str();
        }else if(strcmp(curTag.c_str(), "DIV") == 0){
            curFam.divorced = args.c_str();
        }else if(strcmp(curTag.c_str(), "MARR") == 0){
            curFam.married = args.c_str();
        }
    }


}

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
        store(level, args, tag);
    }else if(strcmp(tag.c_str(), "INDI") == 0 || strcmp(tag.c_str(), "FAM") == 0){
        printf("<-- %s|%s|N|%s\n", level.c_str(), tag.c_str(), args.c_str());
        store(level, tag, args);
    }else{
        validate(level, tag, args);
        store(level, tag, args);
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
