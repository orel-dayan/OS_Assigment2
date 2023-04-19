#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
  if (argc < 3 || argc > 5)
  {
    printf("usage:  cmp <file1> <file2> -v\n");
    return 1;
  }

  bool verbose = false;
  bool ignoreCase = false;
  if (argc == 4)
  {
    if (strcmp(argv[3], "-v") == 0)
    {
      verbose = true;
    }
    else if (strcmp(argv[3], "-i") == 0)
    {
      ignoreCase = true;
    }
    else
    {
      printf("usage:  cmp <file1> <file2> -v\n");
      return 1;
    }
  }
  if (argc == 5)
  {
    if (strcmp(argv[3], "-v") == 0 && strcmp(argv[4], "-i") == 0)
    {
      verbose = true;
      ignoreCase = true;
    }
    else if (strcmp(argv[3], "-i") == 0 && strcmp(argv[4], "-v") == 0)
    {
      verbose = true;
      ignoreCase = true;
    }
    else
    {
      printf("usage:  cmp <file1> <file2> -v\n");
      return 1;
    }
  }
  FILE *file1 = fopen(argv[1], "r"); // open file1
  if (file1 == NULL)
  {
    fclose(file1);
    printf("File %s does not exist\n", argv[1]);
    return 1;
  }
  FILE *file2 = fopen(argv[2], "r"); // open file2
  if (file2 == NULL)
  {
    fclose(file2);
    printf("File %s does not exist\n", argv[2]);
    return 1;
  }
  bool filesAreEqual = false;
  char c1, c2;
  while (true)
  {
    c1 = fgetc(file1);
    c2 = fgetc(file2);
    if (ignoreCase)
    {
      c1 = tolower(c1);
      c2 = tolower(c2);
    }
    if (c1 == EOF && c2 == EOF)
    {
      filesAreEqual = true;
      break;
    }
    if (c1 != c2)
    {
      break;
    }
  }
  if (verbose)
  {
    if (filesAreEqual)
    {
      printf("equal\n");
    }
    else
    {
      printf("distinct\n");
    }
  }

  return filesAreEqual ? 0 : 1;
}
