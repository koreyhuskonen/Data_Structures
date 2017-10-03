// Korey Huskonen

#include <iostream>
#include <ctime>
#include <sstream>

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
    void display(){
        cout << "Name: " << getName() << "  |  Age: " << getAge() << "  |  GPA: " << GPA << endl
             << "MNumber: " << getMNumber() << "  |  Birthday: " << getBirthday() << endl;
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

// Korey Huskonen
