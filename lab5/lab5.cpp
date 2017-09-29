#include <iostream>

using namespace std;

template <class T> struct node {
    T info;
    node<T> *next;
};

template <class T> class olinkedlist {
    node<T> *head, **next;
    int length;
public:
    olinkedlist() : head(), next(&head), length(0) {}
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
        length++;
    }
    T* getItem(string id){
        node<T> *curr_node = head;
        while(curr_node){
            if(curr_node->info == id){
                return &curr_node->info;
            }
            curr_node = curr_node->next;
        }
        return NULL;
    }
    bool isInList(string id){
        node<T> *curr_node = head;
        while(curr_node){
            if(curr_node->info == id) return true;
            curr_node = curr_node->next;
        }
        return false;
    }
    bool isEmpty(){return !head;}
    int size(){return length;}
    T* seeNext(){
        if(isEmpty()) throw "List is empty";
        if(*next == NULL) return NULL;
        T* temp = &(*next)->info;
        next = &(*next)->next;
        return temp;
    }
    T* seeAt(int i){
        if(i >= length || i < 0) throw "Invalid index";
        node<T> *curr_node = head;
        for(int j = 0; j < i; j++) curr_node = curr_node->next;
        next = &curr_node->next;
        return &curr_node->info;
    }
    void reset(){next = &head;}
    void display(){
        node<T> *curr_node = head;
        int i = 0;
        while(curr_node){
            cout << i << ": " << curr_node->info << endl;
            curr_node = curr_node->next;
            i++;
        }
    }
    bool operator<(const olinkedlist<T> &ol){return length < ol.length;}
    bool operator>(const olinkedlist<T> &ol){return length > ol.length;}
    bool operator==(const olinkedlist<T> &ol){
        if(length != ol.length) return false;
        node<T> *l1 = head, *l2 = ol.head;
        while(l1){
            if(l1->info != l2->info) return false;
            l1 = l1->next;
            l2 = l2->next;
        }
        return true;
    }
    ~olinkedlist(){
        node<T> *temp;
        while(head){
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// int main(){
//     srand(time(NULL));
//     olinkedlist<int> test, newb;
//     int temp;
//     for(int i = 0; i < 5; i++){
//         temp = rand() % 100;
//         test.addItem(&temp);
//         newb.addItem(&temp);
//     }
//     test.display();
//     cout << "getting item " << temp << endl;
//     cout << test.getItem(&temp) << endl;
//     temp = 100;
//     cout << test.isInList(&temp) << endl;
//     cout << test.size() << endl;
//     cout << test.isEmpty() << endl;
//     cout << *test.seeNext() << endl;
//     cout << *test.seeNext() << endl;
//     cout << *test.seeAt(2) << endl;
//     cout << *test.seeNext() << endl;
//     cout << *test.seeNext() << endl;
//     cout << test.seeNext() << endl;
//     test.reset();
//     cout << *test.seeNext() << endl;
//     cout << *test.seeNext() << endl;
//     cout << (test == newb) << endl;
// }
