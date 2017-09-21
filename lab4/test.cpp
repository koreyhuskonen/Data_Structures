#include <iostream>
#include "lab4.cpp"

using namespace std;

const int items_to_be_removed = 10, trials = 100;

int main(){
    srand(time(NULL));
    int temp, avg1 = 0, avg2 = 0, avg3 = 0;
    for(int x = 0; x < trials; x++){
        orderedList<int> list1;
        startFromEnd     list2;
        insertHalfway    list3;
        for(int i = 0; i < MAX_ITEMS; i++){ // MAX_ITEMS defined in lab4.cpp
            temp = rand() % MAX_ITEMS;
            list1.addItem(temp);
            list2.addItem(temp);
            list3.addItem(temp);
        }

        for(int i = 0; i < items_to_be_removed; i++){
            temp = rand() % list1.getLenth(); // get random index
            temp = list1.getItem(temp); // get item at random index
            list1.removeItem(temp);
            list2.removeItem(temp);
            list3.removeItem(temp);
        }

        avg1 += list1.getOps(); // get number of operations required (ops)
        avg2 += list2.getOps();
        avg3 += list3.getOps();
    }
    cout << endl
         << "Added: " << MAX_ITEMS << "  Deleted: " << items_to_be_removed << "  Trials: " << trials << endl
         << "Version 1 (starting from front) required on average " << avg1/trials << " operations" << endl
         << "Version 2 (starting from back) required on average " << avg2/trials << " operations" << endl
         << "Version 3 (leaving space between) required on average " << avg3/trials << " operations" << endl
         << endl;

}
