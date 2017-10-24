#include <iostream>

using namespace std;

void swap(int* arr, int a, int b){
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void bubble(int* arr, int size){
    bool swapped;
    do {
        swapped = false;
        for(int i = 1; i < size; i++){
            if(arr[i-1] > arr[i]){
                swap(arr, i, i-1);
                swapped = true;
            }
        }
        size--;
    } while(swapped);
}

void bubble2(int* arr, int size){
    bool swapped;
    for(int i = 1; i < size; i++){
        swapped = false;
        for(int j = 1; j <= size - i; j++){
            if(arr[j-1] > arr[j]){
                swap(arr, j, j-1);
                swapped = true;
            }
        }
        if(!swapped) break;
    }
}

void insertion(int* arr, int size){
    int i, key, j;
    for(i = 1; i < size; i++){
        key = arr[i];
        j = i - 1;
        while(j >= 0 && arr[j] > key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void selection(int* arr, int size){
    int i, min, j;
    for(i = 0; i < size-1; i++){
        min = i;
        for(j = i+1; j < size; j++){
            if(arr[j] < arr[min]) min = j;
        }
        swap(arr, i, min);
    }
}

void merge(int* arr, int l, int m, int h){
    int n1 = m-l+1;
    int n2 = h-m;
    int L[n1], R[n2];
    for(int i = 0; i < n1; i++) L[i] = arr[l+i];
    for(int i = 0; i < n2; i++) R[i] = arr[m+i+1];
    int j = l;
    int i = 0, k = 0;
    while(i < n1 && k < n2){
        if(L[i] < R[k]){
            arr[j] = L[i];
            i++;
        } else {
            arr[j] = R[k];
            k++;
        }
        j++;
    }
    while(i < n1){
        arr[j] = L[i];
        i++;
        j++;
    }
    while(k < n2){
        arr[j] = R[k];
        k++;
        j++;
    }
}

void mergeSort(int* arr, int l, int h){
    if(l < h){
        int m = l+(h-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, h);
        merge(arr, l, m, h);
    }
}

int partition(int* arr, int low, int high){
    int pivot = arr[high];
    int j = low-1;
    for(int i = low; i <= high; i++){
        if(arr[i] <= pivot){
            j++;
            swap(arr, i, j);
        }
    }
    return j;
}

void quickSort(int* arr, int low, int high){
    if(low < high){
        int p = partition(arr, low, high);
        quickSort(arr, low, p-1);
        quickSort(arr, p+1, high);
    }
}

void countSort(int* arr, int size){
    int range = *max_element(arr, arr+size) + 1; // +1 to include last index
    int c[range], output[size];
    memset(c, 0, sizeof(c));
    for(int i = 0; i < size; i++){
        c[arr[i]]++;
    }
    for(int i = 1; i < range; i++){
        c[i] += c[i-1];
    }
    for(int i = 0; i < size; i++){
        output[c[arr[i]]-1] = arr[i];
        c[arr[i]]--;
    }
    for(int i = 0; i < size; i++){
        arr[i] = output[i];
    }
}

// int main(){
//     struct timespec start, finish;
//     double elapsed;
//     srand(time(NULL));
//     int size = 15, num_tests = 6, test_input[num_tests][size], temp;
//     for(int j = 0; j < size; j++){
//         temp = rand() % 100;
//         for(int i = 0; i < num_tests; i++){
//             test_input[i][j] = temp;
//         }
//     }
//
//     cout << "\n_____ Unsorted _____" << endl;
//     for(int i = 0; i < size; i++) cout << test_input[0][i] << endl;
//
// //     cout << "\nBubble" << endl;
// //     clock_gettime(CLOCK_MONOTONIC, &start);
// //     bubble(test_input[0], size);
// //     clock_gettime(CLOCK_MONOTONIC, &finish);
// //     elapsed = (finish.tv_sec - start.tv_sec);
// //     elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
// //     // for(int i = 0; i < size; i++) cout << test_input[0][i] << endl;
// //     cout << "Time: " << elapsed << endl;
// //
// //     cout << "\nInsertion" << endl;
// //     clock_gettime(CLOCK_MONOTONIC, &start);
// //     insertion2(test_input[1], size);
// //     clock_gettime(CLOCK_MONOTONIC, &finish);
// //     elapsed = (finish.tv_sec - start.tv_sec);
// //     elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
// //     // for(int i = 0; i < size; i++) cout << test_input[1][i] << endl;
// //     cout << "Time: " << elapsed << endl;
// //
// //     cout << "\nSelection" << endl;
// //     clock_gettime(CLOCK_MONOTONIC, &start);
// //     selection(test_input[2], size);
// //     clock_gettime(CLOCK_MONOTONIC, &finish);
// //     elapsed = (finish.tv_sec - start.tv_sec);
// //     elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
// //     // for(int i = 0; i < size; i++) cout << test_input[2][i] << endl;
// //     cout << "Time: " << elapsed << endl;
// //
// //     cout << "\nMerge" << endl;
// //     clock_gettime(CLOCK_MONOTONIC, &start);
// //     mergeSort(test_input[3], 0, size-1);
// //     clock_gettime(CLOCK_MONOTONIC, &finish);
// //     elapsed = (finish.tv_sec - start.tv_sec);
// //     elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
// //     // for(int i = 0; i < size; i++) cout << test_input[3][i] << endl;
// //     cout << "Time: " << elapsed << endl;
// //
// //     cout << "\nQuick" << endl;
// //     clock_gettime(CLOCK_MONOTONIC, &start);
// //     quickSort(test_input[4], 0, size-1);
// //     clock_gettime(CLOCK_MONOTONIC, &finish);
// //     elapsed = (finish.tv_sec - start.tv_sec);
// //     elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
// //     // for(int i = 0; i < size; i++) cout << test_input[4][i] << endl;
// //     cout << "Time: " << elapsed << endl;
//     //
//     // cout << "\nCount" << endl;
//     // clock_gettime(CLOCK_MONOTONIC, &start);
//     // countSort(test_input[5], size);
//     // clock_gettime(CLOCK_MONOTONIC, &finish);
//     // elapsed = (finish.tv_sec - start.tv_sec);
//     // elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
//     // // for(int i = 0; i < size; i++) cout << test_input[5][i] << endl;
//     // cout << "Time: " << elapsed << endl;
// }
