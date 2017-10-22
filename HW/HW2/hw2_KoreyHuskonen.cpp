#include <iostream>
#include <chrono>
#include <iomanip>
#include "sorting.cpp"

using namespace std;
typedef chrono::high_resolution_clock Clock;

int main(){
    int num_algos = 5, num_tests = 3, test_sizes[] = {10, 100, 500};
    int* test[num_algos][num_tests];
    // *test* will store all the test cases indexed by algorithm and then by case number
    // We must intialize each test case to the proper size, stored in the *test_sizes* array
    for(int i = 0; i < num_algos; i++){
        for(int j = 0; j < num_tests; j++){
            test[i][j] = new int[test_sizes[j]];
        }
    }
    // Populate each test case
    srand(time(0));
    for(int i = 0; i < num_tests; i++){              // Select each test case
        for(int j = 0; j < test_sizes[i]; j++){      // Fill test case
            int temp = rand() % (2*test_sizes[i]+1); // Fill with integers from 0 to 2n, where n is the size contained in *test_sizes*
            for(int k = 0; k < num_algos; k++){      // Use the same integer for each algorithm (the first index of *test*)
                test[k][i][j] = temp;
            }
        }
    }
    // Display table header
    int w = 15; // *w* = width of each table column
    cout << setw(w) << "";
    for(int i = 0; i < num_tests; i++){
        cout << left << setw(w) << test_sizes[i];
    }
    cout << endl;

    int num_trials = 10;

    cout << left << setw(w) << "Bubble";
    for(int )
    for(int i = 0; i < num_tests; i++){
        auto t1 = Clock::now();
        bubble(test[0][i], test_sizes[i]);
        auto t2 = Clock::now();
        cout << left << setw(w) << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
    }
    cout << endl;

    cout << left << setw(w) << "Insertion";
    for(int i = 0; i < num_tests; i++){
        auto t1 = Clock::now();
        insertion(test[1][i], test_sizes[i]);
        auto t2 = Clock::now();
        cout << left << setw(w) << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
    }
    cout << endl;

    cout << left << setw(w) << "Selection";
    for(int i = 0; i < num_tests; i++){
        auto t1 = Clock::now();
        selection(test[2][i], test_sizes[i]);
        auto t2 = Clock::now();
        cout << left << setw(w) << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
    }
    cout << endl;

    cout << left << setw(w) << "Merge";
    for(int i = 0; i < num_tests; i++){
        auto t1 = Clock::now();
        mergeSort(test[3][i], 0, test_sizes[i]-1);
        auto t2 = Clock::now();
        cout << left << setw(w) << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
    }
    cout << endl;

    cout << left << setw(w) << "Quick";
    for(int i = 0; i < num_tests; i++){
        auto t1 = Clock::now();
        quickSort(test[4][i], 0, test_sizes[i]-1);
        auto t2 = Clock::now();
        cout << left << setw(w) << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
    }
    cout << endl;






    for(int i = 0; i < num_algos; i++){
        for(int j = 0; j < num_tests; j++){
            delete [] test[i][j];
        }
    }
}
