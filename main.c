#include <stdio.h>
#include <stdlib.h>

char *read_file(const char *filename);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  char *source_code = read_file(argv[1]);

  if (source_code != NULL) {
    printf("%s", source_code);
    free(source_code);
  }

  return 0;
}

