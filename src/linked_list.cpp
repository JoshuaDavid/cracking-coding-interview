#include <stdio.h>
#include <stdlib.h>
#include "linked_list.hpp"
#include <iostream>
#include <assert.h>
using namespace std;

template <class T>
class Node {
    public:
        T value;
        Node<T> *next;
        Node (T value) {
            this->value = value;
            this->next = (Node<T> *)NULL;
        }
        ~Node() {}
        Node<T> *clone() {
            Node<T> *copy = new Node<T>(this->value);
            return copy;
        }
};

template <class T>
ostream &operator<<(ostream &os, Node<T> node) {
    cout << "(Node " << node.value << ")";
}

template <class T>
class LinkedList {
    public:
        Node<T> *first;
        Node<T> *last;
        int length;

        LinkedList(T *array = NULL, int length = 0) {
            this->length = length;
            if(length != 0) {
                this->first = new Node<T>(array[0]);
                Node<T> *prev = this->first;
                Node<T> *curr = this->first;
                for(int i = 1; i < length; i++) {
                    curr = new Node<T>(array[i]);
                    prev->next = curr;
                    prev = prev->next;
                }
                this->last = curr;
            }
        }

        ~LinkedList() {
            Node<T> *curr = this->first;
            Node<T> *next;
            while(curr != NULL) {
                next = curr->next;
                delete curr;
                curr = next;
            }
        }

        bool equals(LinkedList *that) {
            Node<T> *curr_this = this->first;
            Node<T> *curr_that = that->first;
            bool equal = true;
            while(curr_this != NULL && curr_that != NULL) {
                if(curr_this->value != curr_that->value) {
                    cout << curr_this->value << ' ' << curr_that->value << endl;
                    equal = false;
                    break;
                }
                curr_this = curr_this->next;
                curr_that = curr_that->next;
            }
            if(curr_this != NULL || curr_that != NULL) {
                equal = false;
            }
            return equal;
        }

        LinkedList<T> *clone() {
            LinkedList<T> *copy = new LinkedList(NULL, 0);
            Node<T> *curr = this->first;
            while(curr != NULL) {
                Node<T> *clonednode = curr->clone();
                Node<T> *prev = clonednode;
                if(copy->first == NULL) {
                    copy->first = clonednode;
                    copy->last  = clonednode;
                } else {
                    copy->last->next = clonednode;
                    copy->last = copy->last->next;
                }
                curr = curr->next;
            }
            copy->length = this->length;
            return copy;
        }

        void concat(LinkedList *that) {
            if(this->last == NULL) {
                this->first = that->first;
            } else {
                this->last->next = that->first;
            }
            this->last    = that->last;
            this->length += that->length;
        }

        Node<T> *nth(int n) {
            Node<T> *curr = this->first;
            for(int i = 0; i < n; i++) {
                if(curr == NULL) break;
                curr = curr->next;
            }
            return curr;
        }

        Node<T> *midpoint() {
            Node<T> *fast = this->first;
            Node<T> *slow = this->first;
            int i = 0;
            while(fast != NULL) {
                if(i % 2 == 1) slow = slow->next;
                fast = fast->next;
                i++;
            }
            return slow;
        }

        void merge(LinkedList<T> *that) {
            if(this->first == NULL) {
                this->first  = that->first;
                this->last   = that->last;
                this->length = that->length;
            } else if(that->first == NULL) {
                // We're merging with an empty list -- do nothing.
            } else {
                this->length += that->length;
                Node<T> *prefirst = new Node<T>(0);
                Node<T> *prev = prefirst;
                Node<T> *curr_this = this->first;
                Node<T> *curr_that = that->first;
                while(curr_this != NULL && curr_that != NULL) {
                    if(curr_this->value <= curr_that->value) {
                        prev->next = curr_this;
                        curr_this = curr_this->next;
                    } else {
                        prev->next = curr_that;
                        curr_that = curr_that->next;
                    }
                    assert(prev->next != NULL);
                    prev = prev->next;
                }
                // We haven't exhausted this 
                if(curr_this != NULL) {
                    prev->next = curr_this;
                    this->last = this->last;
                } else if(curr_that != NULL) {
                    prev->next = curr_that;
                    this->last = that->last;
                } else {
                    // We should never hit this path.
                    throw "Left and right both null after merging.";
                }
                delete prefirst;
            }
        }

        void sort() {
            if(this->length <= 1) {
                return;
            } else {
                LinkedList<T> *left  = new LinkedList(NULL, 0);
                LinkedList<T> *right = new LinkedList(NULL, 0);
                left->first   = this->first;
                left->length  = this->length / 2;
                left->last    = this->nth(left->length - 1);
                right->first  = left->last->next;
                right->last   = this->last;
                right->length = this->length - left->length;
                left->last->next = NULL;

                // Sort each half, then merge.
                left->sort();
                right->sort();
                left->merge(right);

                // And then set self the same as the result.
                this->first  = left->first;
                this->last   = left->last ;
                this->length = left->length ;
            }
        }
};

template <class T>
ostream &operator<<(ostream &os, LinkedList<T> list) {
    cout << "(LinkedList";
    Node<T> *curr = list.first;
    while(curr != NULL) {
        cout << " " << *curr;
        curr = curr->next;
    }
    cout << ")";
}


// Returns the first node of a linked list with the same values as the array,
// or null if passed an empty array.
template <class T>
Node<T> *linked_list_from_array(T *values, int length) {
    if(length == 0) {
        return (Node<T> *)NULL;
    } else {
        Node<T> *first = new Node<T>(values[0]);
        Node<T> *prev = first;
        for(int i = 1; i < length; i++) {
            Node<T> *curr = new Node<T>(values[i]);
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

// given the first node of a linked list, print the linked list.
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

// Gives the length of a singly linked list
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

// Says whether the VALUES of the linked lists are equal
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

// Takes a pointer to the first element of a linked list.
// Returns null if grabbing past end of linked list.
// Otherwise returns the nth element of the linked list.
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

// Finds the midpoint of a linked list.
// Does this by having a fast pointer and a slow pointer.
// Fast pointer moves forward by 1 every iteration.
template <class T>
Node<T> *linked_list_midpoint(Node<T> *first) {
    Node<T> *fast = first;
    Node<T> *slow = first;
    int i = 0;
    while(fast != NULL) {
        if(i++ % 2 == 1) slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

// returns -1 if a < b, 1 if a > b, and 0 if a == b
template <class T>
int compare(T left, T right) {
    if(left < right)      return -1;
    else if(left > right) return  1;
    else                  return  0;
}

// Merges two linked lists based on a comparison function.
// If the comparison function says -1 or 0, take a node from a.
// Otherwise, take a node from b.
template <class T>
Node<T> *linked_list_merge(Node<T> *left, Node<T> *right) {
    Node<T> before (0);
    Node<T> *prev = &before;
    Node<T> *before_first = prev;
    before_first->next = (Node<T> *)NULL;
    while(left != NULL && right != NULL) {
        if(compare<T>(left->value, right->value) <= 0) {
            prev->next = left;
            left = left->next;
        } else {
            prev->next = right;
            right = right->next;
        }
        prev = prev->next;
    }
    if(left != NULL)       prev->next = left;
    else if(right != NULL) prev->next = right;
    return before_first->next;
}

// Finds the midpoint of a linked list and splits the list at that point.
// Returns the first element of the second list.
// If passed an empty list, does nothing and returns null.
// If passed a list of one element, does nothing and returns the first node.
template <class T>
Node<T> *linked_list_split_at_midpoint(Node<T> *first) {
    Node<T> *prev = NULL;
    Node<T> *slow = first;
    Node<T> *fast = first;
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
template <class T>
Node<T> *linked_list_merge_sort(Node<T> *first) {
    if(first == NULL) {
        // length is 0
        return NULL;
    } else if(first->next == NULL) {
        // length is 1
        return first;
    } else {
        Node<T> *left = first;
        Node<T> *right = linked_list_split_at_midpoint(first);
        left = linked_list_merge_sort(left);
        right = linked_list_merge_sort(right);
        Node<T> *merged = linked_list_merge(left, right);
        return merged;
    }
}

template <class T>
int linked_list_has_cycle(Node<T> *first) {
    // An empty list has no cycles.
    if(first == NULL) return 0;
    Node<T> *curr = first;
    Node<T> *last = NULL;
    int search_size = 1;
    while(1) {
        Node<T> *curr = first;
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
template <class T>
Node<T> *linked_list_cycle_start_before(Node<T> *first, Node<T> *last) {
    if(first == last) {
        return first;
    }
    Node<T> *slow = first;
    Node<T> *fast = first;
    int i = 0;
    while(fast != last) {
        fast = fast->next;
        if(i % 2 == 0) slow = slow->next;
        i++;
    }
    Node<T> *curr = last->next;
    int loop_contains_slow = 0;
    while(curr != last) {
        if(curr == first) return first;
        if(curr == slow) loop_contains_slow = 1;
        curr = curr->next;
    }
    if(loop_contains_slow) {
        return linked_list_cycle_start_before(first, slow);
    } else {
        return linked_list_cycle_start_before(slow, last);
    }
    return NULL;
}

// If this list has a cycle, gives the first node of that cycle
template <class T>
Node<T> *linked_list_cycle_start(Node<T> *first) {
    if(!linked_list_has_cycle(first)) {
        return NULL;
    } else {
        int search_size = 1;
        Node<T> *last = NULL;
        while(1) {
            Node<T> *curr = first;
            int i = 0;
            for(i = 0; i < search_size; i++) {
                if(curr == last && i != search_size / 2) {
                    return linked_list_cycle_start_before(first, last);
                }
                curr = curr->next;
            }
            last = curr;
            search_size *= 2;
        }
    }
}
