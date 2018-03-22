只能过小数据集
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>

using namespace std;

int R, C, K;

int solve(vector<vector<int>> grid, vector<vector<int>> dp) {
    vector<vector<int>> rSum(grid), cSum(grid);

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            rSum[i][j] = rSum[i][j - 1] + (grid[i][j] == 1);
        }
    }
    for (int j = 1; j <= C; j++) {
        for (int i = 1; i <= R; i++) {
            cSum[i][j] = cSum[i - 1][j] + (grid[i][j] == 1);
        }
    }

    int maxEdge = min(R, C), ret = R * C - K;
    for (int e = 2; e <= maxEdge; e++) {
        cerr << "edge:" << e << endl;
        for (int i = e; i <= R; i++) {
            for (int j = e; j <= C; j++) {
                if (grid[i][j] == 0 &&
                    rSum[i][j] - rSum[i][j - e] == 0 &&
                    cSum[i][j] - cSum[i - e][j] == 0 &&
                    dp[i - 1][j - 1] >= e - 1
                ) {
                    dp[i][j] = e;
                    ret++;
                }
            }
        }
    }

    return ret;
}
int main() {
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Practice-Round-2/B-large-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Practice-Round-2/B-large-practice.out", "w", stdout);
    int T, line = 1;
    cin >> T;

    while(T--) {
        cin >> R >> C >> K;

        vector<vector<int>> grid(R + 1, vector<int>(C + 1)), dp(R + 1, vector<int>(C + 1, 1));

        int r, c;
        for (int i = 0; i < K; i++) {
            cin >> r >> c;
            grid[r + 1][c + 1] = 1;
            dp[r + 1][c + 1] = 0;
        }
        cerr << "test:" << T << endl;
        cout << "Case #" << line++ << ": " << solve(grid, dp) << endl;
    }

    return 0;
}

优化： 注意返回值用long，int会溢出
参考：http://blog.csdn.net/ihsin/article/details/54845972

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>

using namespace std;

int R, C, K;

long solve(vector<vector<int>> grid, vector<vector<int>> dp) {

    long ret = 0;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            if (grid[i][j] == 0) dp[i][j] = min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j])) + 1;
        }
    }
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            ret += dp[i][j];
        }
    }
    return ret;
}
int main() {
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Practice-Round-2/B-large-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Practice-Round-2/B-large-practice.out", "w", stdout);
    int T, line = 1;
    cin >> T;

    while(T--) {
        cin >> R >> C >> K;

        vector<vector<int>> grid(R + 1, vector<int>(C + 1)), dp(R + 1, vector<int>(C + 1));

        int r, c;
        for (int i = 0; i < K; i++) {
            cin >> r >> c;
            grid[r + 1][c + 1] = 1;
            dp[r + 1][c + 1] = 0;
        }
        cerr << "test:" << T << endl;
        cout << "Case #" << line++ << ": " << solve(grid, dp) << endl;
    }

    return 0;
}
