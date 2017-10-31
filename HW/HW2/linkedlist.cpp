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
    Node* head;
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

Node* SortedMerge(struct Node* a, struct Node* b){
    Node* result = NULL;

    /* Base cases */
    if (a == NULL)
     return(b);
    else if (b == NULL)
     return(a);

    /* Pick either a or b, and recur */
    if (a->info->firstNameGreater(b->info)){
     result = a;
     result->next = SortedMerge(a->next, b);
    } else {
     result = b;
     result->next = SortedMerge(a, b->next);
    }
    return(result);
}

void halve(Node* source, Node** frontRef, Node** backRef)
{
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

void MergeSort(Node** headRef){
    Node* head = *headRef;
    Node* a;
    Node* b;

    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL)){
        return;
    }

    /* Split head into 'a' and 'b' halves */
    halve(head, &a, &b);

    /* Recursively sort the sublists */
    MergeSort(&a);
    MergeSort(&b);

    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b);
}

LL generateStudents(int num_students){
    string name;
    vector<string> firstnames, lastnames;
    // read in student names
    ifstream inFile;
    inFile.open("firstnames.txt");
    while( getline(inFile, name) ){
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
    MergeSort(students.getHead());
    cout << "_______" << endl;
    students.display();
}
