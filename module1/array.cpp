#include <iostream>
using namespace std;

int searchArray(int* arr, int size, int value);

int main() {
    int Pains[] = { 69, 35, 65, 67, 8, 14, 27, 72, 64, 99 };
    int size = sizeof(Pains) / sizeof(Pains[0]);

    cout << "Array size: " << size << endl;

    int value;
    cout << "Enter value to search: ";
    cin >> value;

    int index = searchArray(Pains, size, value);

    if (index != -1)
        cout << "Value " << value << " found at index " << index << endl;
    else
        cout << "Value " << value << " not found in the array." << endl;

    return 0;
}

int searchArray(int* arr, int size, int value) {
    for (int i = 0; i < size; i++) {
        if (*(arr + i) == value) {
            return i;
        }
    }
    return -1;
}
