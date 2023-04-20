#ifndef STSHELL_H
#define STSHELL_H


#define MAX_LINE 80 // The maximum length command
#define clear() printf("\033[H\033[J")


void handle_signal(int);

void redirectFile(int, char *);

void execute(char *);

void init_shell();


#endif
