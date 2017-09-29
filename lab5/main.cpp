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
    do {

        do {
            cout << endl
                 << "***** Student Directory *****" << endl
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
                    cout << "\nEnter student's GPA: ";
                    getline(cin, input);
                    try {
                        gpa = stof(input);
                    } catch(...) {
                        gpa = -1;
                    }
                    if(gpa < 0 || gpa > 4) cout << "\nGPA must be between 0-4\n";
                } while(gpa < 0 || gpa > 4);
            }
            Student new_student(fname, lname, mnum, gpa);
            int month, day, year;
            do {
                cout << "Enter student's birth month (1-12): ";
                getline(cin, input);
                stringstream(input) >> month;
                if(month < 1 || month > 12) cout << "Birth month must be between 1-12\n";
            } while(month < 1 || month > 12);
            do {
                cout << "Enter student's birth day (1-31): ";
                getline(cin, input);
                stringstream(input) >> day;
                if(day < 1 || day > 31) cout << "Birth day must be between 1-31\n";
            } while(day < 1 || day > 31);
            time_t curr_time = time(0); // time_t structure from ctime library
            tm *curr_date = localtime(&curr_time); // tm structure from ctime library
            int curr_year = curr_date->tm_year + 1900;
            do {
                cout << "Enter student's birth year (1910-" << curr_year << "): ";
                getline(cin, input);
                stringstream(input) >> year;
                if(year < 1910 || year > curr_year) cout << "Birth year must be between 1910-" << curr_year << "\n";
            } while(year < 1910 || year > curr_year);
            tm bday_tm;
            bday_tm.tm_mon = month - 1;
            bday_tm.tm_mday = day;
            bday_tm.tm_year = year - 1900;
            new_student.setBirthday(&bday_tm);
            student_directory.addItem(&new_student);

        } else if(menu_selection == 2){
            cout << "Enter student's MNumber: ";
            getline(cin, input);
            Student* student = student_directory.getItem(input);
            if(student) cout << student->getName() << endl;

        } else if(menu_selection == 3){
            cout << "Enter student's MNumber: ";
            getline(cin, input);
            if(student_directory.isInList(input)){
                cout << "This student is in the directory" << endl;
            } else {
                cout << "This student is not in the directory" << endl;
            }

        } else if(menu_selection == 4){
            if(student_directory.isEmpty()){
                cout << "Yes, the Student Directory is empty" << endl;
            } else {
                cout << "No, the Student Directory is not empty" << endl;
            }
            
        }

    } while(true);

}
