#include <iostream>
using namespace std;

int n;

void Count_Sort(int arr[], int index){
    int aux_arr[n];
    int count[10];
    for(int i=0;i<10;i++){
        count[i] = 0;
    }
    for(int i=0;i<n;i++){
        int temp = (arr[i]/index)%10;
        count[temp] = count[temp]+1;
    }
    for(int i=1;i<10;i++){
        count[i] += count[i-1];
    }
    for(int i = n-1;i>=0;i--){
        int temp = (arr[i]/index)%10;
        temp = temp - 1;
        int temp2 = count[temp];
        aux_arr[temp2] = arr[i];
        count[temp] = count[temp] - 1;
    }
    for(int i=0;i<n;i++){
        arr[i] = aux_arr[i];
    }
}

int main(int argc, char const *argv[])
{
    cout<<"Enter the number of elements in the array: ";
    cin>>n;
    int arr[n];
    cout<<"Enter the elements of the array\n";
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    int maxe = arr[0];
    for(int i=1;i<n;i++){
        if(maxe<arr[i]){
            maxe = arr[i];
        }
    }
    int digits = 0;
    while(maxe){
        digits++;
        maxe = maxe/10;
    }
    int exp = 1;
    for(int i=1;i<=digits;i++){
        Count_Sort(arr,exp);
        exp = exp*10;
    }
    cout<<"The sorted array after applying Radix Sort is:\n";
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<"\n";
    return 0;
}
