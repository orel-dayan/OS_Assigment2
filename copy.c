#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
  if (argc < 3 || argc > 5)
  {
    printf("usage:  copy <file1> <file2> -v\n");
    return 1;
  }

  bool verbose = false;
  bool force = false;
  bool error = false;
  int c;
  if (argc == 4)
  {
    if (strcmp(argv[3], "-v") == 0)
    {
      verbose = true;
    }
    else if (strcmp(argv[3], "-f") == 0)
    {
      force = true;
    }
    else
    {
      printf("usage:  copy <file1> <file2> -v\n");
      return 1;
    }
  }
  if (argc == 5)
  {
    if ((strcmp(argv[3], "-v") == 0 && strcmp(argv[4], "-f") == 0) || (strcmp(argv[3], "-f") == 0 && strcmp(argv[4], "-v") == 0))
    {
      verbose = true;
      force = true;
    }

    else
    {
      printf("usage:  copy <file1> <file2> -v\n");
      return 1;
    }
  }
  FILE *src = fopen(argv[1], "r");
  if (src == NULL)
  {
    if (verbose)
    {
      printf("general failure\n");
    }

    fclose(src);
  }

  FILE *dst = fopen(argv[2], "r");

  if (dst != NULL)
  {
    if (!force)
    {
      if (verbose)
      {
        printf("target file exist\n");
      }

      fclose(src);
      fclose(dst);

      return 1;
    }
  }

  dst = fopen(argv[2], "w");

  if (dst == NULL)
  {
    if (verbose)
    {
      printf("general failure\n");
    }

    fclose(src);
    return 1;
  }

  while ((c = getc(src)) != EOF)
  {
    if (c == 0)
    {
      error = true;
      break;
    }
    putc(c, dst);
  }

  fclose(src);
  fclose(dst);

  if (error && verbose)
  {
    printf("general failure\n");
  }
  if (!error && verbose)
  {
    printf("success\n");
  }

  return error;
}
