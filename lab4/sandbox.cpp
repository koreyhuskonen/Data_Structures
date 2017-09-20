#include <iostream>

using namespace std;

#define MAX_ITEMS 20

class myList {
    int *items[MAX_ITEMS], length;
public:
    myList() : length(0), items() {}
    void addItem(int n){
        int i = 0, *new_item = new int; // allocate memory for new item
        *new_item = n;                  // set value of new item to n
        while(items[i]) i++; // find empty index
        items[i] = new_item; // set value of item at index i equal to n
        length++;
    }
    void displayList(){
        for(int i = 0; i < length; i++){
            cout << i << ": " << *items[i] << endl;
        }
    }
};

int main(){
    // myList test;
    // test.addItem(55);
    // test.displayList();
    // test.displayList();
    // int *myptr[5];
    // myptr[0] = NULL;
    // cout << myptr[0] << endl;
    // int bob = 5, cat = 9;
    // myptr[0] = &bob;
    // cout << *myptr[0] << endl;
    // *myptr[0] = cat;
    // cout << *myptr[0] << endl;

    int *myarray[8];
    for(int i = 0; i < 8; i++){
        cout << *(myarray+i) << endl;
    }
    *myarray[7] = 88;

}
