#include <iostream>
#include <string>
using namespace std;

void Combinations(int arr[], int n, int l, int r){
    if(l==r){
        for(int i=0;i<n;i++){
            cout<<arr[i]<<",";
        }
        cout<<" ";
    }
    else{
        for(int i=l;i<=r;i++){
            int temp = arr[l];
            arr[l] = arr[i];
            arr[i] = temp;
            Combinations(arr,n,l+1,r);
            temp = arr[l];
            arr[l] = arr[i];
            arr[i] = temp;
        }
    }
}

int main(int argc, char const *argv[])
{
    int N;
    cout<<"Enter the value of N: ";
    cin>>N;
    int arr[N];
    for(int i=0;i<N;i++){
        arr[i] = (i+1);
    }
    cout<<"The combinations are:\n";
    Combinations(arr,N,0,N-1);
    cout<<"\n";
    return 0;
}
