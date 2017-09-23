// base of stack = -1
// example of queue - printing queue which spools out jobs (prints)
// 2 types of functions: user level (defined) functions
//                       kernel level functions


#include <iostream>

using namespace std;

typedef struct nodetype {
    int info;
    struct nodetype *next = NULL;
} node;

typedef struct {
    node *front = NULL;
    node *rear = NULL;
    void enqueue(int n){
        node *new_node = new node;
        new_node->info = n;
        if(front){
            rear->next = new_node;
            rear = new_node;
        } else {
            front = rear = new_node;
        }
    }
    void display(){
        node *curr_node = front;
        int i = 0;
        while(curr_node){
            cout << i << ": " << curr_node->info << endl;
            curr_node = curr_node->next;
            i++;
        }
    }
    void dequeue(){
        if(front){
            cout << front->info << endl;
            node *temp = front;
            if(front == rear){
                rear = front = NULL;
            } else {
                front = front->next;
            }
            delete temp;
        }
    }
} queue;

int main(){
    queue q;
    q.enqueue(5);
    q.enqueue(43);
    q.enqueue(23);
    q.enqueue(34);
    q.display();

    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();


    q.display();

}
