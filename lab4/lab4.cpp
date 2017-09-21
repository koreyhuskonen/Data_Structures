#include <iostream>

using namespace std;

#define MAX_ITEMS 1000

template <class type> class orderedList {
protected:
    type *items[MAX_ITEMS];
    int length, ops; // ops = operations counter
public:
    orderedList() : length(0), ops(0), items() {}
    virtual void addItem(type n){
        if(length == MAX_ITEMS) throw "List is full";
        type *temp, *new_item = new type;
        *new_item = n;
        for(int i = 0; i <= length; i++, ops += 2){
            if(!items[i] || *items[i] > n){
                temp = items[i];
                items[i] = new_item;
                new_item = temp;
                ops += 3;
            }
        }
        length++;
    }
    virtual void removeItem(type n){
        if(length == 0) throw "List is empty";
        for(int i = 0; i < length - 1; i++, ops += 2){
            if(*items[i] == n){
                *items[i] = n = *items[i+1];
                ops++;
            }
        }
        ops++;
        if(*items[length-1] == n){
            delete items[length-1];
            items[length-1] = NULL;
            length--;
        } else {
            throw "Item not in list";
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
    type getItem(int index){return *items[index];}
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
        if(length == MAX_ITEMS) throw "List is full";
        int *new_item = new int, i;
        *new_item = n;
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
        int prev = 0, next = 0, *new_item = new int, empty_index = MAX_ITEMS;
        *new_item = n;
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
        int index = (next - prev) / 2 + prev; ops++;
        if(items[index]){
            int i = index, *temp1 = items[i], *temp2;
            ops++;
            if(empty_index < index){
                while(temp1){
                    temp2 = items[i-1];
                    items[i-1] = temp1;
                    temp1 = temp2;
                    i--; ops += 3;
                }
            } else {
                if(*items[i] < n) index++; ops++;
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
        for(int i = 0; i < MAX_ITEMS; i++, ops += 2){
            if(items[i] && *items[i] == n){
                delete items[i];
                items[i] = NULL;
                length--;
                return;
            }
        }
        throw "Item is not in list";
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
//         test.displayList();
//     }
// }
