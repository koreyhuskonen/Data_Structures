#include <iostream>
#include <vector>

using namespace std;

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
    char player;
    int from, to;
    string disc;
    Move(char player, int from, int to, string disc) : player(player), from(from), to(to), disc(disc) {}
};

std::ostream& operator<<(std::ostream& os, const Move& mv){
    os << "Player " << mv.player << " moved " << mv.disc << " from " << mv.from << " to " << mv.to;
    return os;
}

// int main(){
//     Move test('R',3,2,"R4");
//     cout << test << endl;
// }
