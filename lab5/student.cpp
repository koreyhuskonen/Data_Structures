#include <iostream>
#include <ctime>

using namespace std;

class Student {
    string FirstName, LastName, MNumber;
    float GPA;
    time_t Birthday;
public:
    Student(string fname, string lname, string mnum, float gpa=0)
    : FirstName(fname), LastName(lname), MNumber(mnum), GPA(gpa) {}
    string getName(){return FirstName + " " + LastName;}
    string getMNumber(){return MNumber;}
    void setBirthday(string bday){
        // string must be of form "mmddyyyy"
        int month = stoi(bday.substr(0,2)) - 1;
        int day = stoi(bday.substr(2,2));
        int year = stoi(bday.substr(4,4)) - 1900;
        tm bday_tm;
        bday_tm.tm_mon = month;
        bday_tm.tm_mday = day;
        bday_tm.tm_year = year;
        // create unix timestamp
        Birthday = mktime(&bday_tm);
    }
    char* getBirthday(){
        // convert timestamp to readable text
        return ctime(&Birthday);
    }
    int getAge(){
        // find difference between timestamps in seconds, convert to years
        return (time(NULL) - Birthday)/(60*60*24*365);
    }
    // bool operator>(const Student &s){
    //
    // }
};


int main(){
    // string name = "M10336480";
    // int temp = stoi(name.substr(1));

    // tm test;
    // test.tm_mon = 8;
    // test.tm_year = 117;
    // time_t now = time(NULL);
    // time_t newb_time = mktime(&test);
    // cout << ctime(&newb_time) << endl;
    // cout << ctime(&now) << endl;
    // cout << (now - newb_time)/(60*60*24) << endl;
    Student newb("K","K","2");
    Student test("K","K","2");
    test.setBirthday("02041976");
    newb.setBirthday("02041996");

}
