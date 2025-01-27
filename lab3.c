#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100

int main() {

  char *line = NULL;
  size_t lineSize = 250;

  char *arr[MAX_LINES];

  for (int i = 0; i < MAX_LINES; i++) {
    arr[i] = NULL;
  }

  int index = 0;
  while (1) {
    printf("Enter input: ");
    getline(&line, &lineSize, stdin);

    line[strcspn(line, "\n")] = '\0';

    if (strcmp(line, "print") == 0) {
      break;
    }

    arr[index] = strdup(line);
    index++;
  }

  free(line);

  printf("print");

  for (int i = index; i > 0; i--) {

    printf("%s\n", arr[i]);
  }
}
