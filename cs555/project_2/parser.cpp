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
#include <iomanip>

using namespace std;

struct individual{
    string name;
    char gender;
    string birthday;
    bool alive;
    string death;
    list<string> child;
    list<string> spouse;
}
curIndi = {"", '\0', "N/A", true, "N/A", {}, {}};

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

int maxIDLength = 2;
int maxNameLength = 4;

/* Print all families in a table */
void printAllFamilies(){
    
    /*cout <<  setw(maxIDLength+1) << "ID" << " |" 
        << setw(maxNameLength+1) << "NAME" << " |"
        << setw(7) << "GENDER" << " |"
        << setw(12) << "BIRTHDAY" << " |" 
        << setw(6) << "ALIVE" << " |"
        << setw(12) << "DEATH" << " |"
        << endl;
    cout << endl;*/

    unordered_map<string, family>:: iterator itr; 
    for (itr = famMap.begin(); itr != famMap.end(); itr++){
        cout << setw(maxIDLength+1) << itr->first << " |" 
            << setw(12) << itr->second.married << " |" 
            << setw(12) << itr->second.divorced << " |"
            << endl;
    }

}

/* Print all individuals in a table */
void printAllIndividuals(){
    
    cout << setw(maxIDLength+1) << "ID" << " |" 
        << setw(maxNameLength+1) << "NAME" << " |"
        << setw(7) << "GENDER" << " |"
        << setw(12) << "BIRTHDAY" << " |" 
        << setw(6) << "ALIVE" << " |"
        << setw(12) << "DEATH" << " |"
        << endl;
    cout << endl;

    unordered_map<string, individual>:: iterator itr; 
    for (itr = indiMap.begin(); itr != indiMap.end(); itr++){
        string alive;
        if(itr->second.alive){
            alive = "True";
        }else{
            alive = "False";
        }
        cout <<  setw(maxIDLength+1) << itr->first << " |" 
            << setw(maxNameLength+1) << itr->second.name << " |"
            << setw(7) << itr->second.gender << " |"
            << setw(12) << itr->second.birthday << " |" 
            << setw(6) << alive << " |"
            << setw(12) << itr->second.death << " |"
            << endl;
    }
    return;
}

/* Store the last individual and family that were being edited */
void finalStore(){
    if(strcmp(curIndi.name.c_str(), "") != 0){
        indiMap[curID.c_str()] = curIndi;
    }
    if(strcmp(curFam.married.c_str(), "") != 0){
        famMap[curID.c_str()] = curFam;
    }
    return;
}

/* Store each line into unordered maps for individuals and families */
void store(string level, string tag, string args){
    if(strcmp(tag.c_str(), "NOTE") == 0 || strcmp(tag.c_str(), "HEAD") == 0){
        return;
    }
    
    if(strcmp(tag.c_str(), "INDI") == 0){
        if(strcmp(curIndi.name.c_str(), "") != 0){
            indiMap[curID.c_str()] = curIndi;
        }
        individual temp = {"N/A", '\0', "N/A", true, "N/A", {}, {}};
        curIndi = temp;
        curID = args;
        if(args.length() > maxIDLength){
            maxIDLength =  args.length();
        }
    }else if(strcmp(tag.c_str(), "NAME") == 0){
        curIndi.name = args.c_str();
        if(args.length() > maxNameLength){
            maxNameLength = args.length();
        }
    }else if(strcmp(tag.c_str(), "SEX") == 0){
        curIndi.gender = *args.c_str();
    }else if(strcmp(tag.c_str(), "BIRT") == 0){
        curTag = tag.c_str();
    }else if(strcmp(tag.c_str(), "DEAT") == 0){
        curTag = tag.c_str();
        curIndi.alive = false;
    }else if(strcmp(tag.c_str(), "FAMC") == 0){
        curIndi.child.push_back(args);
    }else if(strcmp(tag.c_str(), "FAMS") == 0){
        curIndi.spouse.push_back(args);
    }else if(strcmp(tag.c_str(), "FAM") == 0){
        if(strcmp(curFam.married.c_str(), "") != 0){
            famMap[curID.c_str()] = curFam;
        }
        family ftemp = {"N/A", "N/A", "N/A", "N/A", {}};
        curFam = ftemp;
        curID = args;
        if(args.length() > maxIDLength){
            maxIDLength =  args.length();
        }
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
    return;
}

/* Check if each line of the ged file is valid. NOT CURRENTLY BEING USED */
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

/* Parse each line of the ged file into the level, tag, and arguments */
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
        /*validate(level, args, tag);*/
        store(level, args, tag);
    }else if(strcmp(tag.c_str(), "INDI") == 0 || strcmp(tag.c_str(), "FAM") == 0){
        /*printf("<-- %s|%s|N|%s\n", level.c_str(), tag.c_str(), args.c_str());*/
        store(level, tag, args);
    }else{
        /*validate(level, tag, args);*/
        store(level, tag, args);
    }

    return;
}

int main(int argc, char** argv) {
    
    string nextLine;
    ifstream gedcomFile;
    gedcomFile.open(argv[1]);
    
    while(getline(gedcomFile, nextLine)){
        /* printf("--> %s\n", nextLine.c_str()); */
        parse(nextLine);
    }
    finalStore();
    
    unordered_map<string, individual>:: iterator itr; 
    /*for (itr = indiMap.begin(); itr != indiMap.end(); itr++){ 
        printf("%s\n", itr->second.name.c_str());
    }*/
    printAllIndividuals();
    printAllFamilies();
    return 0;
}
