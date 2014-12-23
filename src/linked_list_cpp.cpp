#include <iostream>
using namespace std;

template <class T>
class Node {
    public:
        T element;
        Node<T> *next;

        Node (T arg) {
            element = arg;
        }
};

int main(void) {
    Node<int> a (1);
    Node<int> b (2);
    cout << a.element << "\n";
    a.next = &b;
    cout << a.next->element << "\n";
    return 0;
}
