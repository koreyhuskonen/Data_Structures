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
         << endl;

    int num_algos = 6, num_trials = 10, sizes[5] = {10,100,500,5000,25000};
    unsigned long long bubble_sum, insertion_sum, selection_sum, merge_sum, quick_sum,
                       count_sum;
    for(int x = 0; x < 5; x++){
        int size = sizes[x];
        bubble_sum = insertion_sum = selection_sum = merge_sum = quick_sum = count_sum = 0;
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
             << endl;

    }










    // int num_algos = 5, num_tests = 3, test_sizes[] = {10, 100, 500};
    // int* test[num_algos][num_tests];
    // // *test* will store all the test cases indexed by algorithm and then by case number
    // // We must intialize each test case to the proper size, stored in the *test_sizes* array
    // for(int i = 0; i < num_algos; i++){
    //     for(int j = 0; j < num_tests; j++){
    //         test[i][j] = new int[test_sizes[j]];
    //     }
    // }
    // // Populate each test case
    // srand(time(0));
    // for(int i = 0; i < num_tests; i++){              // Select each test case
    //     for(int j = 0; j < test_sizes[i]; j++){      // Fill test case
    //         int temp = rand() % (2*test_sizes[i]+1); // Fill with integers from 0 to 2n, where n is the size contained in *test_sizes*
    //         for(int k = 0; k < num_algos; k++){      // Use the same integer for each algorithm (the first index of *test*)
    //             test[k][i][j] = temp;
    //         }
    //     }
    // }
    // // Display table header
    // int w = 15; // *w* = width of each table column
    // cout << setw(w) << "";
    // for(int i = 0; i < num_tests; i++){
    //     cout << left << setw(w) << test_sizes[i];
    // }
    // cout << endl;
    //
    // int num_trials = 10;
    //
    // cout << left << setw(w) << "Bubble";
    // for(int )
    // for(int i = 0; i < num_tests; i++){
    //     auto t1 = Clock::now();
    //     bubble(test[0][i], test_sizes[i]);
    //     auto t2 = Clock::now();
    //     cout << left << setw(w) << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
    // }
    // cout << endl;
    //
    // cout << left << setw(w) << "Insertion";
    // for(int i = 0; i < num_tests; i++){
    //     auto t1 = Clock::now();
    //     insertion(test[1][i], test_sizes[i]);
    //     auto t2 = Clock::now();
    //     cout << left << setw(w) << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
    // }
    // cout << endl;
    //
    // cout << left << setw(w) << "Selection";
    // for(int i = 0; i < num_tests; i++){
    //     auto t1 = Clock::now();
    //     selection(test[2][i], test_sizes[i]);
    //     auto t2 = Clock::now();
    //     cout << left << setw(w) << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
    // }
    // cout << endl;
    //
    // cout << left << setw(w) << "Merge";
    // for(int i = 0; i < num_tests; i++){
    //     auto t1 = Clock::now();
    //     mergeSort(test[3][i], 0, test_sizes[i]-1);
    //     auto t2 = Clock::now();
    //     cout << left << setw(w) << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
    // }
    // cout << endl;
    //
    // cout << left << setw(w) << "Quick";
    // for(int i = 0; i < num_tests; i++){
    //     auto t1 = Clock::now();
    //     quickSort(test[4][i], 0, test_sizes[i]-1);
    //     auto t2 = Clock::now();
    //     cout << left << setw(w) << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
    // }
    // cout << endl;
    // for(int i = 0; i < num_algos; i++){
    //     for(int j = 0; j < num_tests; j++){
    //         delete [] test[i][j];
    //     }
    // }
}
