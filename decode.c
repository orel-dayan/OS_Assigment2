#include "stdio.h"
#include <dlfcn.h>
#include <string.h>
#include "codec.h"

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    printf("Usage : ./decode <codec> <message>\n");
    return -1;
  }

  void *handle;
  void (*func_encode)(char *); // declare a function pointer

  if (strcmp(argv[1], "codecA") == 0) // load the library
  {
    handle = dlopen("./libcodecA.so", RTLD_LAZY);
  }
  else if (strcmp(argv[1], "codecB") == 0) // load the library
  {
    handle = dlopen("./libcodecB.so", RTLD_LAZY);
  }
  else
  {
    printf("Usage : ./decode <codec> <message>\n"); // print the usage
    return -1;
  }
  if (!handle) return -1; // check if the library is loaded successfully or not

  func_encode = dlsym(handle, "decode"); // get the address of the function
  func_encode(argv[2]);                  // call the function
  printf("%s\n", argv[2]);               // print the decoded message
  dlclose(handle);                       // close the library

  return 0;
}
