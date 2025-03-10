#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFF_SIZE 128

struct header {
  uint64_t size;
  struct header *next;
};

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUFF_SIZE];
  ssize_t len = snprintf(buf, BUFF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data
                                                       : *(void **)data);
  if (len > 0) {
    write(STDOUT_FILENO, buf, len);
  }
}

void initblock(void *start, uint64_t size, struct header *next, int val) {
  struct header *blockhead = (struct header *)start;
  blockhead->size = size;
  blockhead->next = next;

  void *datastart = (void *)((char *)start + sizeof(struct header));
  memset(datastart, val, size - sizeof(struct header));
}

int main() {
  void *heaps = sbrk(256);
  if (heaps == (void *)-1) {
    return 1; // Error handling
  }

  void *firstblock = (char *)heaps;
  void *secondblock = (char *)heaps + 128;

  initblock(firstblock, 128, NULL, 0);
  initblock(secondblock, 128, (struct header *)firstblock, 1);

  struct header *firsthead = (struct header *)firstblock;
  struct header *secondhead = (struct header *)secondblock;

  // Print block addresses
  print_out("First block address: %p\n", firstblock, sizeof(firstblock));
  print_out("Second block address: %p\n", secondblock, sizeof(secondblock));

  // Print first block header
  print_out("First block size: %llu\n", &firsthead->size,
            sizeof(firsthead->size));
  print_out("First block next: %p\n", &firsthead->next,
            sizeof(firsthead->next));

  // Print second block header
  print_out("Second block size: %llu\n", &secondhead->size,
            sizeof(secondhead->size));
  print_out("Second block next: %p\n", &secondhead->next,
            sizeof(secondhead->next));

  // Print first block data
  uint8_t *firstdata = (uint8_t *)((char *)firstblock + sizeof(struct header));
  for (int i = 0; i < 128 - sizeof(struct header); i++) {
    print_out("%d\n", &firstdata[i], sizeof(firstdata[i]));
  }

  // Print second block data
  uint8_t *seconddata =
      (uint8_t *)((char *)secondblock + sizeof(struct header));
  for (int i = 0; i < 128 - sizeof(struct header); i++) {
    print_out("%d\n", &seconddata[i], sizeof(seconddata[i]));
  }

  return 0;
}
