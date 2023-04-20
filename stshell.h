#ifndef STSHELL_H
#define STSHELL_H

#define MAX_LINE 80

void handle_signal(int);

void redirectFile(int, char *);

void execute(char *);

void init_shell();


#endif
