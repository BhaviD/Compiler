#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    int N;
    cout<<"Enter the value of N: ";
    cin>>N;
    bool parr[N];
    parr[0] = false;
    parr[1] = false;
    for(int i=2;i<N;i++){
        parr[i] = true;
    }
    for(int i=2;i<N;i++){
        if(parr[i]==true){
            for(int j=2*i;j<N;j+=i){
                parr[j] = false;
            }
        }
    }
    int sum = 0;
    for(int i=2;i<N;i++){
        if(parr[i]==true){
            sum += i;
        }
    }
    cout<<"The sum of all primes strictly less than N = "<<sum<<"\n";
    return 0;
}
