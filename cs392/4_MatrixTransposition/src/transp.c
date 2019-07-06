/*Matthew Monaco
 *I pledge my honor that I have abided by the Stevens Honor System
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

/*Global Variables
 *N: Width of the square matrix
 *B: Width of the square block for transposition
 */
int N;
int B;

/*createMatrix
 *Generates an NxN matrix of random floats
 *Return: Matrix generated
 */
float* createMatrix(){
  float *mat = (float*) malloc(N * N * sizeof(float));
  if(mat == NULL){
    printf("Unable to allocate initial array\n");
    exit(-1);
  }
  for(int i = 0; i < (N*N); i++){
    mat[i] = ((((float)rand()) / RAND_MAX)*100);
  }
  return mat;
}

/*transpose
 *Param input: Array being transposed
 *Transpose the initial array into another matrix
 *Return: Transposed matrix
 */
float* transpose(float* input){
  float *output = (float*) malloc(N * N * sizeof(float));
  int i = 0;
  int j = 0;
  struct timeval start, end;
  gettimeofday(&start, NULL);
  while(i < N){
    while(j < N){
      for(int x = i; x < B + i; x++){
	for(int y = j; y < B + j; y++){
	  output[x*N + y] = input[y*N + x];
	}
      }
      j += B;
    }
    j = 0;
    i += B;
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
  for(int row = 0; row < N; row++){
    for(int col = 0; col < N; col++){
      if(input[row*N + col] != output[col*N + row]){
	printf("Verification Failed\n");
      }
    }
  }
  printf("Verification Succeeded\n");
  return;
}

/*Transpose a Square Matrix using a specified block size
 * to transpose the values. This program is used to study
 * locality
 */
int main(int argc, char **argv){
  srand(time(0));
  N = atoi(argv[1]);
  B = atoi(argv[2]);
  if(B > N){B = N;}
  float *input = createMatrix();
  float *output = transpose(input);
  verify(input, output);
  free(output);
  free(input);
  exit(0);
}
