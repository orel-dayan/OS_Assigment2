#include "string.h"
#include "codec.h"

void encode(char *input)
{
  while (*input != '\0')
  {
    *input = *input + 3;
    input++;
  }
}
void decode(char *input)
{
  while (*input != '\0')
  {
    *input = *input - 3;
    input++;
  }
}
