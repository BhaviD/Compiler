#include <iostream>
using namespace std;

int main() {
    unsigned long long a, b, c, m, n;

    for (int d = 1; d < 100000000/2; ++d) {
        for (unsigned long long n = 1; n < 100000000/2; ++n) {
            m = n+d;
            c = m*m + n*n;
            if (c > 100000000)
                break;
            a = m*m - n*n;
            b = 2*m*n;
            cout << "(" << a << ", " << b << ", " << c << ")" << endl;
        }
    }
    return 0;
}
