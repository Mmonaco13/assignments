/*Matthew Monaco
  I pledge my honor that I have abided by the Stevens Honor System*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
  
int main(int argc, char **argv){
  /*Check correct number of arguments*/
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

  /*Create a line buffer for reading data*/
  char* lineBuf;
  size_t bufSize = 30;
  lineBuf = (char *)malloc(bufSize * sizeof(char));
  if(lineBuf == NULL){
    exit(1);
  }

  char *userId;
  char *itemId;
  char *rating;
  char *timestamp;
  
  short userVal;
  short itemVal;
  char rateVal;
  long long int timeVal;

  /*Cycle through each line of the file, separate the values,
    convert the values, then fwrite them into the output file.
    Stop when the end of the input file is reached.*/
  while(1){
    getline(&lineBuf, &bufSize, inFile);
    if(feof(inFile)){
      break;
    }
    
    if(strlen(lineBuf) > 6){
      
      userId = strtok(lineBuf,"\t");
      itemId = strtok(NULL, "\t");
      rating = strtok(NULL, "\t");
      timestamp = strtok(NULL, "\t");
      
      userVal = atoi(userId);
      itemVal = atoi(itemId);
      rateVal = rating[0];
      timeVal = atoll(timestamp);
      
      fwrite(&userVal,sizeof(short),1,outFile);
      fwrite(&itemVal,sizeof(short),1,outFile);
      fwrite(&rateVal,sizeof(char),1,outFile);
      fwrite(&timeVal,sizeof(long long int),1,outFile);
    }
  }
  
  free(lineBuf);
  fclose(inFile);
  fclose(outFile);
  return(0);
}
