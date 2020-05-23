#include <iostream>
using namespace std;

bool is_prime(int n)
{
    for (int i = 2; i*i <= n; ++i)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main() {
    int n;
    cin >> n;

    if (is_prime(n))
    {
        cout << n << " is a prime number" << endl;
    }
    else
    {
        cout << n << " is not a prime number" << endl;
    }
    return 0;
}
