#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <unordered_set>

using namespace std;

int N;
/*
错解，直接每次考虑最大的。但是实际比如 N=19 = 3*3 + 3*3 + 1*1，需要3个
而按照以下算法，需要 19 = 4*4 + 1*1 + 1*1 + 1*1 需要4个
*/

vector<int> square(101);
int solve1() {
    int ret = 0;
    while (N != 0) {
        for (int i = 100; i >= 1; i--) {
            if (N >= square[i]) {
                N -= square[i];
                ret++;
                break;
            }
        }
    }
    return ret;
}

/*
 参考解析，动规
 leetcode 四方数。。。
*/
vector<int> dp(20010, -1);
int solve() {
    dp[0] = 0;
    for (int i = 1; i <= 100; i++) {
        for (int j = 0; j <= 10000; j++) {
            if (dp[j + i*i] == -1 || dp[j + i*i] > dp[j] + 1) {
                dp[j + i * i] = dp[j] + 1;
            }
        }
    }
}

int main() {
    clock_t tStart = clock();
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-F/D-small-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-F/D-small-practice.out", "w", stdout);
    int T;
    cin >> T;

    // for (int i = 0; i <= 100; i++) square[i] = i * i;

    solve();
    for (int i = 1; i <= T; i++) {
        cin >> N;

        cout << "Case #" << i << ": " << dp[N] << endl;

        cerr << "Case #" << i << ": " << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    }
    cerr << "Time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    return 0;
}
