// Korey Huskonen

#include <iostream>
#include <ctime>
#include <sstream>
#include "lab5.cpp"
#include "student.cpp"

using namespace std;

int main(){
    olinkedlist<Student> student_directory;
    string input; // generic variable for storing user input
    int menu_selection;
    bool return_to_menu = true;

    do {

        do {
            cout << endl
                 << "***** Student Directory *****" << endl
                 << "1. Add Student" << endl
                 << "2. Find Student by MNumber" << endl
                 << "3. Check if Student is in Directory " << endl
                 << "4. Check if Directory is empty" << endl
                 << "5. Check size of Directory" << endl
                 << "6. Check Student at given location in Directory (seeAt)" << endl
                 << "7. Check the next Student in the Directory (seeNext)" << endl
                 << "8. Reset seeNext to the beginning" << endl
                 << "9. Display Student Directory" << endl
                 << "10. Exit" << endl
                 << "Enter your selection: ";
            getline(cin, input);
            stringstream(input) >> menu_selection;
        } while(menu_selection < 1 || menu_selection > 9);

        if(menu_selection == 1){
            string fname, lname, mnum;
            float gpa = 0;
            cout << "\n___ Add Student ___\n"
                 << "Enter student's first name: ";
            getline(cin, fname);
            cout << "Enter student's last name: ";
            getline(cin, lname);
            bool flag;
            do {
                flag = false;
                cout << "\nEnter student's MNumber (include the M): ";
                getline(cin, mnum);
                cout << "\n";
                if(mnum.length() != 9){
                    cout << "MNumber must be 9 characters long\n";
                    flag = true;
                }
                if(mnum[0] != 'M'){
                    cout << "MNumber must begin with 'M'\n";
                    flag = true;
                }
                for(int i = 1; i < 9; i++){
                    if(!isdigit(mnum[i])){
                        cout << "The last 8 characters must be numbers\n";
                        flag = true;
                        break;
                    }
                }
            } while(flag);
            cout << "(Optional) Enter student's GPA? (y/n) ";
            getline(cin, input);
            if(input == "y" || input == "Y" || input == "yes"){
                do {
                    cout << "\nEnter student's GPA (0-4): ";
                    getline(cin, input);
                    try {
                        gpa = stof(input);
                    } catch(...) {
                        gpa = -1;
                    }
                    if(gpa < 0 || gpa > 4) cout << "\nGPA must be 0-4\n";
                } while(gpa < 0 || gpa > 4);
            }
            int m, d, y;
            tm bd;
            do {
                cout << "Enter student's birth month (1-12): ";
                getline(cin, input);
                stringstream(input) >> m;
                if(m < 1 || m > 12) cout << "Birth month must be 1-12\n";
            } while(m < 1 || m > 12);

            do {
                cout << "Enter student's birth day (1-31): ";
                getline(cin, input);
                stringstream(input) >> d;
                if(d < 1 || d > 31) cout << "Birth day must be 1-31\n";
            } while(d < 1 || d > 31);

            time_t curr_time = time(NULL); // time_t structure from ctime library
            tm *curr_date = localtime(&curr_time); // tm structure from ctime library
            int curr_year = curr_date->tm_year + 1900;
            do {
                cout << "Enter student's birth year (1910-" << curr_year << "): ";
                getline(cin, input);
                stringstream(input) >> y;
                if(y < 1910 || y > curr_year) cout << "Birth year must be 1910-" << curr_year << "\n";
            } while(y < 1910 || y > curr_year);
            cout << endl;
            bd.tm_mon = m - 1;
            bd.tm_mday = d;
            bd.tm_year = y - 1900;
            Student new_student(fname, lname, mnum, gpa);
            new_student.setBirthday(&bd);
            new_student.display();
            student_directory.addItem(new_student);

        } else if(menu_selection == 2){
            cout << "\nEnter student's MNumber: ";
            getline(cin, input);
            Student* student = student_directory.getItem(input);
            if(student){
                cout << endl;
                student->display();
            } else {
                cout << "\nThis student is not in the directory" << endl;
            }

        } else if(menu_selection == 3){
            cout << "\nEnter student's MNumber: ";
            getline(cin, input);
            if(student_directory.isInList(input)){
                cout << "This student is in the directory" << endl;
            } else {
                cout << "This student is not in the directory" << endl;
            }

        } else if(menu_selection == 4){
            if(student_directory.isEmpty()){
                cout << "\nYes, the directory is empty" << endl;
            } else {
                cout << "\nNo, the directory is not empty" << endl;
            }

        } else if(menu_selection == 5){
            cout << "\nThe directory contains " << student_directory.size() << (student_directory.size() == 1 ? " student" : " students") << endl;

        } else if(menu_selection == 6){
            if(student_directory.isEmpty()){
                cout << "\nThere are currently no students in the directory" << endl;
                break;
            }
            Student *student = NULL;
            int index;
            cout << "\nEnter the location you want to see: ";
            getline(cin, input);
            stringstream(input) >> index;
            try {
                student = student_directory.seeAt(index);
            } catch(...) {
                cout << "\nInvalid location\nYou can only search locations 0-" << student_directory.size() - 1 << endl;
            }
            if(student){
                cout << "\nThe student at location " << index << " is " << student->getName() << "\n\n";
                student->display();
            }

        } else if(menu_selection == 7){
            Student *student = NULL;
            try {
                student = student_directory.seeNext();
                if(student){
                    cout << "\nThe next student is " << student->getName() << "\n\n";
                    student->display();
                } else {
                    cout << "\nYou have reached the end of the directory and need to reset seeNext" << endl;
                }
            } catch(...) {
                cout << "\nThe list is empty" << endl;
            }

        } else if(menu_selection == 8){
            student_directory.reset();
            cout << "\nseeNext has been reset" << endl;

        } else if(menu_selection == 9){
                node<Student> *curr_node = student_directory.start();
                for(int i = 0; i < student_directory.size(); i++){
                    cout << endl << i << ":" << endl;
                    curr_node->info.display();
                    curr_node = curr_node->next;
                }

        } else {
            return_to_menu = false;
        }

    } while(return_to_menu);

}

// Korey Huskonen
