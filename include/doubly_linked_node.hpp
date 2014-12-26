template <class T>
class Node {
    public:
        T value;
        Node<T> *next;
        Node<T> *prev;
        Node (T value);
        ~Node();
        Node<T> *clone();
};
