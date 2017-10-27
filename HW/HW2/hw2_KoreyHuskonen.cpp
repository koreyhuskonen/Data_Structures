#include <iostream>
#include <chrono>
#include <iomanip>
#include "sorting.cpp"

using namespace std;
typedef chrono::high_resolution_clock Clock;

int main(){
    srand(time(0));
    int w = 15;
    cout << endl
         << left << setw(10) << "n"
         << left << setw(w) << "Bubble"
         << left << setw(w) << "Insertion"
         << left << setw(w) << "Selection"
         << left << setw(w) << "Merge"
         << left << setw(w) << "Quick"
         << left << setw(w) << "Count"
         << left << setw(w) << "Radix"
         << left << setw(w) << "Heap"
         << endl;

    int num_algos = 8, num_trials = 10, sizes[5] = {10,100,500,5000,25000};
    unsigned long long bubble_sum, insertion_sum, selection_sum, merge_sum, quick_sum,
                       count_sum, radix_sum, heap_sum;
    for(int x = 0; x < 5; x++){
        int size = sizes[x];
        bubble_sum = insertion_sum = selection_sum = merge_sum = quick_sum = count_sum = radix_sum = heap_sum = 0;
        for(int j = 0; j < num_trials; j++){
            int test[num_algos][size];
            for(int i = 0; i < size; i++){
                int temp = rand() % (2*size+1);
                for(int k = 0; k < num_algos; k++){
                    test[k][i] = temp;
                }
            }

            // for(int j = 0; j < num_algos; j++){
            //     for(int i = 0; i < size; i++){
            //         cout << test[j][i] << endl;
            //     }
            //     cout << "________" << endl;
            // }

            auto t1 = Clock::now();
            bubble(test[0], size);
            auto t2 = Clock::now();
            bubble_sum += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();

            t1 = Clock::now();
            insertion(test[1], size);
            t2 = Clock::now();
            insertion_sum += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();

            t1 = Clock::now();
            selection(test[2], size);
            t2 = Clock::now();
            selection_sum += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();

            t1 = Clock::now();
            mergeSort(test[3], 0, size-1);
            t2 = Clock::now();
            merge_sum += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();

            t1 = Clock::now();
            quickSort(test[4], 0, size-1);
            t2 = Clock::now();
            quick_sum += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();

            t1 = Clock::now();
            countSort(test[5], size);
            t2 = Clock::now();
            count_sum += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();

            t1 = Clock::now();
            radix(test[6], size);
            t2 = Clock::now();
            radix_sum += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();

            t1 = Clock::now();
            heapSort(test[7], size);
            t2 = Clock::now();
            heap_sum += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();

            // for(int j = 0; j < num_algos; j++){
            //     for(int i = 0; i < size; i++){
            //         cout << test[j][i] << endl;
            //     }
            //     cout << "________" << endl;
            // }
        }

        cout << setw(10) << size
             << left << setw(w) << bubble_sum/num_trials
             << left << setw(w) << insertion_sum/num_trials
             << left << setw(w) << selection_sum/num_trials
             << left << setw(w) << merge_sum/num_trials
             << left << setw(w) << quick_sum/num_trials
             << left << setw(w) << count_sum/num_trials
             << left << setw(w) << radix_sum/num_trials
             << left << setw(w) << heap_sum/num_trials
             << endl;

    }

}
