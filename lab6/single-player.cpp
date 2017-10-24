#include <iostream>
#include <sstream>
#include <vector>
#include "stack_class.cpp"

using namespace std;

// I just redefined the Queue class here so I could use it with the automated solution
// I didn't want to import the Move struct used for multiplayer mode -- had to make a new Move struct
template <class T> class Queue {
    vector<T*> q;
public:
    void enqueue(T* item){
        q.push_back(item);
    }
    T* dequeue(){
        T* temp = q[0];
        q.erase(q.begin());
        return temp;
    }
    void display(){
        for(int i = 0; i < q.size(); i++) cout << i+1 << ": " << *q[i] << endl;
    }
    ~Queue(){
        for(int i = 0; i < q.size(); i++) delete q[i];
    }
};

struct Move {
    int from, to, disc;
    Move(int from, int to, int disc) : from(from), to(to), disc(disc) {}
};

std::ostream& operator<<(std::ostream& os, const Move& mv){
    os << "Moved " << mv.disc << " from Tower" << mv.from+1 << " to Tower" << mv.to+1;
    return os;
}

const int num_towers = 3;

class Hanoi {
    int num_discs;
    Stack<int>* towers[num_towers];
    Queue<Move> moves;
public:
    Hanoi(int num_discs) : num_discs(num_discs) {
        for(int i = 0; i < num_towers; i++) towers[i] = new Stack<int>(num_discs);
        for(int i = num_discs; i > 0; i--){
            int* temp = new int;
            *temp = i;
            towers[0]->push(temp);
        }
    }
    void moveDisc(int f, int t){
        Stack<int> *from = towers[f], *to = towers[t];
        if(!from->getTop()){
            cout << "Illegal! You cannot move a disc from an empty tower!" << endl;
            return;
        } else if(to->getTop() && *to->getTop() < *from->getTop()){
            cout << "Illegal! You cannot move a bigger disc onto a smaller one!" << endl;
            return;
        }

        Move* current_move = new Move(f, t, *from->getTop());
        moves.enqueue(current_move);
        to->push(from->pop());
    }
    bool gameOver(){return towers[2]->length() == num_discs;}
    void showMoves(){moves.display();}
    void display(){
        for(int i = 0; i < num_towers; i++){
            cout << "Tower" << i+1 << "-> "; displayStack(*towers[i]); cout << endl;
        }
    }
    void automate(int n, int from, int to, int aux){
        if(n == 1){
            moveDisc(from, to);
            return;
        }
        automate(n-1, from, aux, to);
        moveDisc(from, to);
        automate(n-1, aux, to, from);
    }
};

int main(){
    string input; // dummy variable for user input
    int num_discs;

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

    cout << "\nYour mission: Move your discs from Tower1 to Tower3\n\n";

    Hanoi game(num_discs);
    game.display();

    int from, to, turn_count = 0; // *from* and *to* are tower indexes to pop from and push to
    cout << "\nAutomate solution? (y/n) ";
    getline(cin, input);
    if(input == "y" || input == "Y"){
        game.automate(num_discs, 0, 2, 1);
    } else {
        while(!game.gameOver()){
            turn_count++;
            cout << "\n_____ Turn " << turn_count << " _____\n";
            game.display();
            do {
                cout << "Enter the tower to move from (1-" << num_towers << "): ";
                getline(cin, input);
                stringstream(input) >> from;
            } while(from < 1 || from > num_towers);
            do {
                cout << "Enter the tower to move to (1-" << num_towers << "): ";
                getline(cin, input);
                stringstream(input) >> to;
            } while(to < 1 || to > num_towers);
            game.moveDisc(from-1, to-1);
        }
    }
    cout << endl;
    game.display();
    cout << "\nGame Over\n";
    cout << "\n___ Turn History ___\n";
    game.showMoves();
    cout << "\n";
}
