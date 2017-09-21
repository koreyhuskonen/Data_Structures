// Korey Huskonen - Data Structures Lab 4 - 09/21/2017

#include <iostream>
#include "exceptions.cpp"

using namespace std;

#define MAX_ITEMS 10

template <class type> class orderedList {
protected:
    type *items[MAX_ITEMS];
    int length, ops; // ops = operations counter
public:
    orderedList() : length(0), ops(0), items() {}
    virtual void addItem(type n){
        if(length == MAX_ITEMS) throw ListIsFull();
        type *temp, *new_item = new type;
        *new_item = n;
        for(int i = 0; i <= length; i++, ops += 2){
            // find first empty index
            // or index where we need to start shifting items up to make room for the new item
            if(!items[i] || *items[i] > n){
                // shift items up until we reach the end of the list
                temp = items[i];
                items[i] = new_item;
                new_item = temp;
                ops += 3;
            }
        }
        length++;
    }
    virtual void removeItem(type n){
        if(length == 0) throw ListIsEmpty();
        for(int i = 0; i < length - 1; i++, ops += 2){
            // start from back, if we find n, shift all items after it down one
            if(*items[i] == n){
                *items[i] = n = *items[i+1];
                ops++;
            }
        }
        ops++;
        if(*items[length-1] == n){
            delete items[length-1]; // delete the pointer we no longer need at the end
            items[length-1] = NULL;
            length--;
        } else {
            throw ItemNotInList();
        }
    }
    virtual void displayList(){
        for(int i = 0; i < length; i++){
            cout << i << ": " << *items[i] << endl;
        }
    }
    bool isEmpty(){return length == 0;}
    bool isFull(){return length == MAX_ITEMS;}
    void makeEmpty(){
        for(int i = 0; i < length; i++){
            delete items[i];
            items[i] = NULL;
        }
        length = 0;
    }
    type getItem(int index){
        if(items[index]){
            return *items[index];
        } else {
            throw ItemNotInList();
        }
    }
    int getLenth(){return length;}
    int getOps(){return ops;}
    bool operator<(const orderedList &ol){
        return length < ol.length;
    }
    bool operator>(const orderedList &ol){
        return length > ol.length;
    }
    bool operator==(orderedList &ol){
        if(length != ol.length) return false;
        for(int i = 0; i < length; i++){
            if(*items[i] != ol.getItem(i)) return false;
        }
        return true;
    }
    ~orderedList(){
        for(int i = 0; i < MAX_ITEMS; i++) delete items[i];
    }
};

class startFromEnd : public orderedList<int> {
public:
    void addItem(int n){
        if(length == MAX_ITEMS) throw ListIsFull();
        int *new_item = new int, i;
        *new_item = n;
        // start from end, keep shifting items up until we find the index where we need to insert n
        for(i = length; i > 0; i--, ops += 2){
            if(*items[i-1] > n){
                items[i] = items[i-1];
                ops++;
            } else {
                break;
            }
        }
        items[i] = new_item; ops++;
        length++;
    }
};

class insertHalfway : public orderedList<int> {
public:
    void addItem(int n){
        if(length == MAX_ITEMS) throw ListIsFull();
        int prev = 0, next = 0, *new_item = new int, empty_index = MAX_ITEMS;
        *new_item = n;
        // find indexes of upper and lower bounds (prev and next)
        for(int i = 0; i < MAX_ITEMS; i++, ops++){
            if(items[i] && *items[i] >= n){
                next = i; ops += 2;
                break;
            } else if(items[i] && *items[i] < n){
                prev = i; ops += 3;
            } else {
                next = empty_index = i; ops += 3;
            }
        }
        // calculate index of new item halfway between prev and next
        int index = (next - prev) / 2 + prev; ops++;
        // check if there's already a value there
        if(items[index]){
            int i = index, *temp1 = items[i], *temp2;
            ops++;
            if(empty_index < index){
                // we have empty spaces toward the front of the list, so shift items down
                while(temp1){
                    temp2 = items[i-1];
                    items[i-1] = temp1;
                    temp1 = temp2;
                    i--; ops += 3;
                }
            } else {
                // increment index if the current item is less to keep list in order
                if(*items[i] < n) index++; ops++;
                // shift items up
                while(temp1){
                    temp2 = items[i+1];
                    items[i+1] = temp1;
                    temp1 = temp2;
                    i++; ops += 3;
                }
            }
        }
        items[index] = new_item; ops++;
        length++;
    }
    void removeItem(int n){
        if(length == 0) throw ListIsEmpty();
        for(int i = 0; i < MAX_ITEMS; i++, ops += 2){
            if(items[i] && *items[i] == n){
                delete items[i];
                items[i] = NULL;
                length--;
                return;
            }
        }
        throw ItemNotInList();
    }
    void displayList(){
        for(int i = 0; i < MAX_ITEMS; i++){
            if(items[i]){
                cout << i << ": " << *items[i] << endl;
            } else {
                cout << i << ": " << "NULL" << endl;
            }
        }
    }
};

// int main(){
//     srand(time(NULL));
//     int temp;
//     startFromEnd test;
//     for(int i = 0; i < MAX_ITEMS; i++){
//         temp = rand() % 100;
//         cout << "_____ Adding " << temp << " _____" << endl;
//         test.addItem(temp);
//     }
// }
