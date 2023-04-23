#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <stdbool.h>
#include "stshell.h"

int main()
{
  int counterPipe = 0; // counter for the number of pipes

  init_shell(); // initialize the shell

  signal(SIGINT, handle_signal); // for Ctrl-C
  while (true)
  {
    char input[MAX_LINE + 1]; // command line (of 80) has max of 80 chars + \0
    printf("\033[36mstshell>\033[0m ");
    fgets(input, sizeof(input), stdin); // read a line from stdin (user input)

    input[strcspn(input, "\n")] = 0; // remove the trailing newline character from the input

    if (strcmp(input, "clear") == 0) // clear the screen
    {
      write(STDOUT_FILENO, "\033[H\033[J", 7);

      continue; // skip the rest of the loop
    }

    if (strcmp(input, "exit") == 0) // exit the shell
    {
      exit(0);
    }

    /*  Check if the input contains a pipe  */

    for (int i = 0; i < strlen(input); i++)
    {
      if (input[i] == '|')
        counterPipe++;
    }

    // check if counterPipe is greater than 0 then execute the pipe
    if (counterPipe > 0)
    {
      /**
       * split the input by pipes and store each command in an array
       */
      char *commands[counterPipe + 1]; // +1 for the NULL terminator
      char *token = strtok(input, "|");
      int i = 0; // index of the commands array
      while (token != NULL)
      {
        commands[i++] = token;
        token = strtok(NULL, "|");
      }
      commands[i] = NULL; // NULL terminator
      /**
       * create array of pipes
       * there is 2 file descriptors per pipe 0: read end, 1: write end
       */
      int pipes[counterPipe][2];
      for (int i = 0; i < counterPipe; i++)
      {
        if (pipe(pipes[i]) == -1) // create a pipe
        {
          printf("Error : creating pipe \n");
          exit(1);
        }
      }

      // Fork a child process for each command in the pipeline
      int pid;
      for (int i = 0; i < counterPipe + 1; i++)
      {
        pid = fork();

        if (pid == -1)
        {
          printf("Error : forking child process \n");
          exit(1);
        }
        else if (pid == 0)
        {
          // Child process
          signal(SIGINT, handle_signal); // for Ctrl-C

          // Redirect input from the previous pipe, if this is not the first command
          if (i > 0)
          {
            if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1) // duplciate the read end of the previous pipe to the standard input
            {
              printf("Error : dup2 \n");
              exit(1);
            }
          }

          // Redirect output to the next pipe, if this is not the last command
          if (i < counterPipe)
          {
            if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
            {
              printf("Error : dup2 \n");
              exit(1);
            }
          }

          // Close all pipe ends except the ones being used by this command
          for (int j = 0; j < counterPipe; j++)
          {
            if (i > 0 && j == i - 1)
            {
              close(pipes[j][1]); // close the write end
            }
            else if (i < counterPipe && j == i)
            {
              close(pipes[j][0]); // close the read end
            }
            else
            {
              close(pipes[j][0]); // close the read end
              close(pipes[j][1]); // close the write end
            }
          }
          execute_command(commands[i]);
        }
      }

      // Close all pipe ends in the parent process
      for (int i = 0; i < counterPipe; i++)
      {
        close(pipes[i][0]);
        close(pipes[i][1]);
      }

      // Wait for all child processes to exit
      int status;
      for (int i = 0; i < counterPipe + 1; i++)
      {
        wait(&status);
      }
    }
    else
    {
      // Execute the command normally
      int pid = fork();

      if (pid == -1)
      {
        printf("Error : forking child process \n");
        exit(1);
      }
      else if (pid == 0)
      {

        signal(SIGINT, handle_signal); // for Ctrl-C
        execute_command(input);
      }
      else
      {
        // Wait for the child process to exit
        int status;
        wait(&status);
      }
    }
  }
  return 0;
}

void init_shell()
{
  clear();
  printf("\033[1;31m   _   _      _ _              \033[0m\n");  // Red
  printf("\033[1;33m  | | | | ___| | | ___         \33[0m\n");   // Yellow
  printf("\033[1;32m  | |_| |/ _ \\ | |/ _ \\     \033[0m\n");   // Green
  printf("\033[1;36m  |  _  |  __/ | | (_) |       \033[0m\n");  // Cyan
  printf("\033[1;34m  |_| |_|\\___|_|_|\\___/       \033[0m\n"); // Blue

  printf("\033[0m\n"); // Reset color to default

  // sleep(1);

  // clear();
}

void handle_signal(int signal)
{
  // Do nothing
  printf("\n");
}

void redirect(int output, char *file)
{
  // Redirect output to a file if necessary
  if (output == 1)
  {
    // Output redirection with ">"
    int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
      printf("Error : open \n");
      exit(1);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
      printf("Error : dup2 \n");
      exit(1);
    }
    close(fd);
  }
  else if (output == 2)
  {
    // Output redirection with ">>"
    int fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
      printf("Error : open \n");
      exit(1);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
      printf("Error : dup2 \n");
      exit(1);
    }
    close(fd);
  }
}

void execute_command(char *input)
{
  /*
  The arguments to the command 256 is the maximum number of arguments that can be
   passed to a command cause of the limit of the array size in C (256).
  */
  char *args[256];
  char *arg = strtok(input, " ");
  int i = 0;
  while (arg != NULL)
  {
    args[i++] = arg;
    arg = strtok(NULL, " ");
  }
  args[i] = NULL;

  // Check if this command contains an output redirection symbol
  int output = 0;
  char *file_output = NULL; // The file to redirect output to
  for (int j = 0; args[j] != NULL; j++)
  {
    if (strcmp(args[j], ">") == 0) // Output redirection with ">"
    {
      output = 1;                // 1 means ">"
      file_output = args[j + 1]; // The file to redirect output to
      args[j] = NULL;            // Set the output redirection symbol to NULL so that it is not passed to execvp
      break;                     // Break out of the loop
    }
    else if (strcmp(args[j], ">>") == 0)
    {
      output = 2;                // 2 means ">>"
      file_output = args[j + 1]; // The file to redirect output to
      args[j] = NULL;            // Set the output redirection symbol to NULL so that it is not passed to execvp
      break;                     // Break out of the loop
    }
    else if (strcmp(args[j], "<") == 0)
    {
      int fd = open(args[j + 1], O_RDONLY); // Open the file to redirect input from
      if (fd == -1)                         // If the file does not exist
      {
        printf("Error : open \n");
        exit(1);
      }
      if (dup2(fd, STDIN_FILENO) == -1) // Redirect input from the file
      {
        printf("Error : dup2 \n");
        exit(1);
      }
      close(fd);
      args[j] = NULL;
      break;
    }
  }
  redirect(output, file_output);

  if (execvp(args[0], args) == -1) // execute the command
  {
    printf("Error : execvp \n");
    exit(1);
  }
}
