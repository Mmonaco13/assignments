/*Matthew Monaco
  I pledge my honor that I have abided by the Stevens Honor System*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
  
int main(int argc, char **argv){

  /*Check number of arguments*/
  if(argc != 4){
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
  FILE* itemFile = fopen(argv[2],"r");
  if(inFile == NULL){
    printf("File Cannot be Opened \n");
    exit(0);
  }
  
  FILE* outFile = fopen(argv[3],"w");
  if(outFile == NULL){
    printf("File Cannot be Opened \n");
    exit(0);
  }

  short userId;
  short itemId;
  char rating;
  long long int timestamp;

  /*Create an index array and a line buffer*/
  long long int *index = (long long int*)malloc(sizeof(long long int)*100);
  int maxSize = 100;
  char* lineBuf;
  size_t bufSize = 30;
  lineBuf = (char *)malloc(bufSize * sizeof(char));
  if(lineBuf == NULL){
    exit(1);
  }
  int counter = 1;
  index[0]=0;
  getline(&lineBuf, &bufSize, itemFile);

  /*Fill the index with the offsets for each movie*/
  while(lineBuf != NULL){
    if(ftell(itemFile) == index[counter-1]){
      lineBuf = NULL;
    }else{
      if(counter > maxSize){
	maxSize = maxSize + 100;
	index = (long long int*)realloc(index, sizeof(long long int)*maxSize);
      }
      index[counter] = ftell(itemFile);
      counter++;
      getline(&lineBuf, &bufSize, itemFile);
    }
  }

  /*Read the values, and reprint to the output file
    while swapping the item Id for the movie index*/
  while(!(feof(inFile))){
    fread(&userId, sizeof(short), 1, inFile);
    fread(&itemId, sizeof(short), 1, inFile);
    itemId--;
    fread(&rating, sizeof(char), 1, inFile);
    fread(&timestamp, sizeof(long long int), 1, inFile);
    if(feof(inFile)){
      break;
    }
    fprintf(outFile,"%i\t%lld\t%c\t%lld\n", userId, index[itemId], rating, timestamp);
  }
  
  free(lineBuf);
  free(index);
  fclose(inFile);
  fclose(outFile);
  fclose(itemFile);
}
