#include <stdio.h>
#include <stdlib.h>
// Todo: figure out how to make that .hpp instead of .cpp
#include "singly_linked_node.cpp"
#include "linked_list.hpp"
#include <iostream>
#include <assert.h>
using namespace std;

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
            Node<T> *end = this->cycleStart();
            while(curr != end) {
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

        bool nodeBetween(Node<T> *target, Node<T> *start, Node<T> *end) {
            if(target == NULL) {
                return false;
            } else {
                Node<T> *curr = start;
                while(curr != end) {
                    if(target == curr) {
                        return true;
                    } else {
                        curr = curr->next;
                    }
                }
            }
        }

        bool nodeBetweenIndices(Node<T> *target, int start, int end) {
            if(target == NULL) {
                return false;
            } else {
                Node<T> *curr = this->nth(start);
                int i = 0;
                while(i <= end) {
                    if(curr == target) {
                        return true;
                    } else if(curr == NULL) {
                        return false;
                    } else {
                        curr = curr->next;
                    }
                    i++;
                }
                return false;
            }
        }

        bool hasCycle() {
            if(this->first == NULL) {
                return false;
            } else {
                for(int i = 1; i <= (1 << 30); i *= 2) {
                    Node<T> *target = this->nth(i);
                    if(target == NULL) {
                        // The list ended.
                        return false;
                    } else if(nodeBetweenIndices(target, 0, i - 1)) {
                        return true;
                    }
                }
            }
        }

        Node<T> *cycleStart() {
            // Get a node which is definitely in the loop.
            Node<T> *in_loop;
            for(int i = 1; i <= (1 << 30); i *= 2) {
                Node<T> *target = this->nth(i);
                if(target == NULL) {
                    // The list ended.
                    return NULL;
                } else if(nodeBetweenIndices(target->next, 0, i - 1)) {
                    // If the node occurs between the first element and itself,
                    //  there's a loop
                    in_loop = target;
                    break;
                }
            }

            // By binary search, find the first node which is in the loop.
            Node<T> *start = this->first;
            while(1) {
                if(start == in_loop) {
                    return start;
                }
                Node<T> *slow = start;
                Node<T> *fast = start;
                int i = 0;
                while(fast != in_loop) {
                    if(i && i % 2 == 0) slow = slow->next;
                    fast = fast->next;
                }
                if(nodeBetween(in_loop->next, slow, in_loop)) {
                    // Loop begins in first half.
                    in_loop = slow;
                } else {
                    // Loop begins in second half.
                    start = slow->next;
                }
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
