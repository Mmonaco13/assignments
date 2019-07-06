/*Matthew Monaco
  I pledge my honor that I have abided by the Stevens Honor System*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
  
int main(int argc, char **argv){

  /*Check number of arguments*/
  if(argc != 3){
    fprintf(stderr, "Wrong number of command-line arguments\n");
    //usage(argv[0]);
    return -1;
  }

  /*Open files and make sure they exist*/
  FILE* inFile = fopen(argv[1],"r");
  if(inFile == NULL){
    printf("File Cannot be Opened \n");
    exit(0);
  }
  
  FILE* outFile = fopen(argv[2],"w");
  if(outFile == NULL){
    printf("File Cannot be Opened \n");
    exit(0);
  }

  short userId;
  short itemId;
  char rating;
  long long int timestamp;

  /*Read values out of the file until end of file is reached.
    After each set of data, print to the output file.*/
  while(!(feof(inFile))){
    fread(&userId, sizeof(short), 1, inFile);
    fread(&itemId, sizeof(short), 1, inFile);
    fread(&rating, sizeof(char), 1, inFile);
    fread(&timestamp, sizeof(long long int), 1, inFile);
    if(feof(inFile)){
      break;
    }
    fprintf(outFile,"%i\t%i\t%c\t%lld\n", userId, itemId, rating, timestamp);
  }

  
  fclose(inFile);
  fclose(outFile);
  return(0);
}
