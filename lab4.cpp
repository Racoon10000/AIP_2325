#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    const int SIZE = 256;
    int arr[SIZE];

    srand(time(nullptr));

    for (int i = 0; i < SIZE; ++i) {
        arr[i] = rand() % 1000 + 1;
    }

    for (int i = 0; i < SIZE; ++i) {
        if (i % 4 == 0) {
            cout << setw(10) << dec << arr[i];  
        }
        else if (i % 4 == 1) {
            cout << setw(10) << hex << arr[i];  
        }
        else if (i % 4 == 2) {
            cout << setw(10) << oct << arr[i];  
        }
        else {
            cout << setw(10) << dec << arr[i];  
        }
        if ((i + 1) % 4 == 0) {
            cout << endl;  
        }
    }

    return 0;
}
