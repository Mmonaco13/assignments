#ifndef msh_H
#define msh_H

int eval(char* command);
void sigint_handler(int sig);
void sigchld_handler(int sig);

#endif

