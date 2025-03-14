#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ASSERT(expr)                                                           \
  {                                                                            \
    if (!(expr)) {                                                             \
      fprintf(stderr, "Assertion failed: %s, file %s, line %d\n", #expr,       \
              __FILE__, __LINE__);                                             \
      exit(1);                                                                 \
    }                                                                          \
  }

#define TEST(expr)                                                             \
  {                                                                            \
    if (!(expr)) {                                                             \
      fprintf(stderr, "Test failed: %s\n", #expr);                             \
      exit(1);                                                                 \
    }                                                                          \
  }

typedef struct node {
  uint64_t data;
  struct node *next;
} node_t;

typedef struct info {
  uint64_t sum;
} info_t;

node_t *head = NULL;
info_t info = {0};

void insert_sorted(uint64_t data) {
  node_t *new_node = malloc(sizeof(node_t));
  new_node->data = data;
  new_node->next = NULL;

  if (head == NULL) {
    head = new_node;
  } else if (data < head->data) {
    new_node->next = head;
    head = new_node;
  } else {
    node_t *curr = head;
    node_t *prev = NULL;

    // Traverse until we find the insertion point.
    while (curr != NULL && data >= curr->data) {
      prev = curr;
      curr = curr->next;
    }
    // Insert new_node between prev and curr.
    prev->next = new_node;
    new_node->next = curr;
  }

  info.sum += data;
}

// Function to compute the sum of all elements in the list.
uint64_t compute_sum() {
  uint64_t sum = 0;
  node_t *curr = head;
  while (curr != NULL) {
    sum += curr->data;
    curr = curr->next;
  }
  return sum;
}

int index_of(uint64_t data) {
  node_t *curr = head;
  int index = 0;
  while (curr != NULL) {
    if (curr->data == data) {
      return index;
    }
    curr = curr->next;
    index++;
  }
  return -1;
}

int main() {
  insert_sorted(1);
  insert_sorted(3);
  insert_sorted(5);
  insert_sorted(2);

  TEST(info.sum == (1 + 3 + 5 + 2));
  // Verify the side property (info.sum) against the computed sum from the list.
  ASSERT(info.sum == compute_sum());

  TEST(index_of(2) == 1);

  return 0;
}
