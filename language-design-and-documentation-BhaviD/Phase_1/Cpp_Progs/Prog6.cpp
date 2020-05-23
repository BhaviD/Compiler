#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter the size of array: ";
    cin >> n;

    int arr[n];
    cout << "Enter the values:\n";
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    for (int j = 1; j < n; ++j)
    {
        for (int i = j-1; i >= 0 && arr[i] > arr[i+1]; --i)
        {
            swap(arr[i], arr[i+1]);
        }
    }
    cout << "After Insertion Sort: \n";
    for (int i = 0; i < n; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}
