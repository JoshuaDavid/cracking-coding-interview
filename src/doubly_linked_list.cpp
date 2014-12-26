#include <stdio.h>
#include <stdlib.h>
// Todo: figure out how to make that .hpp instead of .cpp
#include "doubly_linked_node.cpp"
#include "doubly_linked_list.hpp"
#include <iostream>
#include <assert.h>
using namespace std;

template <class T>
LinkedList<T>::LinkedList(T *array, int length) {
    this->length = length;
    if(length == 0) {
        this->first  = NULL;
        this->last   = NULL;
        this->length = 0;
    } else {
        this->first = new Node<T>(array[0]);
        Node<T> *prev = this->first;
        Node<T> *curr = this->first;
        for(int i = 1; i < length; i++) {
            curr = new Node<T>(array[i]);
            prev->next = curr;
            curr->prev = prev;
            prev = prev->next;
        }
        this->last = curr;
    }
}

template <class T>
LinkedList<T>::~LinkedList() {
    Node<T> *curr = this->first;
    Node<T> *next;
    Node<T> *end = this->cycleStart();
    while(curr != end) {
        next = curr->next;
        delete curr;
        curr = next;
    }
}

template <class T>
bool LinkedList<T>::equals(LinkedList *that, int verbose = 0) {
    Node<T> *curr_this = this->first;
    Node<T> *curr_that = that->first;
    bool equal = true;
    while(curr_this != NULL && curr_that != NULL) {
        if(curr_this->value != curr_that->value) {
            if(verbose) cout << *curr_this << " != " << *curr_that << endl;
            equal = false;
            break;
        }
        curr_this = curr_this->next;
        curr_that = curr_that->next;
    }
    if(curr_this != NULL) {
        if(verbose) cout << "curr_this should be NULL, is " << *curr_this << endl;
        equal = false;
    } else if(curr_that != NULL) {
        if(verbose) cout << "curr_that should be NULL, is " << *curr_that << endl;
        equal = false;
    }
    return equal;
}

template <class T>
LinkedList<T> *LinkedList<T>::clone() {
    LinkedList<T> *copy = new LinkedList(NULL, 0);
    if(this->length == 0) {
        return copy;
    } else {
        Node<T> *curr = this->first;
        while(curr != NULL) {
            Node<T> *clonednode = curr->clone();
            Node<T> *prev = clonednode;
            if(copy->first == NULL) {
                copy->first = clonednode;
                copy->last  = clonednode;
            } else {
                copy->last->next = clonednode;
                clonednode->prev = copy->last;
                copy->last = copy->last->next;
            }
            curr = curr->next;
        }
        copy->length = this->length;
        return copy;
    }
}

template <class T>
void LinkedList<T>::push(T value) {
    if(this->length == 0) {
        this->first = new Node<T>(value);
        this->last = this->first;
        this->length += 1;
    } else {
        Node<T> *node = new Node<T>(value);
        node->prev = this->last;
        this->last->next = node;
        this->last = node;
        this->length += 1;
    }
}

template <class T>
T LinkedList<T>::pop() {
    return NULL;
}

template <class T>
void LinkedList<T>::unshift(T value) {
    if(this->length == 0) {
        this->first = new Node<T>(value);
        this->last = this->first;
        this->length += 1;
    } else {
        Node<T> *node = new Node<T>(value);
        node->next = this->first;
        this->first->prev = node;
        this->first = node;
        this->length += 1;
    }
}

template <class T>
T LinkedList<T>::shift() {
    return NULL;
}

template <class T>
void LinkedList<T>::concat(LinkedList *that) {
    if(this->last == NULL) {
        this->first = that->first;
    } else {
        this->last->next = that->first;
    }
    this->last    = that->last;
    this->length += that->length;
}

template <class T>
T LinkedList<T>::nth_value(int index) {
    return this->nth(index)->value;
}

template <class T>
Node<T> *LinkedList<T>::nth(int n) {
    Node<T> *curr = this->first;
    for(int i = 0; i < n; i++) {
        if(curr == NULL) break;
        curr = curr->next;
    }
    return curr;
}

template <class T>
Node<T> *LinkedList<T>::midpoint() {
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

template <class T>
void LinkedList<T>::merge(LinkedList<T> *that) {
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

template <class T>
void LinkedList<T>::sort() {
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

template <class T>
bool LinkedList<T>::nodeBetween(Node<T> *target, Node<T> *start, Node<T> *end) {
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

template <class T>
bool LinkedList<T>::nodeBetweenIndices(Node<T> *target, int start, int end) {
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

template <class T>
bool LinkedList<T>::hasCycle() {
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

template <class T>
Node<T> *LinkedList<T>::cycleStart() {
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
