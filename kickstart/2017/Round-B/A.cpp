跑大数据集大概要1min。 O(n^2)
大概思路：
比如 以 1，2，3，4，5 为例先求出2set，即：
4 {1，2}，{1，3}，{1，4}，{1，5}
6 {1，3}，{2，4}，{3，5}
6 {1，4}，{2，5}
4 {1，5}
20

之后的3set、4set、5set是在2set的基础上做一些改变

比如3set包含上面的2set的第二行、第三行*C(2, 1)、第四行*C(3,1) = 30
4set 包含上面的2set的第三行、第四行*C(3,1) = 18
5set = 4

结果20+30+18+4=72

其实也就是固定两边的数，求中间有多少种组合。

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>

const int mod = 1e9 + 7;

using namespace std;

long add(long a, long b) {
    return (a + b) % mod;
}

long C[10005][10005];
void initial() {
    int i, j;
    for(i = 0; i <= 10001; ++i) {
        C[0][i] = 0;
        C[i][0] = 1;
    }
    for(i = 1; i<= 10001; ++i) {
        for(j = 1; j <= 10001; ++j)
            C[i][j] = (C[i-1][j] + C[i-1][j-1]) % mod;
    }
}
long solve(vector<int> num, int N) {
    if (N == 1) return 0;

    vector<long> sum2(N);
    vector<long> sum(N + 1);

    for (int k = 1; k <= N - 1; k++) {
        for (int i = 0; i < N - k; i++) {
            long diff = (num[i + k] - num[i]) % mod;
            sum2[k - 1] = add(diff, sum2[k - 1]);
        }
    }

    for (int i = 0; i < N; i++) sum[2] = add(sum[2], sum2[i]);

    // 3subset ~ N subset
    for (int i = 3; i <= N; i++) {
        for (int j = i - 2; j < N - 1; j++) {
            sum[i] = add(sum[i], sum2[j] * C[j][i - 2]);
        }
    }

    long ret = 0;
    for (int i = 0; i < sum.size(); i++) {
        ret = add(ret, sum[i]);
    }

    //    ret = add(ret, sum.back());
    return ret;
}

int main() {
    initial();
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-B/A-large-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-B/A-large-practice.out", "w", stdout);
    int T, line = 1;
    cin >> T;

    while(T--) {
        int N;
        cin >> N;

        vector<int> num(N);
        for (int i = 0; i < N; i++) cin >> num[i];

        cout << "Case #" << line++ << ": " << solve(num, N) << endl;
    }


//        vector<int> num{1,2,3,4,5};
//        cout << solve(num, 5) << endl;
    return 0;
}


优化：
