#ifndef STSHELL_H
#define STSHELL_H

#define MAX_LINE 80 // The maximum length command
#define clear() printf("\033[H\033[J") // Clear the screen

/**
 * @brief handle_signal handles the SIGINT signal (Ctrl-C)
 * @param int signal
 * @return void
 */

void handle_signal(int);

/**
 * @brief redirects the output of a command to a file
 * @param int output_redirect - The output redirection symbol
 * @param char *output_file - The file to redirect the output to
 * @return void
 *
 */

void redirectFile(int, char *);

/**
 * @brief execute executes a command with arguments and possibly an output redirection symbol
 * @param char *input - The command with arguments and possibly an output redirection symbol
 * @return void
 *
 */

void execute(char *);

/**
 * @brief init_shell initializes the shell printing the welcome message (just for fun :) )
 * @return void
 *
 */

void init_shell();

#endif
