#include <stdio.h>
#include <string.h> // strtok.

int main(int argc, char** argv) {
  printf("argc: %d\n", argc);

  const char delims[] = {'\r', '\n', '-', '|', ',', '.'};

  int i = 0;
  for (i = 0; i < argc; ++i) {
    printf("argv[%d]: %s\n", i, argv[i]);
    char* token = strtok(argv[i], delims);

    if (token != NULL) {
      printf("    token: %s\n", token);

      do {
        token = strtok(NULL, delims);

        if (token != NULL) {
          printf("    token: %s\n", token);
        }
      } while (token != NULL);
    }
  }
  return 0;
}

