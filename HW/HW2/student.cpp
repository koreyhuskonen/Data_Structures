#include <iomanip>

class Student {
    std::string FirstName, LastName, MNumber;
    float GPA;
public:
    Student() {}
    Student(std::string fname, std::string lname, std::string mnum)
    : FirstName(fname), LastName(lname), MNumber(mnum) {}
    std::string getName(){return FirstName + " " + LastName;}
    std::string getFirstName(){return FirstName;}
    std::string getLastName(){return LastName;}
    std::string getMNumber(){return MNumber;}
    void display(){
        std::cout << "Name: " << std::left << std::setw(30) << getName() << "MNumber: " << getMNumber() << std::endl;
    }
    bool firstNameGreater(Student& s){return FirstName > s.getFirstName();}
    bool lastNameGreater(Student& s){return LastName > s.getLastName();}
    bool mnumNameGreater(Student& s){return MNumber > s.getMNumber();}

};
