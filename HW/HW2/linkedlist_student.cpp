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
    ~LL(){
        while(head){
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};



int main(){
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
    // generate random students and add them to linked list
    LL students;
    srand(time(0));
    for(int j = 0; j < 50; j++){
        string firstname, lastname, mnum;
        int i = rand() % firstnames.size();
        firstname = firstnames[i];
        i = rand() % lastnames.size();
        lastname = lastnames[i];
        i = rand() % 100000000;
        mnum = 'M' + to_string(i);
        while(mnum.length() < 9) mnum += '0';
        Student* new_student = new Student(firstname, lastname, mnum);
        students.addItem(new_student);
    }

    students.display();


}
