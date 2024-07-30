#include <iostream>

using namespace std;

int ackermann(int m,int n) {
    if (m == 0) {
        return n + 1;
    } else if (n == 0) {
        return ackermann(m - 1, 1);
    } else {
        return ackermann(m - 1, ackermann(m, n - 1));
    }
}
int main() {
    int m, n;
    cout << "請輸入 m 和 n 的值: ";
    cin >> m >> n;
    cout << "(" << m << ',' << n << ") = " << (m, n);
    return 0;
}