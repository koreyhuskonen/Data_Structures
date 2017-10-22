#include <iostream>

using namespace std;

int main(){
    int num_algos = 3, num_tests = 3, test_sizes[] = {10, 15, 20};
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




}
