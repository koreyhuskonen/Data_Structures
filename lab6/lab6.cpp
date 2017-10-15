#include <iostream>

using namespace std;

template <class T> class Stack {
    T** arr;
    int top;
public:
    Stack(int size) : arr(new T*[size]), top(-1) {}
    void push(T* new_item){arr[++top] = new_item;}
    T* pop(){return arr[top--];}
    T* getTop(){return arr[top];}
    int length(){return top+1;}
    template <class U> friend void displayStack(Stack<U>& s);
    void empty(){
        for(int i = 0; i <= top; i++) delete arr[i];
        top = -1;
    }
    ~Stack(){
        empty();
        delete [] arr;
    }
};

template <class T>
void displayStack(Stack<T>& s){
    for(int i = 0; i <= s.top; i++){
        std::cout << i << ": " << *s.arr[i] << std::endl;
    }
}



int main(){
    int size = 5;
    srand(time(0));
    Stack<int> test(size);
    for(int i = 0; i < size; i++){
        int* temp = new int;
        *temp = rand() % 100;
        test.push(temp);
    }
    displayStack(test);
}
