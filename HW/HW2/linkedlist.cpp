#include <iostream>
#include <fstream>
#include <vector>
#include "student.cpp"

using namespace std;

struct Node {
    Student* info;
    Node* next;
    ~Node(){
        delete info;
    }
};

class LL {
    Node *head, *tail;
public:
    LL() : head() {}
    void addItem(Student* new_student){
        Node* new_node = new Node;
        new_node->info = new_student;
        new_node->next = head;
        head = new_node;
    }
    void display(){
        Node* curr_node = head;
        while(curr_node){
            curr_node->info->display();
            curr_node = curr_node->next;
        }
    }
    Node** getHead(){return &head;}
    ~LL(){
        while(head){
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

Node* getTail(Node* head){
    while(head->next) head = head->next;
    return head;
}

Node *partition(Node *head, Node *end, Node **newHead, Node **newEnd, int order){
    struct Node *pivot = end;
    struct Node *prev = NULL, *cur = head, *tail = pivot;
    // During partition, both the head and end of the list might change
    // which is updated in the newHead and newEnd variables
    if(order == 0){
        while(cur != pivot){
            if(cur->info->lastNameGreater(pivot->info)){
                // If cur node is greater than pivot
                // Move cur node to next of tail, and change tail
                if(prev) prev->next = cur->next;
                Node *tmp = cur->next;
                cur->next = NULL;
                tail->next = cur;
                tail = cur;
                cur = tmp;
            } else {
                // First node that has a value less than the pivot - becomes
                // the new head
                if(*newHead == NULL) *newHead = cur;
                prev = cur;
                cur = cur->next;
            }
        }
    } else {
        while(cur != pivot){
            if(cur->info->lastNameGreater(pivot->info)){
                // First node that has a value less than the pivot - becomes
                // the new head
                if(*newHead == NULL) *newHead = cur;
                prev = cur;
                cur = cur->next;
            } else {
                // If cur node is greater than pivot
                // Move cur node to next of tail, and change tail
                if(prev) prev->next = cur->next;
                Node *tmp = cur->next;
                cur->next = NULL;
                tail->next = cur;
                tail = cur;
                cur = tmp;
            }
        }
    }
    // If the pivot data is the smallest element in the current list,
    // pivot becomes the head
    if(*newHead == NULL)
        *newHead = pivot;
    // Update newEnd to the current last node
    *newEnd = tail;
    // Return the pivot node
    return pivot;
}

Node* quickSortRecur(Node *head, Node *end, int order){
    // base condition
    if(!head || head == end)
        return head;
    Node *newHead = NULL, *newEnd = NULL;
    // Partition the list, newHead and newEnd will be updated
    // by the partition function
    Node *pivot = partition(head, end, &newHead, &newEnd, order);
    // If pivot is the smallest element - no need to recur for
    // the left part.
    if(newHead != pivot){
        // Set the node before the pivot node as NULL
        Node *tmp = newHead;
        while(tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;
        // Recur for the list before pivot
        newHead = quickSortRecur(newHead, tmp, order);
        // Change next of last node of the left half to pivot
        tmp = getTail(newHead);
        tmp->next = pivot;
    }
    // Recur for the list after the pivot element
    pivot->next = quickSortRecur(pivot->next, newEnd, order);
    return newHead;
}

// The main function for quick sort. This is a wrapper over recursive
// function quickSortRecur()
void quickSort(Node **headRef, int order=0){
    *headRef = quickSortRecur(*headRef, getTail(*headRef), order);
    return;
}

Node* SortedMerge(Node* a, Node* b, int order=0){
    Node* result = NULL;

    /* Base cases */
    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;

    /* Pick either a or b, and recur */
    if(order == 0){     // descending order
        if (a->info->firstNameGreater(b->info)){
            result = b;
            result->next = SortedMerge(a, b->next);
        } else {
            result = a;
            result->next = SortedMerge(a->next, b);
        }
    } else {            // ascending order
        if (a->info->firstNameGreater(b->info)){
            result = a;
            result->next = SortedMerge(a->next, b, order);
        } else {
            result = b;
            result->next = SortedMerge(a, b->next, order);
        }
    }
    return result;
}

void halve(Node* source, Node** frontRef, Node** backRef){
    Node* fast;
    Node* slow;
    if(source == NULL || source->next == NULL){
        /* length < 2 cases */
        *frontRef = source;
        *backRef = NULL;
    } else {
        slow = source;
        fast = source->next;
        /* Advance 'fast' two nodes and 'slow' one node */
        while(fast != NULL){
            fast = fast->next;
            if(fast != NULL){
                slow = slow->next;
                fast = fast->next;
            }
        }
        /* 'slow' is before the midpoint in the list, so split it in two
          at that point. */
        *frontRef = source;
        *backRef = slow->next;
        slow->next = NULL;
    }
}

void MergeSort(Node** headRef, int order=0){
    Node* head = *headRef;
    Node* a;
    Node* b;

    /* Base case -- length 0 or 1 */
    if((head == NULL) || (head->next == NULL)){
        return;
    }

    /* Split head into 'a' and 'b' halves */
    halve(head, &a, &b);

    /* Recursively sort the sublists */
    MergeSort(&a, order);
    MergeSort(&b, order);

    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b, order);
}

void sortedInsert(Node** head, Node* curr){
    if(!(*head) || (*head)->info->mnumNameGreater(curr->info)){
        curr->next = *head;
        *head = curr;
    } else {
        Node* temp = *head;
        while(temp->next && curr->info->mnumNameGreater(temp->next->info)){
            temp = temp->next;
        }
        curr->next = temp->next;
        temp->next = curr;
    }
}

void insertionSort(Node** head){
    Node *current = *head, *sorted = NULL;
    while(current){
        Node* temp = current->next;
        sortedInsert(&sorted, current);
        current = temp;
    }
    *head = sorted;
}

LL generateStudents(int num_students){
    string name;
    vector<string> firstnames, lastnames;
    // read in student names
    ifstream inFile;
    inFile.open("firstnames.txt");
    while( getline(inFile, name) ){
        // clean string or else it screws up formatting
        for(int i = 0; i < name.length(); i++){
            if(!isalpha(name[i])) name[i] = ' ';
        }
        firstnames.push_back(name);
    }
    inFile.close();
    inFile.open("lastnames.txt");
    while( getline(inFile, name) ){
        lastnames.push_back(name);
    }
    inFile.close();
    LL students;
    // generate random students and add them to linked list
    srand(time(0));
    for(int j = 0; j < num_students; j++){
        string firstname, lastname, mnum;
        int i = rand() % firstnames.size();
        firstname = firstnames[i];
        i = rand() % lastnames.size();
        lastname = lastnames[i];
        i = rand() % 100000000;
        mnum = 'M' + to_string(i);
        while(mnum.length() < 9) mnum += '0'; // Make sure MNumber is 9 characters
        Student* new_student = new Student(firstname, lastname, mnum);
        students.addItem(new_student);
    }
    return students;
}

int main(){
    LL students = generateStudents(10);
    students.display();
    insertionSort(students.getHead());
    cout << "_______" << endl;
    students.display();

}
