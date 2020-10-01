/*I pledge my honor that I have abided by the Stevens Honor System
  Matthew Monaco 10/28/2018*/
#include <unistd.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "msh.h"

#define MAXLINE 5000

void sigint_handler(int sig){
  int olderrno = errno;
  printf("\n");
  errno = olderrno;
}

void sigchld_handler(int sig){
  int olderrno = errno;
  int pid;
  while((pid = waitpid(-1, NULL, WNOHANG)) > 0){
    printf("pid: %ld done\n", (long)pid);
  }
  if(errno != ECHILD){
    /*printf("wait error\n");*/
  }
  errno = olderrno;
}

int eval(char* command){
  if(!strcmp(command,"\n")){
    return 0;
  }
  strtok(command, "\n");
  int MAXARGS = 50;
  char* argv[MAXARGS];
  int argCount = 0;
  char* curVal = (char*)malloc(MAXLINE * sizeof(char));
  pid_t pid;

  /*Tokenize the string*/
  argv[argCount] = strtok(command, " ");
  argCount++;
  while(1){
    argv[argCount] = strtok(NULL, " ");
    if(argv[argCount] == NULL){
      break;
    }
    argCount++;
  }

  /*Exit command*/
  if(strcmp(argv[0],"exit") == 0){
    return 4;

  /*Cd command*/
  }else if(strcmp(argv[0],"cd") == 0){
    if(chdir(argv[1]) != 0){
      printf("%s\n","Directeory Change Error");
    }

  /*Background command*/
  }else if(strcmp(argv[argCount-1],"&") == 0){
    int i = 0;
    argv[argCount-1] = NULL;
    if((pid = fork()) == 0){
      if(execvp(argv[0],argv) < 0){
	printf("Command not found\n");
	i = 1;
	exit(-1);
      }
      exit(0);
    }
    printf("pid: %ld cmd: ", (long)pid);
    for(int i = 0; i < argCount-1; i++){
      printf("%s ",argv[i]);
    }
    printf("\n");

  /*Foreground command*/ 
  }else{
    if((pid = fork()) == 0){
      if(execvp(argv[0],argv) < 0){
	printf("Command not found\n");
	exit(-1);
      }
      exit(0);
    }
    int status;
    if(waitpid(pid, &status, 0) < 0){
      printf("Wait pid error\n");
    }
  }
  free(curVal);
  return 1;
}
int main(){

  if(signal(SIGINT, sigint_handler) == SIG_ERR){
    printf("Signal error\n");
  }
  if(signal(SIGCHLD, sigchld_handler) == SIG_ERR){
    printf("Signal error\n");
  }
  
  char *command = (char*)malloc(MAXLINE * sizeof(char)) ;
  struct passwd* password = getpwuid(getuid());
  char* username = password->pw_name;
  char curDir[MAXLINE];

  /*Get next user command*/
  while(1){
    getcwd(curDir, sizeof(curDir));
    printf("SWS:%s:%s>\n", username, curDir);
    fgets(command, MAXLINE, stdin);
    if(eval(command) == 4){
      killpg(getpid(), SIGTERM);
      free(command);
      return 1;
    }
  }
  
  killpg(getpid(), SIGTERM);
  free(command);
  return 1;
}
