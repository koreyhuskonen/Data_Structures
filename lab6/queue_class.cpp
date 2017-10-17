#include <iostream>
#include <vector>

using namespace std;

template <class T> class Queue {
    vector<T> q;
public:
    void enqueue(T& item){
        q.push_back(item);
    }
    T dequeue(){
        T temp = q[0];
        q.erase(q.begin());
        return temp;
    }
    void display(){
        for(int i = 0; i < q.size(); i++) cout << q[i] << endl;
    }
};

int main(){


}
