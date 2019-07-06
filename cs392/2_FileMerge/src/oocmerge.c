/*Matthew Monaco
  I pledge my honor that I have abided by the Stevens Honor System*/

#include "oocmerge.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

int fileCreate(char* argv){
  FILE* tem;
  float val;
  char buf[20];

  /*Put a random float between -100 and
    100 into each file*/
  for(int i = 1; i <=  atoi(argv); i++){
    sprintf(buf, "temp/f%i.txt", i);
    tem = fopen(buf,"w");
    chmod(buf, 200);
    if(tem == NULL){
      printf("File Cannot be Opened \n");
      exit(0);
    }
    val = ((((float)rand()) / RAND_MAX)*200)-100;
    fwrite(&val, sizeof(float), 1, tem);
    fclose(tem);
  }
  return 1;
}

int sort(int i, int newNum){
  FILE* uno;
  FILE* dos;
  FILE* ne;
  char buf[20];
  char buf2[20];

  /*File Declarations*/
  sprintf(buf,"temp/f%i.txt",i);
  chmod(buf,400);
  uno = fopen(buf,"r");
  if(uno == NULL){
    printf("File Cannot be Opened \n");
    exit(0);
  }
	  
  sprintf(buf2,"temp/f%i.txt",i+1);
  chmod(buf2,400);
  dos = fopen(buf2,"r");
  if(dos == NULL){
    printf("File Cannot be Opened \n");
    exit(0);
  }

  ne = fopen("temp/foo.txt","w");
  chmod("temp/foo.txt",200);
  if(ne == NULL){
    printf("File Cannot be Opened \n");
    exit(0);
  }

  /*Sort the values from the two files
    into a new file in increasing order*/
  float num1;
  float num2;
  size_t check1 = sizeof(float);
  size_t check2 = sizeof(float);
  fread(&num1, sizeof(float), 1, uno);
  fread(&num2, sizeof(float), 1, dos);
  while(1){
    
    if(num1 < num2){
      fwrite(&num1, sizeof(float), 1, ne);
      check1 = fread(&num1, sizeof(float), 1, uno);
      
      if(check1 != 1){
	fwrite(&num2, sizeof(float), 1, ne);
	check2 = fread(&num2, sizeof(float), 1, dos);

	while(check2 == 1){
	  fwrite(&num2, sizeof(float), 1, ne);
	  check2 = fread(&num2, sizeof(float), 1, dos);
	}
	fclose(uno);
	fclose(dos);
	remove(buf);
	remove(buf2);
	fclose(ne);
	return(0);
      }
    }else{
      fwrite(&num2, sizeof(float), 1, ne);
      check2 = fread(&num2, sizeof(float), 1, dos);
      
      if(check2 != 1){
	fwrite(&num1, sizeof(float), 1, ne);
	check1  = fread(&num1, sizeof(float), 1, uno);
	
	while(check1 == 1){
	  fwrite(&num1, sizeof(float), 1, ne);
	  check1 = fread(&num1, sizeof(float), 1, uno);
	}
	fclose(uno);
	fclose(dos);
	remove(buf);
	remove(buf2);
	fclose(ne);
	return(0);
      }
    }
  }
}

int merge(char* argv){
  int num = 1;
  int maxNum = atoi(argv);
  int newNum = 1;
  char buf[20];
  char newbuf[20];

  /*Merge the data files until only
    file remains. Send files to sort()
    to be merged into a single file*/
  while(maxNum > 1){
    for(int i = 1; i <= maxNum; i=i+2){
      if(i == maxNum){
	sprintf(buf,"temp/f%i.txt",i);
	sprintf(newbuf,"temp/f%i.txt",newNum);
	rename(buf, newbuf);
	
      }else{
	sort(i, newNum);
	sprintf(buf,"temp/f%i.txt",newNum);
	rename("temp/foo.txt", buf);
      }
      newNum++;
    }
    maxNum = newNum - 1;
    newNum = 1;
  } 
  return(0);
}

int verify(char* fileName){
  chmod(fileName, 400);
  FILE* out = fopen(fileName,"r");
  if(out==NULL){
    printf("File Cannot be Opened\n");
    exit(0);
  }

  float num1;
  float num2;
  int check;
  fread(&num1, sizeof(float), 1, out);
  check = fread(&num2, sizeof(float), 1, out);

  /*Check the output file to make sure
    the values are properly sorted*/
  while(check == 1){
    if(num1 <= num2){
      num1 = num2;
      check = fread(&num2, sizeof(float), 1, out);
    }else{
      return 0;
    }
  }
  printf("Sort Verified\n");
  return 1;
}

int main(int argc, char **argv){
  srand(time(0));
  mkdir("temp",S_IRWXU);

  /*Create the files with the random
    values*/
  if(fileCreate(argv[1])!=1){
    printf("%s\n", "Failed to Create Files");
    exit(0);
  }
  
  /*Merge the files together and sort*/
  merge(argv[1]);

  /*Rename the output file and check if
    it is properly sorted*/
  char buf[20];
  sprintf(buf,"%s",argv[2]);
  rename("temp/f1.txt", buf);
  remove("temp");
  if(verify(argv[2]) != 1){
    printf("Output File not Sorted\n");
    exit(0);
  }
  return(0);
}


