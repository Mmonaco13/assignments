#ifndef minprio_H
#define minprio_H

/*Creates the number of files asked for from
  the command line. A float value is put 
  into each file then the file is closed.*/
int fileCreate(char* argv);

/*Sorts the values in two files into one new
  file. One value from each file is taken at
  a time and they are individually compared.*/
int sort(int i, int newNum);

/*This function picks which files to merge
  together. The two files to be merged are
  sent to sort to be sorted and merged into
  one file*/
int merge(char* argv);

/*This function verifies that the values in
  the final file are sorted in increasing 
  order.*/
int verify(char* fileName);

#endif
