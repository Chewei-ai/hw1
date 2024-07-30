#include <iostream>
#include <stack>
#include <tuple>

using namespace std;

int ackermann_iterative(int m, int n) {
    stack<pair<int, int>> stack;
    stack.push(make_pair(m, n));

    while (!stack.empty()) {
        tie(m, n) = stack.top();
        stack.pop();

        if (m == 0) {
            n += 1;
        } else if (n == 0) {
            stack.push(make_pair(m - 1, 1));
            continue;  // 跳过后续逻辑，因为我们已经将下一步压入堆栈
        } else {
            stack.push(make_pair(m - 1, 0)); 
            stack.push(make_pair(m, n - 1));
            continue;  // 跳过后续逻辑，因为我们已经将下一步压入堆栈
        }

        if (!stack.empty()) {
            auto &top = stack.top();
            stack.pop();
            stack.push(make_pair(get<0>(top), n));
        }
    }

    return n;
}
int main() {
    int m, n;
    cout << "請輸入 m 和 n 的值: ";
    cin >> m >> n;
    int result = ackermann_iterative(m, n);  
    cout << "ackermann_iterative(" << m << ", " << n << ") = " << result << endl;
    return 0;
}
