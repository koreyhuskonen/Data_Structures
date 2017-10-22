#include <iostream>

using namespace std;

#define MAX 1000

class Stack {
    int top;
    int a[MAX];
public:
    Stack() : top(-1) {}
    bool push(int n){
        if(top >= MAX) return false;
        a[++top] = n;
        return true;
    }
    int pop(){
        if(top < 0) return top;
        return a[top--];
    }
    void display(){
        for(int i = 0; i <= top; i++){
            cout << i << ": " << a[top-i] << endl;
        }
    }
};

int main(){
    Stack test;
    test.push(5);
    test.push(52);
    test.push(78);
    test.push(2);

    cout << test.pop() << endl;
    cout << test.pop() << endl;
    cout << test.pop() << endl;
    cout << test.pop() << endl;



}
