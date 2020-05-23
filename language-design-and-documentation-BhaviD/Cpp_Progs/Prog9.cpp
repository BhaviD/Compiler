#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    int m,n;
    cout<<"Enter the number of rows of the matrices: ";
    cin>>m;
    cout<<"Enter the number of columns of the matrices: ";
    cin>>n;
    int mat1[m][n];
    int mat2[m][n];
    cout<<"Enter the elements of the first matrix:\n";
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cin>>mat1[i][j];
        }
    }
    cout<<"Enter the elements of the second matrix:\n";
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cin>>mat2[i][j];
        }
    }
    int sum_mat[m][n];
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            sum_mat[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
    cout<<"The sum of the two matrices is:\n";
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cout<<sum_mat[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
    return 0;
}
