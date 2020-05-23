#include <iostream>
#include <climits>
using namespace std;

void merge(int *arr, int i, int m, int j)
{
    int arr1[m-i+1 + 1], arr2[j-m + 1];
    arr1[m-i+1] = arr2[j-m] =  INT_MAX;
    for (int k = 0; k < m-i+1; ++k)
    {
        arr1[k] = arr[i+k];
    }
    for (int k = 0; k < j-m; ++k)
    {
        arr2[k] = arr[m+k+1];
    }
    int p = 0, q = 0;
    for (int k = i; k <= j; ++k)
    {
        if (arr1[p] < arr2[q])
        {
            arr[k] = arr1[p++];
        }
        else
        {
            arr[k] = arr2[q++];
        }
    }
}

void merge_sort(int *arr, int n, int i, int j)
{
    if (i < j)
    {
        int m = i + (j-i)/2;
        merge_sort(arr, n, i, m);
        merge_sort(arr, n, m+1, j);
        merge(arr, i, m, j);
    }
}

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

    merge_sort(arr, n, 0, n-1);
    cout << "After Merge Sort: \n";
    for (int i = 0; i < n; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}
