class Student {
    string FirstName, LastName, MNumber;
    float GPA;
public:
    Student() {}
    Student(string fname, string lname, string mnum, float gpa=0)
    : FirstName(fname), LastName(lname), MNumber(mnum), GPA(gpa) {}
    string getName(){return FirstName + " " + LastName;}
    string getFirstName(){return FirstName;}
    string getLastName(){return LastName;}
    void display(){
        cout << "Name: " << getName() << "  |  MNumber: " << getMNumber() << "  |  GPA: " << GPA << endl;
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
