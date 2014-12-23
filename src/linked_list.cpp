#include <stdio.h>
#include <stdlib.h>
#include "linked_list.hpp"
#include <iostream>
using namespace std;

template <class T>
Node<T> *mknode(T value) {
    Node<T> *n = (Node<T> *)calloc(1, sizeof(Node<T>)); 
    n->value = value;
}

template <class T>
Node<T> *linked_list_from_array(T *values, int length) {
    if(length == 0) {
        return (Node<T> *)NULL;
    } else {
        Node<T> *first = mknode(values[0]);
        Node<T> *prev = first;
        for(int i = 1; i < length; i++) {
            Node<T> *curr = mknode(values[i]);
            prev->next = curr;
            prev = prev->next;
        }
        return first;
    }
}

template <class T>
Node<T> *linked_list_concat(Node<T> *left, Node<T> *right) {
    if(left == NULL) {
        return right;
    } else if(right == NULL) {
        return left;
    } else {
        Node<T> *curr = left;
        while(curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = right;
        return left;
    }
}

template <class T>
void print_linked_list(Node<T> *first) {
    if(first == NULL) {
        cout << "[]" << endl;
    } else {
        Node<T> *curr = first;
        cout << "[";
        while(curr != NULL) {
            cout << curr->value;
            if(curr->next != NULL) {
                cout << ", ";
            }
            curr = curr->next;
        }
        cout << "]" << endl;
    }
}

template <class T>
int linked_list_length(Node<T> *first) {
    Node<T> *curr = first;
    int len = 0;
    while(curr != NULL) {
        curr = curr->next;
        len++;
    }
    return len;
}

template <class T>
int linked_lists_equal(Node<T> *left, Node<T> *right) {
    int equal = 1;
    while(left != NULL && right != NULL) {
        if(left->value != right->value) {
            equal = 0;
            break;
        }
        left = left->next;
        right = right->next;
    }
    if(left != NULL || right != NULL) {
        equal = 0;
    }
    return equal;
}

template <class T>
Node<T> *linked_list_nth_node(Node<T> *first, int n) {
    Node<T> *curr = first;
    for(int i = 0; i < n; i++) {
        if(curr == NULL) {
            break;
        }
        curr = curr->next;
    }
    return curr;
}

template <class T>
Node<T> *linked_list_midpoint(Node<T> *first) {
    return NULL;
}

template <class T>
int compare_(T left, T right) {
    if(left < right)      return -1;
    else if(left > right) return  1;
    else                  return  0;
}

template <class T>
Node<T> *linked_list_merge(Node<T> *left, Node<T> *right) {
    return NULL;
}

template <class T>
Node<T> *linked_list_split_at_midpoint(Node<T> *first) {
    return NULL;
}

template <class T>
Node<T> *linked_list_merge_sort(Node<T> *first) {
    return NULL;
}

template <class T>
int linked_list_has_cycle(Node<T> *first) {
    return 0;
}

template <class T>
Node<T> *linked_list_cycle_start_before(Node<T> *first, Node<T> *last) {
    return NULL;
}

template <class T>
Node<T> *linked_list_cycle_start(Node<T> *first) {
    return NULL;
}

sl_node *make_node(int value) {
    sl_node *node = (sl_node *)calloc(1, sizeof(sl_node));
    node->value = value;
    return node;
}

/*
// Returns the first node of a linked list with the same values as the array,
// or null if passed an empty array.
sl_node *sl_list_from_array(int *values, int length) {
    if(length == 0) {
        return NULL;
    } else {
        sl_node *first = make_node(values[0]);
        sl_node *prev = first;
        int i = 1;
        for(i = 1; i < length; i++) {
            sl_node *curr = make_node(values[i]);
            prev->next = curr;
            prev = curr;
        }
        return first;
    }
}

void print_sl_node(sl_node *node) {
    printf("%i ", node->value);
}

void sl_free(sl_node *node) {
    sl_node *curr = node;
    while(curr != NULL) {
        sl_node *next = curr->next;
        free(curr);
        next = curr;
    }
}

sl_node *sl_concat(sl_node *first_a, sl_node *first_b) {
    if(first_a == NULL) {
        return first_b;
    } else if(first_b == NULL) {
        // Not strictly necessary for correctness, but skips passing through
        // all of list a if list b is empty.
        return first_a;
    } else {
        sl_node *curr = first_a;
        // Scan to last node
        while(curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = first_b;
        return first_a;
    }
}

// given the first node of a linked list, print the linked list.
void print_linked_list_(sl_node *first) {
    sl_node *curr = first;
    while(curr != NULL) {
        print_sl_node(curr);
        curr = curr->next;
    }
    puts("");
}

// Gives the length of a singly linked list
int sl_list_length(sl_node *first) {
    sl_node *node = first;
    int length = 0;
    while(node != NULL) {
        length += 1;
        node = node->next;
    }
    return length;
}

// Says whether the VALUES of the linked lists are equal
int sl_lists_equal(sl_node *first_a, sl_node *first_b) {
    sl_node *node_a = first_a;
    sl_node *node_b = first_b;
    int equal = 1;
    while(node_a != NULL && node_b != NULL) {
        if(node_a->value != node_b->value) {
            equal = 0;
            break;
        } else {
            node_a = node_a->next;
            node_b = node_b->next;
        }
    }
    if(node_a != NULL || node_b != NULL) {
        // The lists are of different lengths
        equal = 0;
    }
    return equal;
}

// Takes a pointer to the first element of a linked list.
// Returns null if grabbing past end of linked list.
// Otherwise returns the nth element of the linked list.
sl_node *sl_nth_node(sl_node *first, int n) {
    sl_node *curr = first;
    int i = 0;
    for(i = 0; i < n; i++) {
        if(curr == NULL) {
            return NULL;
        } else {
            curr = curr->next;
        }
    }
    return curr;
}

// Finds the midpoint of a linked list.
// Does this by having a fast pointer and a slow pointer.
// Fast pointer moves forward by 1 every iteration.
sl_node *sl_list_midpoint(sl_node *first) {
    sl_node *slow = first;
    sl_node *fast = first;
    int count = 0;
    while(fast != NULL) {
        fast = fast->next;
        if(fast == NULL) {
            return slow;
        } else {
            fast = fast->next;
            slow = slow->next;
        }
    }
    return slow;
}


// returns -1 if a < b, 1 if a > b, and 0 if a == b
int compare(int a, int b) {
    if(a < b) {
        return -1;
    } else if(a > b) {
        return  1;
    } else {
        return 0;
    }
}

// Returns the opposite of compare
int compare_desc(int a, int b) {
    return -compare(a, b);
}

// Merges two linked lists based on a comparison function.
// If the comparison function says -1 or 0, take a node from a.
// Otherwise, take a node from b.
sl_node *sl_merge(sl_node *first_a, sl_node *first_b, int (*cmp)(int, int)) {
    sl_node *before = make_node(0);
    sl_node *prev = before;
    sl_node *curr_a = first_a;
    sl_node *curr_b = first_b;
    while(curr_a != NULL && curr_b != NULL) {
        if(cmp(curr_a->value, curr_b->value) <= 0) {
            prev->next = curr_a;
            curr_a = curr_a->next;
        } else {
            prev->next = curr_b;
            curr_b = curr_b->next;
        }
        prev = prev->next;
    }
    if(curr_a != NULL) {
        prev->next = curr_a;
    } else if(curr_b != NULL) {
        prev->next = curr_b;
    }
    sl_node *first = before->next;
    free(before);
    return first;
}

// Finds the midpoint of a linked list and splits the list at that point.
// Returns the first element of the second list.
// If passed an empty list, does nothing and returns null.
// If passed a list of one element, does nothing and returns the first node.
sl_node *sl_split_at_midpoint(sl_node *first) {
    sl_node *prev = NULL;
    sl_node *slow = first;
    sl_node *fast = first;
    int count = 0;
    while(fast != NULL) {
        fast = fast->next;
        if(fast == NULL) {
            break;
        } else {
            fast = fast->next;
            prev = slow;
            slow = slow->next;
        }
    }
    if(prev != NULL) {
        //assert(prev->next == slow);
        prev->next = NULL;
    }
    return slow;
}

// Performs a merge sort on a linked list, recursively.
// Splits the list at the midpoint, then merges the two sides by the provided
// comparison function.
sl_node *sl_merge_sort(sl_node *first, int (*cmp)(int, int)) {
    if(first == NULL) {
        // length is 0
        return NULL;
    } else if(first->next == NULL) {
        // length is 1
        return first;
    } else {
        sl_node *left = first;
        sl_node *right = sl_split_at_midpoint(first);
        left = sl_merge_sort(left, cmp);
        right = sl_merge_sort(right, cmp);
        sl_node *merged = sl_merge(left, right, cmp);
        return merged;
    }
}

int sl_list_has_cycle(sl_node *first) {
    // An empty list has no cycles.
    if(first == NULL) return 0;
    sl_node *curr = first;
    sl_node *last = NULL;
    int search_size = 1;
    while(1) {
        sl_node *curr = first;
        int i = 0;
        for(i = 0; i < search_size; i++) {
            if(curr == NULL) {
                return 0;
            } else {
                if(curr == last && i != search_size / 2) {
                    return 1;
                }
                curr = curr->next;
            }
        }
        last = curr;
        search_size *= 2;
    }
}

// Given that last is in the cycle, find the first node in the
// cycle by scanning forward from last and seeing if first is
// included. If so, first is the first node, else recursively try
// again.
sl_node *sl_cycle_start_before(sl_node *first, sl_node *last) {
    if(first == last) {
        return first;
    }
    sl_node *slow = first;
    sl_node *fast = first;
    int i = 0;
    while(fast != last) {
        fast = fast->next;
        if(i % 2 == 0) slow = slow->next;
        i++;
    }
    sl_node *curr = last->next;
    int loop_contains_slow = 0;
    while(curr != last) {
        if(curr == first) return first;
        if(curr == slow) loop_contains_slow = 1;
        curr = curr->next;
    }
    if(loop_contains_slow) {
        return sl_cycle_start_before(first, slow);
    } else {
        return sl_cycle_start_before(slow, last);
    }
    return NULL;
}

// If this list has a cycle, gives the first node of that cycle
sl_node *sl_list_cycle_start(sl_node *first) {
    if(!sl_list_has_cycle(first)) {
        return NULL;
    } else {
        int search_size = 1;
        sl_node *last = NULL;
        while(1) {
            sl_node *curr = first;
            int i = 0;
            for(i = 0; i < search_size; i++) {
                if(curr == last && i != search_size / 2) {
                    return sl_cycle_start_before(first, last);
                }
                curr = curr->next;
            }
            last = curr;
            search_size *= 2;
        }
    }
}
*/
