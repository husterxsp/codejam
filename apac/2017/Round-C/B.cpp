/*

 */

#include <bits/stdc++.h>
#define ll long long

using namespace std;
vector<vector<int>> matrix;
int R, C, K;

ll solve() {
    // 左上角、右下角
    vector<vector<int>> dp(R, vector<int>(C));

    dp[0][0] = matrix[0][0];
    for (int i = 1; i < R; i++) {
        dp[i][0] = dp[i - 1][0] + matrix[i][0];
    }
    for (int i = 1; i < C; i++) {
        dp[0][i] = dp[0][i - 1] + matrix[0][i];
    }
    for (int i = 1; i < R; i++) {
        for (int j = 1; j < C; j++) {
            dp[i][j] = dp[i][j - 1] + dp[i - 1][j] - dp[i - 1][j - 1] + matrix[i][j];
        }
    }

    ll ret = R * C - K;
    int maxEdge = min(R, C);
    for (int i = 2; i <= maxEdge; i++) {
        for (int j = 0; j + i - 1 < R; j++) {
            for (int k = 0; k + i - 1 < C; k++) {
                int sum = dp[j + i - 1][k + i - 1];
                if (j > 0) sum -= dp[j - 1][k + i - 1];
                if (k > 0) sum -= dp[j + i - 1][k - 1];
                if (j > 0 && k > 0) sum += dp[j - 1][k - 1];
                if (sum == 0) ret++;
            }
        }
    }

    return ret;
}

int main() {
    clock_t tStart = clock();

    freopen("/Users/xushaopeng/Desktop/codejam/apac/2017/Round-C/B-small-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/apac/2017/Round-C/B-small-practice.out", "w", stdout);

    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> R >> C >> K;
        matrix.assign(R, vector<int>(C));

        for (int j = 0; j < K; j++) {
            int Ri, Ci;
            cin >> Ri >> Ci;
            matrix[Ri][Ci] = 1;
        }
        cout << "Case #" << i << ": " << solve() << endl;
        cerr << "Case #" << i << endl;
    }

    cerr << "Time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;

    return 0;
}
