#include <iostream>
#include <sstream>
#include "stack_class.cpp"

using namespace std;

class Hanoi {
    int num_discs;
    Stack<int> A, B, C;
public:
    Hanoi(int num_discs) : num_discs(num_discs), A(num_discs), B(num_discs), C(num_discs) {
        for(int i = num_discs; i > 0; i--){
            int* temp = new int;
            *temp = i;
            A.push(temp);
        }
    }
    Stack<int>* getA(){return &A;}
    Stack<int>* getB(){return &B;}
    Stack<int>* getC(){return &C;}
    void moveDisc(Stack<int>* from, Stack<int>* to){
        if(!from->getTop()){
            cout << "Illegal! You cannot move a disc from an empty tower!" << endl;
            return;
        } else if(to->getTop() && *to->getTop() < *from->getTop()){
            cout << "Illegal! You cannot move a bigger disc onto a smaller one!" << endl;
            return;
        }
        to->push(from->pop());
    }
    bool gameOver(){return C.length() == num_discs;}
    void display(){
        cout << "A:"; displayStack(A); cout << endl;
        cout << "B:"; displayStack(B); cout << endl;
        cout << "C:"; displayStack(C); cout << endl;
    }
};

int main(){
    string input;
    int num_discs, turn_count = 0, player_option;

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
    cout << "\nYour mission:\nMove one disc at a time until all discs are stacked in order on C\n";

    while(!game.gameOver()){
        turn_count++;
        cout << "\n_____ Turn " << turn_count << " _____\n";
        game.display();
        do {
            cout << "\nYour options:\n"
                 << "1. Move from A to B\n"
                 << "2. Move from A to C\n"
                 << "3. Move from B to A\n"
                 << "4. Move from B to C\n"
                 << "5. Move from C to A\n"
                 << "6. Move from C to B\n"
                 << "Your selection: ";
            getline(cin, input);
            stringstream(input) >> player_option;
        } while(player_option < 1 || player_option > 6);

        if(player_option == 1) game.moveDisc(game.getA(), game.getB());
        if(player_option == 2) game.moveDisc(game.getA(), game.getC());
        if(player_option == 3) game.moveDisc(game.getB(), game.getA());
        if(player_option == 4) game.moveDisc(game.getB(), game.getC());
        if(player_option == 5) game.moveDisc(game.getC(), game.getA());
        if(player_option == 6) game.moveDisc(game.getC(), game.getB());
    }
    cout << endl;
    game.display();
    cout << "\nGame Over\n\n";
}
