#include <iostream>

using namespace std;

template <class T> struct node {
    T info;
    node<T> *next;
};

template <class T> class olinkedlist {
    node<T> *head;
public:
    olinkedlist() : head() {}
    void addItem(T *item){
        node<T> *new_node = new node<T>;
        new_node->info = *item;
        node<T> *temp1 = head, **temp2 = &head;
        while(temp1 && temp1->info < new_node->info){
            temp2 = &temp1->next;
            temp1 = temp1->next;
        }
        *temp2 = new_node;
        new_node->next = temp1;

        // if(!head){
        //     head = new_node;
        //     return;
        // } else if(head->info > *item){
        //     new_node->next = head;
        //     head = new_node;
        //     return;
        // }
        // node<T> *curr_node = head, *prev;
        // while(curr_node && curr_node->info <= *item){
        //     prev = curr_node;
        //     curr_node = curr_node->next;
        // }
        // prev->next = new_node;
        // new_node->next = curr_node;
    }
    void display(){
        node<T> *curr_node = head;
        int i = 0;
        while(curr_node){
            cout << i << ": " << curr_node->info << endl;
            curr_node = curr_node->next;
            i++;
        }
    }
};

int main(){
    olinkedlist<int> test;
    int a = 1, b = 2, c = 3, d = 5;
    test.addItem(&c);
    test.addItem(&a);
    test.addItem(&b);
    test.addItem(&d);
    test.addItem(&a);

    test.display();
}
