#include <iostream>

using namespace std;

// Helper functions

struct node{
    int info;
    node *next;
};

node* insertAtEnd(node **head, int item){
    node *new_node, *curr_node;
    new_node = (node*)malloc(sizeof(node));
    new_node->info = item;
    new_node->next = NULL;
    if(*head == NULL){
        *head = new_node;
    } else {
        curr_node = *head;
        while(curr_node->next != NULL){
            curr_node = curr_node->next;
        }
        curr_node->next = new_node;
    }
    return new_node;
}

void displayLinkedList(node **head){
    int i = 0;
    node *curr_node = *head;
    while(curr_node != NULL){
        cout << i << ": " << curr_node->info << endl;
        curr_node = curr_node->next;
        i++;
        if(i > 20) return;
    }
    cout << "Size: " << i << endl;
}

// Question 1

void nthToLast(node **head, int n){
    // error trap
    if(n < 0){
        cout << "Cannot have negative index " << n << endl;
        return;
    }
    // create pointer to node and set it equal to head
    node *curr_node = *head;
    // check if list is empty
    if(curr_node == NULL){
        cout << "Empty list" << endl;
        return;
    }
    // initialize variable to store length of list
    int length;
    // iterate through each node of list until we reach the end (NULL)
    // add 1 to length each time
    for(length = 0; curr_node != NULL; length++) curr_node = curr_node->next;
    // check to see if list has an nth from last node (at most n can equal length - 1 since 0 = last node)
    if(n >= length){
        cout << "List is too short" << endl;
        return;
    }
    // reset curr_node to the beginning
    curr_node = *head;
    // iterate through list until we find the nth to last node
    for(int i = 1; i < length - n; i++) curr_node = curr_node->next;
    // display (or return) value at nth to last node
    cout << "Element " << n << " from the last: " << curr_node->info << endl;
}

// Question 2

void deleteNode(node **head, node **target){
    node *temp = (*target)->next;
    **target = *temp;
    delete temp;
    // node *prev, *curr_node = *head;
    // if(*target == *head){
    //     *head = curr_node->next;
    //     return;
    // }
    // while(curr_node != *target){
    //     if(curr_node == NULL){
    //         cout << "Target node is not in list" << endl;
    //         return;
    //     }
    //     prev = curr_node;
    //     curr_node = curr_node->next;
    // }
    // prev->next = curr_node->next;
    // delete curr_node;
}

// Question 3

void reverseList(node **head){
    // create pointer to a node and set it equal to head
    node *prev_node = NULL, *curr_node = *head, *next_node;
    // loop through linked list
    while(curr_node != NULL){
        // store the next node
        next_node = curr_node->next;
        // switch the next attribute of current node to point to previous node
        curr_node->next = prev_node;
        // store each previous node
        prev_node = curr_node;
        // move to next node
        curr_node = next_node;
    }
    // point the head at the last node (curr_node now = NULL, so we have to use prev_node)
    *head = prev_node;
}

// Question 4

bool detectLoop(node *head){
    // create two pointers
    node *fast_node = head, *slow_node = head;
    // check to see if we haven't reached the end of the list after the first node
    while(fast_node && fast_node->next){
        slow_node = slow_node->next;
        fast_node = fast_node->next->next;
        // if fast_node ever catches the slow_node, there must be a loop
        if(fast_node == slow_node) return true;
    }
    return false;
}

// Question 5

node *findMiddle(node *head){
    // make a second pointer to store the middle node
    node *middle = head;
    int counter = 0;
    // traverse linked list
    while(head->next){
        // only update the middle node half the time
        if(counter % 2){
            middle = middle->next;
        }
        head = head->next;
        counter++;
    }
    return middle;
}

// Question 6


// Question 7

node *find3rd(node *head){
    // need at least 3 elements
    if(head && head->next && head->next->next){
        // if there are more than 3, keep traversing until we reach third from last
        while(head->next->next->next) head = head->next;
        return head;
    }
    return NULL;
}

void createLoop(node *head){
    if(head == NULL){
        return;
    }
    node *curr_node = head, *end_node;
    int length = 1;
    while(curr_node->next){
        curr_node = curr_node->next;
        length++;
    }
    end_node = curr_node;
    curr_node = head;
    // for(int i = 0; i < length / 2; i++) curr_node = curr_node->next;
    end_node->next = curr_node;
}

int main(){
    node *head = NULL;
    insertAtEnd(&head, 1);
    insertAtEnd(&head, 2);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 4);
    node *target = insertAtEnd(&head, 5);
    insertAtEnd(&head, 21);
    insertAtEnd(&head, 7);
    insertAtEnd(&head, 42);
    insertAtEnd(&head, 570);
    insertAtEnd(&head, 15);
    insertAtEnd(&head, 65);
    displayLinkedList(&head);
    cout << "deleting" << endl;
    deleteNode(&head, &target);
    displayLinkedList(&head);

    // cout << findMiddle(head)->info << endl;
}
