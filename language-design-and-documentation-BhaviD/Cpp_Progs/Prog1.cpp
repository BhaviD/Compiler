#include<iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int N, k, sum = 0;
    cout<<"Enter the value of N: ";
    cin>>N;
    cout<<"Enter the value of k: ";
    cin>>k;
    for(int i=1;i<=N;i++){
        int temp = i;
        for(int j=2;j<=k;j++){
            temp = temp * i;
        }
        sum = sum + temp;
    }
    cout<<"The value of the expression = "<<sum<<"\n";
    return 0;
}

