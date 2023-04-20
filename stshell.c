#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include "stshell.h"

#define MAX_LINE 80 // The maximum length command
#define clear() printf("\033[H\033[J")

int main()
{

  init_shell(); // initialize the shell

  signal(SIGINT, handle_signal); // for Ctrl-C
  while (1)
  {
    char input[MAX_LINE + 1]; // +1 for the null terminator
    printf("\033[36mstshell>\033[0m ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = 0; // remove the trailing newline
// maybe remove 
    if (strcmp(input, "clear") == 0)
    {
      write(STDOUT_FILENO, "\033[H\033[J", 7);

      continue;
    }

    if (strcmp(input, "exit") == 0)
    {
      exit(0);
    }

    /*  Check if the input contains a pipe  */
    int counterPipe = 0;
    for (int i = 0; i < strlen(input); i++)
    {
      if (input[i] == '|')
        counterPipe++;
    }

    if (counterPipe > 0)
    {
      /**
       * split the input by pipes and store each command in an array
       */
      char *commands[counterPipe + 1];
      char *token = strtok(input, "|");
      int i = 0; // index of the commands array
      while (token != NULL)
      {
        commands[i++] = token;
        token = strtok(NULL, "|");
      }
      commands[i] = NULL;
      /**
       * create array of pipes
       * there is 2 file descriptors per pipe 0: read end, 1: write end
       */
      int pipes[counterPipe][2];
      for (int i = 0; i < counterPipe; i++)
      {
        if (pipe(pipes[i]) == -1) // create a pipe
        {
          perror("pipe");
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
          perror("fork");
          exit(1);
        }
        else if (pid == 0)
        {
          // Child process

          // Set up signal handling for Ctrl+c
          signal(SIGINT, handle_signal);

          // Redirect input from the previous pipe, if this is not the first command
          if (i > 0)
          {
            if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1) // duplciate the read end of the previous pipe to the standard input
            {
              perror("dup2");
              exit(1);
            }
          }

          // Redirect output to the next pipe, if this is not the last command
          if (i < counterPipe)
          {
            if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
            {
              perror("dup2");
              exit(1);
            }
          }

          // Close all pipe ends except the ones being used by this command
          for (int j = 0; j < counterPipe; j++)
          {
            if (i > 0 && j == i - 1)
            {
              close(pipes[j][1]);
            }
            else if (i < counterPipe && j == i)
            {
              close(pipes[j][0]);
            }
            else
            {
              close(pipes[j][0]);
              close(pipes[j][1]);
            }
          }
          execute(commands[i]);
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
        perror("fork");
        exit(1);
      }
      else if (pid == 0)
      {

        // Execute the command
        execute(input);
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
  printf("\033[1m  _   _      _ _            \033[0m\n");
  printf("\033[1m | | | | ___| | | ___       \33[0m\n");
  printf("\033[1m | |_| |/ _ \\ | |/ _ \\   \033[0m\n");
  printf("\033[1m |  _  |  __/ | | (_) |     \033[0m\n");
  printf("\033[1m |_| |_|\\___|_|_|\\___/     \033[0m\n");
  printf("\033[1m                              \033[0m\n");

  sleep(1);

  clear();
}

void handle_signal(int sig)
{
  // Do nothing
  printf("\n");
}

void redirectFile(int output_redirect, char *output_file)
{
  // Redirect output to a file if necessary
  if (output_redirect == 1)
  {
    // Output redirection with ">"
    int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
      perror("open");
      exit(1);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
      perror("dup2");
      exit(1);
    }
    close(fd);
  }
  else if (output_redirect == 2)
  {
    // Output redirection with ">>"
    int fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
      perror("open");
      exit(1);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
      perror("dup2");
      exit(1);
    }
    close(fd);
  }
}

void execute(char *input)
{
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
  int output_redirect = 0;
  char *output_file = NULL;
  for (int j = 0; args[j] != NULL; j++)
  {
    if (strcmp(args[j], ">") == 0)
    {
      output_redirect = 1;
      output_file = args[j + 1];
      args[j] = NULL;
      break;
    }
    else if (strcmp(args[j], ">>") == 0)
    {
      output_redirect = 2;
      output_file = args[j + 1];
      args[j] = NULL;
      break;
    }
    else if (strcmp(args[j], "<") == 0)
    {
      int fd = open(args[j + 1], O_RDONLY);
      if (fd == -1)
      {
        perror("open");
        exit(1);
      }
      if (dup2(fd, STDIN_FILENO) == -1)
      {
        perror("dup2");
        exit(1);
      }
      close(fd);
      args[j] = NULL;
      break;
    }
  }
  redirectFile(output_redirect, output_file);

  // Execute the command
  if (execvp(args[0], args) == -1)
  {
    perror("execvp");
    exit(1);
  }
}
