#include <iostream>
#include <algorithm>
#include "AVLTree.hpp"
using namespace std;


template <class K, class V>
AVLTree<K,V>::AVLTree() {
    this->root = NULL;
}

template <class K, class V>
AVLTree<K,V>::~AVLTree() {
    delete this->root;
}

template <class K, class V>
void AVLTree<K,V>::insert(K key, V value) {
    AVLNode<K,V> *node = new AVLNode<K,V>(key, value);
    if(this->root == NULL) {
        this->root = node;
        node->tree = this;
    } else {
        this->root->insertNode(node);
        node->tree = this;
    }
}


template <class K, class V>
AVLNode<K,V>::AVLNode(K key, V value) {
    this->key = key;
    this->value = value;
    this->depth = 1;
    this->size = 1;
    this->left   = NULL;
    this->right  = NULL;
    this->parent = NULL;
}

template <class K, class V>
AVLNode<K,V>::~AVLNode() {
    if(this->size > 0) {
        delete this->left;
        delete this->right;
    }
}

template <class K, class V>
void AVLNode<K,V>::rotate_left() {
    //      P              P
    //      |              |
    //      A              B
    //     / \            / \
    //    L   B    =>    A   R
    //       / \        / \
    //      M   R      L   M
    AVLNode<K,V> *p = this->parent;
    AVLNode<K,V> *a = this;
    AVLNode<K,V> *b = this->right;
    AVLNode<K,V> *l = a->left;
    AVLNode<K,V> *m = b->left;
    AVLNode<K,V> *r = b->right;
    /*
    cout << "     " << (p == NULL ? -1 : p->key) << "      >";
    cout << "     " << (p == NULL ? -1 : p->key) << "      >";
    cout << endl;
    cout << "     |" << "       >";
    cout << "     |" << "       >";
    cout << endl;
    cout << "     " << (a == NULL ? -1 : a->key) << "      >";
    cout << "     " << (b == NULL ? -1 : b->key) << "      >";
    cout << endl;
    cout << "    / \\" << "      >";
    cout << "    / \\" << "      >";
    cout << endl;
    cout << "   " << (l == NULL ? -1 : l->key) << "  " << (b == NULL ? -1 : b->key) << "    >";
    cout << "   " << (a == NULL ? -1 : a->key) << "  " << (r == NULL ? -1 : r->key) << "    >";
    cout << endl;
    cout << "      / \\" << "    >";
    cout << "  / \\" << "        >";
    cout << endl;
    cout << "     " << (m == NULL ? -1 : m->key) << "  " << (r == NULL ? -1 : r->key) << "  >";
    cout << " " << (l == NULL ? -1 : l->key) << "  " << (m == NULL ? -1 : m->key) << "      >";
    cout << endl;
    */
    if(this == this->tree->root) {
        this->tree->root = b;
        b->parent  = NULL;
    } else {
        if(p->left == a) {
            p->left   = b;
            b->parent = p;
        } else {
            p->right  = b;
            b->parent = p;
        }
    }
    b->left  = a;
    b->right = r;
    a->left  = l;
    a->right = m;

    if(a != NULL) a->parent = b;
    if(r != NULL) r->parent = b;
    if(l != NULL) l->parent = a;
    if(m != NULL) m->parent = a;

    int adepth = (a == NULL) ? 0 : a->depth;
    int rdepth = (r == NULL) ? 0 : r->depth;
    int ldepth = (l == NULL) ? 0 : l->depth;
    int mdepth = (m == NULL) ? 0 : m->depth;

    a->depth = std::max(ldepth, mdepth) + 1;
    b->depth = std::max(adepth, rdepth) + 1;
}

template <class K, class V>
void AVLNode<K,V>::rotate_right() {
    //      P              P
    //      |              |
    //      A              B
    //     / \            / \
    //    B   R    =>    L   A
    //   / \                / \
    //  L   M              M   R
    AVLNode<K,V> *p = this->parent;
    AVLNode<K,V> *a = this;
    AVLNode<K,V> *b = this->left;
    AVLNode<K,V> *l = b->left;
    AVLNode<K,V> *m = b->right;
    AVLNode<K,V> *r = a->right;
    if(this == this->tree->root) {
        this->tree->root = b;
        b->parent  = NULL;
    } else {
        if(p->left == a) {
            p->left   = b;
            b->parent = p;
        } else {
            p->right  = b;
            b->parent = p;
        }
    }
    b->left  = l;
    b->right = a;
    a->left  = m;
    a->right = r;

    if(l != NULL) l->parent = b;
    if(a != NULL) a->parent = b;
    if(m != NULL) m->parent = a;
    if(r != NULL) r->parent = a;

    int ldepth = (l == NULL) ? 0 : l->depth;
    int adepth = (a == NULL) ? 0 : a->depth;
    int mdepth = (m == NULL) ? 0 : m->depth;
    int rdepth = (r == NULL) ? 0 : r->depth;

    a->depth = std::max(mdepth, rdepth) + 1;
    b->depth = std::max(ldepth, adepth) + 1;
}

template <class K, class V>
void AVLNode<K,V>::balance() {
    int ldepth = this->left  == NULL ? 0 : this->left->depth;
    int rdepth = this->right == NULL ? 0 : this->right->depth;
    bool isUnbalanced = false;
    if(ldepth - rdepth >= 2) {
        isUnbalanced = true;
        int lldepth = this->left->left  == NULL ? 0 : this->left->left->depth;
        int lrdepth = this->left->right == NULL ? 0 : this->left->right->depth;
        if(lrdepth - lldepth >= 1) {
            this->left->rotate_left();
        }
        this->rotate_right();
    } else if(rdepth - ldepth >= 2) {
        isUnbalanced = true;
        int rldepth = this->right->left  == NULL ? 0 : this->right->left->depth;
        int rrdepth = this->right->right == NULL ? 0 : this->right->right->depth;
        if(rldepth - rrdepth >= 1) {
            this->right->rotate_right();
        }
        this->rotate_left();
    }
    if(isUnbalanced) {
        AVLNode<K,V> *curr = this;
        while(curr != NULL) {
            curr->balance();
            curr = curr->parent;
        }
    }
}

template <class K, class V>
void AVLNode<K,V>::insertNode(AVLNode<K,V> *node) {
    AVLNode<K,V> *curr = this->parent;
    while(curr != NULL) {
        if(node == curr) {
            cout << "Something went circular." << endl;
            throw 0;
        }
        curr = curr->parent;
    }
    if(node->key < this->key) {
        if(this->left == NULL) {
            this->left = node;
            node->parent = this;
        } else {
            this->left->insertNode(node);
        }
    } else {
        if(this->right == NULL) {
            this->right = node;
            node->parent = this;
        } else {
            this->right->insertNode(node);
        }
    }
    int ldepth = this->left == NULL ? 0 : this->left->depth;
    int rdepth = this->right == NULL ? 0 : this->right->depth;
    this->depth = std::max(ldepth, rdepth) + 1;

    this->balance();
}

template <class K, class V>
void AVLNode<K,V>::print(std::string prefix = "", bool isLeft = false) {
    if(this->left == NULL && this->right == NULL) {
        if(isLeft) cout << prefix << "┌───";
        else       cout << prefix << "└───";
        cout << " " << this->key << " => " << this->value << endl; 
        return;
    } else {
        if(left == NULL) {
            if(isLeft) cout << prefix << "  ┌─── NULL" << endl;
            else       cout << prefix << "  ┌─── NULL" << endl;
        } else {
            if(isLeft) this->left->print(prefix + "  ", true);
            else       this->left->print(prefix + "│ ", true);
        }

        if(isLeft) cout << prefix << "┌─┼─";
        else       cout << prefix << "└─┼─";
        cout << " " << this->key << " => " << this->value << endl; 

        if(right == NULL) {
            if(isLeft) cout << prefix << "  └─── NULL" << endl;
            else       cout << prefix << "  └─── NULL" << endl;
        } else {
            if(isLeft) this->right->print(prefix + "│ ", false);
            else       this->right->print(prefix + "  ", false);
        }
    }
}
