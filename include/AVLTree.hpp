template <class K, class V> class AVLTree;
template <class K, class V> class AVLNode;

template <class K, class V>
class AVLNode {
    public:
        K key;
        V value;
        AVLNode<K,V> *left;
        AVLNode<K,V> *right;
        AVLNode<K,V> *parent;
        AVLTree<K,V> *tree;
        int size;
        int depth;
        AVLNode(K key, V value);
        ~AVLNode();
        void balance();
        void rotate_left();
        void rotate_right();
        void insertNode(AVLNode<K,V> *node);
        V lookup(K key);
        void print(std::string prefix, bool isLeft);
};

template <class K, class V>
class AVLTree {
    public:
        AVLNode<K,V> *root;
        AVLTree();
        ~AVLTree();
        void insert(K key, V value);
};
