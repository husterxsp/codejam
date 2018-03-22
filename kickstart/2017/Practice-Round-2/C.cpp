#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>

using namespace std;

long solve(long n) {
    for (int l = log(n + 1)/ log(2); l >= 2; l--) {
        long left = 2, right = pow(n, 1.0 / (l - 1)) + 1;

        while (left < right) {
            long mid = left + (right - left) / 2, sum = 0;

            for (int j = 0; j < l; j++) {
                sum = sum * mid + 1;
            }

            if (sum == n) return mid;
            if (sum > n) right = mid;
            else left = mid + 1;
        }
    }
    return n - 1;
}

int main() {
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Practice-Round-2/C-large-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Practice-Round-2/C-large-practice.out", "w", stdout);
    int T, line = 1;
    long n;
    cin >> T;

    while(T--) {
        cin >> n;
        cerr << "test:" << T << endl;
        cout << "Case #" << line++ << ": " << solve(n) << endl;
    }

    return 0;
}
