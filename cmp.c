#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

bool verbose = false;
bool ignoreCase = false;

int compare_files(FILE *file1, FILE *file2);

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    printf("usage: ./cmp <file1> <file2> [-v] [-i]\n");
    return 1;
  }

  for (int i = 3; i < argc; i++)
  {
    if (strcmp(argv[i], "-v") == 0)
    {
      verbose = true;
    }
    else if (strcmp(argv[i], "-i") == 0)
    {
      ignoreCase = true;
    }
    else
    {
      printf("usage: ./cmp <file1> <file2> [-v] [-i]\n");
      return 1;
    }
  }

  FILE *file1 = fopen(argv[1], "r");
  FILE *file2 = fopen(argv[2], "r");

  if (!file1 || !file2)
  {
    printf("Error opening file(s)");
    return 1;
  }

  int isEqual = compare_files(file1, file2);

  if (verbose == true)
  {
    printf("%s\n", (isEqual == 0) ? "equal" : "distinct");
  }

  fclose(file1); // close the file
  fclose(file2); // close the file

  return isEqual == 0 ? 0 : 1;
}

int compare_files(FILE *file1, FILE *file2)
{
  unsigned char buffer1[BUFFER_SIZE];
  unsigned char buffer2[BUFFER_SIZE];
  size_t readFile1, readFile2;

  while ((readFile1 = fread(buffer1, 1, BUFFER_SIZE, file1)) > 0 && (readFile2 = fread(buffer2, 1, BUFFER_SIZE, file2)) > 0)
  {
    /**
     * @brief If ignoreCase is true, convert the characters in buffer1 and buffer2 to lowercase
     */

    if (ignoreCase == true)
    {
      for (size_t i = 0; i < readFile1; i++)
      {
        buffer1[i] = tolower(buffer1[i]);
        buffer2[i] = tolower(buffer2[i]);
      }
    }
    /**
     * @brief  Compare the contents of buffer1 and buffer2 and return 1 if they are not equal and 0 if they are equal
     */

    if (readFile1 != readFile2 || memcmp(buffer1, buffer2, readFile1) != 0)  return 1;
  }

  return (feof(file1) && feof(file2)) ? 0 : 1; // return 0 if both files have been read to the end, otherwise return 1
}
