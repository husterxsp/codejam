/**
    L个左括号，R个右括号，求能拼成的字符串的 balanced non-empty substrings 最多的个数。
    最多的情况： ...()()()()()...
    C(n, 2)

    需要注意用 long，数比较大
*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>

using namespace std;

long solve(int L, int R) {
    long N = min(L, R);
    return N * (N + 1) / 2;
}
int main() {
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Practice-Round/C-large-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Practice-Round/C-large-practice.out", "w", stdout);
    int T, line = 1;
    cin >> T;

    while(T--) {
        int L, R;
        cin >> L >> R;
        cout << "Case #" << line++ << ": " << solve(L, R) << endl;
    }

    return 0;
}
