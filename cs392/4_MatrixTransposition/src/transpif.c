/*Matthew Monaco
 *I pledge my honor that I have abided by the Stevens Honor System
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

/*Global Variables
 *height: Height of the matrix
 *width: Width of the matrix
 *blockWidth: Width of the transposition block
 *blockHeight: Height of the transposition block
 *Block size (Constant)
 */
int height;
int width;
int blockWidth;
int blockHeight;
int B;

/*createMatrix
 *Generates a height x width matrix of random floats
 *Return: Matrix generated
 */
float* createMatrix(){
  float *mat = (float*) malloc(height * width * sizeof(float));
  if(mat == NULL){
    printf("Unable to allocate initial array\n");
    exit(-1);
  }
  for(int i = 0; i < (height * width); i++){
    mat[i] = ((((float)rand()) / RAND_MAX)*100);
    /*printf("%i: %f\n", i, mat[i]);*/
  }
  return mat;
}

/*transpose
 *Param input: Array being transposed
 *Transpose the initial array into another matrix
 *Return: Transposed matrix
 */
float* transpose(float* input){
  float *output = (float*) malloc(height * width * sizeof(float));
  int i = 0;
  int j = 0;
  struct timeval start, end;
  gettimeofday(&start, NULL);
  while(i < width){
    if(i + blockHeight > width){
      blockHeight = width - i;
    }
    while(j < height){
      if(j + blockWidth > height){
	blockWidth = height - j;
      }
      for(int x = i; x < blockHeight + i; x++){
	for(int y = j; y < blockWidth + j; y++){
	  output[x*height + y] = input[y*width + x];
	  /*printf("%i: %f\n",x*height + y , output[x*height + y]);*/
	}
      }
      j += blockWidth;
      blockWidth = B;
    }
    j = 0;
    i += blockHeight;
    blockHeight = B;
  }
  gettimeofday(&end, NULL);
  printf("%ld Microseconds\n", ((end.tv_sec * 1000000 + end.tv_usec)
	  - (start.tv_sec * 1000000 + start.tv_usec)));
  return output;
}

/*verify
 *Param input: Initial array
 *Param output: Transposed array
 *Check to see that output is the transposition of input
 */
void verify(float *input, float *output){
  for(int row = 0; row < height; row++){
    for(int col = 0; col < width; col++){
      if(input[row*width + col] != output[col*height + row]){
	printf("Verification Failed\n");
	exit(-1);
      }
    }
  }
  printf("Verification Succeeded\n");
  return;
}

/*Transpose a Matrix using a specified block size
 * to transpose the values. This program is used to study
 * locality
 */
int main(int argc, char **argv){
  srand(time(0));
  height = atoi(argv[1]);
  width = atoi(argv[2]);
  B = atoi(argv[3]);
  blockHeight = atoi(argv[3]);
  blockWidth = blockHeight;
  
  float *input = createMatrix();
  float *output = transpose(input);
  verify(input, output);
  free(output);
  free(input);
  exit(0);
}
