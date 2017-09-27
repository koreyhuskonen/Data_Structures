#include <iostream>
#include <ctime>
#include <sstream>
#include "lab5.cpp"
#include "student.cpp"

using namespace std;

int main(){
    olinkedlist<Student> student_directory;
    string input;
    int menu_selection;
    do {
        cout << "***** Student Directory *****" << endl
             << "1. Add Student" << endl
             << "2. Find Student by MNumber" << endl
             << "3. Check if Student is in Directory " << endl
             << "4. Check if Directory is empty" << endl
             << "5. Check size of Directory" << endl
             << "6. Check Student at given position in Directory (seeAt)" << endl
             << "7. Check the next Student in the Directory (seeNext)" << endl
             << "8. Reset seeNext to the beginning" << endl
             << "9. Exit" << endl
             << "Enter your selection: ";
        getline(cin, input);
        stringstream(input) >> menu_selection;
    } while(menu_selection < 1 || menu_selection > 9);

    if(menu_selection == 1){
        string fname, lname, mnum;
        int gpa = 0;
        cout << "\n___ Add Student ___\n"
             << "Enter student's first name: ";
        getline(cin, fname);
        cout << "Enter student's last name: ";
        getline(cin, lname);
        cout << "Enter student's MNumber (include the M): ";
        getline(cin, mnum);
        cout << "(Optional) Enter student's GPA? (y/n) ";
        getline(cin, input);
        if(input == "y" || input == "Y" || input == "yes"){
            do {
                cout << "Enter student's GPA: ";
                cin >> input;
                try {
                    gpa = stof(input);
                } catch(...) {
                    gpa = -1;
                }
                if(gpa < 0 || gpa > 4) cout << "\nGPA must be 0-4\n";
            } while(gpa < 0 || gpa > 4);
        }
        Student new_student(fname, lname, mnum, gpa);
        int month, day, year;
        do {
            cout << "Enter the student's birth month (1-12): ";
            getline(cin, input);
            stringstream(input) >> month;
            if(month < 1 || month > 12) cout << "\nBirth month must be 1-12\n";
        } while(month < 1 || month > 12);
        do {
            cout << "Enter the student's birth day (1-31): ";
            getline(cin, input);
            stringstream(input) >> day;
            if(day < 1 || day > 31) cout << "\nBirth day must be 1-31\n";
        } while(day < 1 || day > 31);
        time_t curr_time = time(0);
        tm *curr_date = localtime(&curr_time);
        int curr_year = curr_date->tm_year + 1900;
        cout << curr_year << endl;


        tm bday; // tm structure from ctime library


        // bday.tm_mon = stoi(input) - 1;
        // cout << bday.tm_mon << endl;
        // cout << "Enter the student's birth day: ";
        // getline(cin, input);
        // temp = stringstream(input);
        // cout << temp << endl;
        // stringstream(input) >> bday.tm_mday;

        // cout << "Enter the student's birth year: ";
        // getline(cin, input);
        // temp = stringstream(input) - 1900;
        // cout << temp << endl;
        // (stringstream(input) - 1900) >> bday.tm_year;
        // new_student.setBirthday(&bday);
        // cout << new_student.getBirthday() << endl;
        // int month = stoi(bday.substr(0,2)) - 1;
        // int day = stoi(bday.substr(2,2));
        // int year = stoi(bday.substr(4,4)) - 1900;
        // tm bday_tm;
        // bday_tm.tm_mon = month;
        // bday_tm.tm_mday = day;
        // bday_tm.tm_year = year;
    }
}
