#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "singly_linked_node.hpp"
using namespace std;

template <class T>
Node<T>::Node(T value) {
    this->value = value;
    this->next = (Node<T> *)NULL;
}

template <class T>
Node<T>::~Node() { }

template <class T>
Node<T> *Node<T>::clone() {
    Node<T> *copy = new Node<T>(this->value);
    return copy;
}

template <class T>
ostream &operator<<(ostream &os, Node<T> node) {
    cout << "(Node " << node.value << ")";
}
