#include "string.h"
#include "codec.h"

void encode(char *input)
{
  while (*input != '\0')
  {
    if ('a' <= *input && *input <= 'z')
    {
      *input = *input + 'A' - 'a';
    }
    else if ('A' <= *input && *input <= 'Z')
    {
      *input = *input + 'a' - 'A';
    }
    input++;
  }
}

void decode(char *input)
{
  encode(input);
}
