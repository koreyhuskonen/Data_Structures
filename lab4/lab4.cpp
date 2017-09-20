#include <iostream>

using namespace std;

#define MAX_ITEMS 20

class myList {
    int *items[MAX_ITEMS], length;
public:
    myList() : length(0) {
        cout << "______________" << endl;
        for(int i = 0; i < 20; i++){
            cout << *(items+i) << endl;
        }
        cout << "______________" << endl;
    }
    void addItem(int n){
        cout << items[length] << endl;
        *items[length] = n; // length = first empty index
        length++;
        cout << length << endl;

    }
    void removeItem(int n){
        int j = 0;
        for(int i = 0; i < length; i++){
            if(*items[i] != n){
                items[j] = items[i];
                j++;
            }
        }
        length--;
    }
    void displayList(){
        for(int i = 0; i < length; i++){
            cout << i << ": " << *items[i] << endl;
        }
        cout << "Length: " << length << endl;
    }
};

int main(){
    myList test;
    test.addItem(55);
    test.addItem(55);
    test.addItem(55);
    test.addItem(55);
    test.addItem(55);
}
