#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include "stack_class.cpp"

using namespace std;

const int num_towers = 5;

class Hanoi {
    int num_discs;
    Stack<string>* towers[num_towers];
public:
    Hanoi(int num_discs) : num_discs(num_discs) {
        for(int i = 0; i < num_towers; i++) towers[i] = new Stack<string>(num_discs);
        for(int i = num_discs; i > 0; i--){
            string *temp1 = new string, *temp2 = new string;
            *temp1 = "L" + to_string(i);
            *temp2 = "R" + to_string(i);
            towers[0]->push(temp1);
            towers[num_towers-1]->push(temp2);
        }
    }
    void moveDisc(Stack<string>* from, Stack<string>* to){
        if(!from->getTop()){
            cout << "Illegal! You cannot move a disc from an empty tower!" << endl;
            return;
        } else if(to->getTop() && *to->getTop() < *from->getTop()){
            cout << "Illegal! You cannot move a bigger disc onto a smaller one!" << endl;
            return;
        }
        to->push(from->pop());
    }
    void display(){
        for(int i = 0; i < num_towers; i++){
            cout << i << ":"; displayStack(*towers[i]); cout << endl;
        }
    }
};

int main(){
    string input;
    int num_discs, turn_count = 0;

    cout << "\nWelcome to..." << endl
         << " _/\\_     _/\\_     _/\\_ \n"
         << "  ||       ||       ||\n"
         << "  ||       ||       ||\n"
         << "  ||       ||       ||\n"
         << "  ||       ||       ||\n"
         << "  ||       ||       ||\n"
         << "------------------------\n"
         << "  ...the Towers of Hanoi\n\n";
    do {
        cout << "Enter the number of discs (at least 2): ";
        getline(cin, input);
        stringstream(input) >> num_discs;
    } while(num_discs < 2);
    Hanoi game(num_discs);
    game.display();

}
