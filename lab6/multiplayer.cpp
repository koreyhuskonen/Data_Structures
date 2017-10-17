#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include "stack_class.cpp"

using namespace std;

const int num_towers = 5;
const char players[2] = {'L', 'R'};

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
    void moveDisc(char player, Stack<string>* from, Stack<string>* to){
        if(!from->getTop()){
            cout << "Illegal! You cannot move a disc from an empty tower!" << endl;
            return;
        }
        string disc = *from->getTop();
        if(disc[0] != player){
            cout << "Illegal! The disc on top of this tower belongs to the other player!" << endl;
            return;
        }
        if(to->getTop() && *to->getTop() < *from->getTop()){
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
    bool checkTower(Stack<string>* tower, char player){ // checks if we got a winning tower
        if(tower->length() != num_discs) return false;
        bool result = true;
        Stack<string> temp_tower(num_discs); // create a temporary tower to hold discs
        for(int i = 0; i < num_discs; i++){
            string disc = *tower->getTop();
            if(disc[0] != player){ // check if disc is owned by player
                result = false;
                break;
            }
            temp_tower.push(tower->pop()); // pop from tower and store in temp_tower
        }
        for(int i = 0; i < temp_tower.length(); i++) tower->push(temp_tower.pop()); // put the discs back on original tower
        return result;
    }
    bool gameOver(){
        for(int i = 0; i < 2; i++){
            if(checkTower(towers[i], players[1])) return true;
        }
        for(int i = num_towers-2; i < num_towers; i++){
            if(checkTower(towers[i], players[0])) return true;
        }
        return false;
    }
    ~Hanoi(){
        for(int i = 0; i < num_towers; i++) delete towers[i];
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
    cout << "Your mission:\nGet all your discs to the other side\n";
    game.display();
    game.gameOver();
    game.display();

}
