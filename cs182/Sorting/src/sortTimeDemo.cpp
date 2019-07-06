/* Demonstration of getting timing measurements for sorting sizeable arrays. 
 * Uses test files from Project Gutenberg http://www.gutenberg.org/
 */

#include <string>
#include <cstdio>
#include <cstring>


/* assuming i,j in range, swaps the values, in place */
void mySwap(std::string arr[], int i, int j) {
    std::string temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}


/* Muddle with arr[l:r] in place, to kill time.
 * Precondition: 0 <= l <= r <= len(arr).
 * Known bugs: Doesn't crash but does nothing useful, slowly.  Is that a bug?
 */ 
void quacksort(std::string arr[], int l, int r) {
    for (int silly = l; silly < r; silly++) 
        for (int sillier = silly; sillier < r; sillier++)
            if (arr[silly] < arr[sillier])
                mySwap(arr, silly, sillier);
}


#define NUM_REPEAT 1 /* number of repetitions of a sorting test */


/* Repeatedly run quacksort on the given file, assuming it exists and contains 
 * at most numwords of words, with each word of length at most wordlen. 
 * (A word is just a sequence of characters, delimited by white space.)
 * Print the approximate execution time, including time for copying the array
 * but not the time for loading the file.
 */
void testsort(std::string filename, int numwords, int wordlen) {
  std::string* big = new std::string[numwords];
  std::string* copy = new std::string[numwords];
  char buf[wordlen+1]; // allow for null

    /* load the file into big array (with no error checking!) */

    FILE* file = fopen(filename.c_str(), "r");
    int actualwords = 0;
    while( fscanf(file, "%s", buf) != EOF ) {
        big[actualwords++] = std::string(buf);
    }
    fclose(file);

    printf("testing file  %s ...\n", filename.c_str());
    
    /* save start time, repeatedly make a (shallow) copy of the array and sort it */ 

    clock_t begin, end;
    double time_spent;
    begin = clock();

    for (int j = 0; j < NUM_REPEAT; j++) {
        for (int i = 0; i < actualwords; i++)
            copy[i] = big[i];
        quacksort(copy, 0, actualwords);
    }

    /* stop timing and print duration */

    end = clock();
    time_spent = ((double)(end - begin)) / CLOCKS_PER_SEC;
    printf("file is %s; time spent on %i sorts is %f; time per sort is %f \n", 
           filename.c_str(), NUM_REPEAT, time_spent, time_spent/NUM_REPEAT);
    delete [] big;
    delete [] copy;
}        


/* Run some tests.  ALERT: I've hard coded the data sizes. 
*/

/*int main(int argc, char *argv[]) {

    testsort("statesContig.txt", 267, 3);  
    testsort("3esl.txt", 23427, 21);  
    testsort("chromosome4.txt", 170617, 61); */
//    testsort("war+peace.txt", 564264, 32); /* May not work, may cause errors due to size. But try it.*/

//}






