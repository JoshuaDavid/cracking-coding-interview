#include <stdio.h>
#include <stdlib.h>

struct singly_linked_node {
    int value;
    struct singly_linked_node *next;
};

typedef struct singly_linked_node sl_node;
sl_node *make_node(int value);
sl_node *sl_list_from_array(int *values, int length);
void print_sl_node(sl_node *node);
void print_linked_list(sl_node *first);
void sl_free(sl_node *node);
sl_node *sl_concat(sl_node *first_a, sl_node *first_b);
int sl_list_length(sl_node *first);
int sl_lists_equal(sl_node *first_a, sl_node *first_b);
sl_node *sl_nth_node(sl_node *first, int n);
sl_node *sl_list_midpoint(sl_node *first);
int compare(int, int);
sl_node *sl_merge(sl_node *first_a, sl_node *first_b, int (*cmp)(int, int));
sl_node *sl_split_at_midpoint(sl_node *first);
sl_node *sl_merge_sort(sl_node *first, int (*cmp)(int, int));
int sl_list_has_cycle(sl_node *first);
sl_node *sl_list_cycle_start(sl_node *first);
