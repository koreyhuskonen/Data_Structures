#include <iostream>
#include <ctime>

using namespace std;

class Student {
    string FirstName, LastName, MNumber;
    float GPA;
    time_t Birthday;
public:
    Student() {}
    Student(string fname, string lname, string mnum, float gpa=0)
    : FirstName(fname), LastName(lname), MNumber(mnum), GPA(gpa) {}
    string getName(){return FirstName + " " + LastName;}
    string getMNumber(){return MNumber;}
    void setBirthday(tm *bday){
        // create unix timestamp
        Birthday = mktime(bday);
    }
    char* getBirthday(){
        // convert timestamp to readable text
        return ctime(&Birthday);
    }
    int getAge(){
        // find difference between current time and birthday in seconds, convert to years
        return (time(0) - Birthday)/(60*60*24*365);
    }
    bool operator>(const Student &s){
        return MNumber > s.MNumber;
    }
    bool operator<(const Student &s){
        return MNumber < s.MNumber;
    }
    bool operator==(const Student &s){
        return MNumber == s.MNumber;
    }
    bool operator==(string id){
        return MNumber == id;
    }
};


// int main(){
// //     string name = "M10336480";
// //     int temp = stoi(name.substr(1));
// //
// //     tm test;
// //     test.tm_mon = 8;
// //     test.tm_year = 117;
// //     time_t now = time(NULL);
// //     time_t newb_time = mktime(&test);
// //     cout << ctime(&newb_time) << endl;
// //     cout << ctime(&now) << endl;
// //     cout << (now - newb_time)/(60*60*24) << endl;
//     // Student newb("K","K","M10336480");
//     // Student test("K","K","M10336580");
// //     test.setBirthday("02041976");
// //     newb.setBirthday("02041976");
// //     cout << test.getBirthday() << endl;
// //     cout << newb.getBirthday() << endl;
//     // cout << (newb == "M10336480") << endl;
// }
