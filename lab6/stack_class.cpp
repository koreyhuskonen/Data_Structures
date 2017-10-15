#include <iostream>
#include <exception>

struct StackOverflow : public std::exception {
   const char * what () const throw () {
      return "Stack Overflow";
   }
};

struct StackUnderflow : public std::exception {
   const char * what () const throw () {
      return "Stack Underflow";
   }
};

template <class T> class Stack {
    T** arr;
    int top, size;
public:
    Stack(int size) : arr(new T*[size]), top(-1), size(size) {}
    void push(T* new_item){
        if(top == size-1) throw StackOverflow();
        arr[++top] = new_item;
    }
    T* pop(){
        if(top == -1) throw StackUnderflow();
        return arr[top--];
    }
    T* getTop(){
        if(top == -1) return NULL;
        return arr[top];
    }
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
        std::cout << " " << *s.arr[i];
    }
}

// int main(){
//     int size = 5;
//     srand(time(0));
//     Stack<int> test(size);
//     for(int i = 0; i < size; i++){
//         int* temp = new int;
//         *temp = rand() % 100;
//         test.push(temp);
//     }
//     displayStack(test);
//     for(int i = 0; i < size; i++){
//         int* temp = test.pop();
//         std::cout << " " << *temp;
//     }
// }
