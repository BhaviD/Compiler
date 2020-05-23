#include <iostream>
using namespace std;

int main ()
{
    int A_m, A_n;
    cout << "Enter dimensions of matrix A: ";
    cin >> A_m >> A_n;
    int A[A_m][A_n];
    cout << "Enter values of matrix A:" << endl;
    for (int i = 0; i < A_m; ++i)
    {
        for (int j = 0; j < A_n; ++j)
        {
            cin >> A[i][j];
        }
    }

    int B_m, B_n;
    cout << endl;
    cout << "Enter dimensions of matrix B: ";
    cin >> B_m >> B_n;
    int B[B_m][B_n];
    cout << "Enter values of matrix B:" << endl;
    for (int i = 0; i < B_m; ++i)
    {
        for (int j = 0; j < B_n; ++j)
        {
            cin >> B[i][j];
        }
    }

    if (A_n != B_m)
    {
        cout << "The matrices are not compatible for multiplication!!\n";
        return 1;
    }

    int C[A_m][B_n];
    for (int i = 0; i < A_m; ++i)
    {
        for (int j = 0; j < B_n; ++j)
        {
            C[i][j] = 0;
            for (int k = 0; k < A_n; ++k)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    cout << endl;
    cout << "A x B: " << endl;
    for (int i = 0; i < A_m; ++i)
    {
        for (int j = 0; j < B_n; ++j)
        {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
