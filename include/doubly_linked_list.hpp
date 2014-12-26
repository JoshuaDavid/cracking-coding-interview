#include <stdio.h>
#include <stdlib.h>
template <class T>
class LinkedList {
    public:
        Node<T> *first;
        Node<T> *last;
        int length;

        LinkedList(T *array, int length);
        ~LinkedList();
        bool equals(LinkedList *that, int verbose);
        LinkedList<T> *clone();
        void push(T value);
        T pop();
        void unshift(T value);
        T shift();
        void concat(LinkedList *that);
        Node<T> *nth(int n);
        T nth_value(int n);
        Node<T> *midpoint();
        void merge(LinkedList<T> *that);
        void sort();
        bool nodeBetween(Node<T> *target, Node<T> *start, Node<T> *end);
        bool nodeBetweenIndices(Node<T> *target, int start, int end);
        bool hasCycle();
        Node<T> *cycleStart();
};
