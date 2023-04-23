#ifndef STSHELL_H
#define STSHELL_H

#define MAX_LINE 80                    // The maximum length command
#define clear() printf("\033[H\033[J") // Clear the screen

/**
 * @brief handle_signal handles the SIGINT signal (Ctrl-C)
 * @param int signal
 * @return void
 */

void handle_signal(int);


/***
 * @brief execute_command executes a command passed as a parameter (input)
 *      It also handles the output redirection
 * @param char *input - The command to execute
 * @return void
 */

void execute_command(char *);

/**
 * @brief init_shell initializes the shell printing the welcome message (just for fun :) )
 * @return void
 *
 */

void init_shell();

#endif
