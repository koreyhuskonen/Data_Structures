#include <iostream>

using namespace std;

template <class T> struct Node {
    Node *left, *right;
    T val;
    Node() : left(), right() {}
};

template <class T> class BST {
    int height;
    Node<T>* root;
    void insert_helper(Node<T>* new_node, Node<T>** curr){
        if(*curr == NULL){
            *curr = new_node;
            return;
        }
        if(new_node->val < (*curr)->val){
            insert_helper(new_node, &(*curr)->left);
        } else {
            insert_helper(new_node, &(*curr)->right);
        }
    }
public:
    BST() : height(0), root() {}
    void insert(T val){
        Node<T>* new_node = new Node<T>;
        new_node->val = val;
        insert_helper(new_node, &root);
    }
};

int main(){
    BST<int> test;
    test.insert(55);
    test.insert(2);

}
