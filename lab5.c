#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next,
                      int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  // TODO: Implement first fit
  // first block that can fit it
  struct header *current = free_list_ptr;
  while (current != NULL) {
    if (current->size >= size) {
      return current->id;
    }
    current = current->next;
  }
  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  int best_fit_id = -1;
  // TODO: Implement best fit
  // find block that is just enough size
  uint64_t min_diff = 30000;
  struct header *current = free_list_ptr;
  while (current != NULL) {
    if (current->size >= size) {
      unint64_t current_diff = current->size - size;
      if (current_diff < min_diff) {
        min_diff = current_diff;
        best_fit_id = current->id;
      }
    }
    current = current->next;
  }
  return best_fit_id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  int worst_fit_id = -1;
  // TODO: Implement worst fit
  // find biggest block
  unint64_t max_diff = -1;
  struct header *current = free_list_ptr;
  while (current != NULL) {
    if (current->size >= size) {
      unint64_t current_diff = current->size - size;
      if (current_diff > max_diff) {
        max_diff = current_diff;
        worst_fit_id = current->id;
      }
    }
    current = current->next;
  }
  return worst_fit_id;
}

int main(void) {

  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  // TODO: Print out the IDs
  printf("First-fit %d", first_fit_id);
  printf("Best-Fit %d", best_fit_id);
  printf("Worst-Fit %d", worst_fit_id);

  return 0;
}
