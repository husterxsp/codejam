/*
 参考analysis 动态规划, 递归

 其实就是递归，另外需要先求出所有的区间最值。

 */

#include <bits/stdc++.h>
#define ll long long

using namespace std;

int N, M;
vector<vector<int>> matrix;

/*
 small dataset

 就是的注意一些边界。
 1. 此处的分割 假设原数组 为 1 2 3
 则有四个分割点 |1|2|3|，则起始时 l=0, r=3
 2. 计算min_element 的时候注意 [first, last)

 */

//vector<vector<int>> dp;
//int solve1(int l, int r) {
//    if (dp[l][r] != -1) return dp[l][r];
//
//    if (l + 1 == r) return dp[l][r] = 0;
//
//    int ret = 0;
//    for (int i = l + 1; i < r; i++) {
//        ret = max(ret, solve1(l, i) + solve1(i, r));
//    }
//
//    ret += *min_element(matrix[1].begin() + l + 1, matrix[1].begin() + r + 1);
//    return dp[l][r] = ret;
//}

// large dataset

// RMQ 模板
int dp[45][45][45][45];
//vector<vector<vector<vector<int>>>> dp;
vector<vector<vector<int>>> rmq;

int query(int k, int left, int right) {
    int j = 0;
    while (1 << (j + 1) <= right - left + 1) j++;

    return min(rmq[k][left][j], rmq[k][right - (1 << j) + 1][j]);
}

void init() {
    memset(dp, 0, sizeof(dp));

    rmq.assign(N + 1, vector<vector<int>>());

    vector<vector<int>> tmp(M + 1, vector<int>(M + 1));

    for (int k = 1; k <= N; k++) {
        // 长度为0，表示数据自身
        for (int i = 1; i <= M; i++) tmp[i][0] = matrix[k][i];

        for (int j = 1; (1<<j) <= M; j++) {
            for (int i = 1; i + ((1 << j) - 1) <= M; i++) {

                tmp[i][j] = min(tmp[i][j - 1], tmp[i + (1<<(j - 1))][j - 1]);
            }
        }
        rmq[k] = tmp;
    }

}
// 此处的参数表示数组中具体元素的位置
int getMin(int l, int r, int p, int q) {
    int ret = INT_MAX;
    for (int i = p; i <= q; i++) {
        ret = min(ret, query(i, l, r));
    }
    return ret;
}
/*
l,r 表示竖着切, p，q表示横着切
此处的参数表示切割的位置
*/
int solve(int l, int r, int p, int q) {
    if (l + 1 == r && p + 1 == q) return 0;
    if (dp[l][r][p][q] != 0) return dp[l][r][p][q];

    int ret = 0;

    for (int i = l + 1; i < r; i++) {
        ret = max(ret, solve(l, i, p, q) + solve(i, r, p, q));
    }
    for (int i = p + 1; i < q; i++) {
        ret = max(ret, solve(l, r, p, i) + solve(l, r, i, q));
    }
    int x = getMin(l + 1, r, p + 1, q);

    return dp[l][r][p][q] = ret + x;
}

int main() {
    clock_t tStart = clock();
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-G/C-large-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-G/C-large-practice.out", "w", stdout);
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> N >> M;

        matrix.assign(N + 1, vector<int>(M + 1, INT_MAX));

        for (int j = 1; j <= N; j++) {
            for (int k = 1; k <= M; k++) {
                cin >> matrix[j][k];
            }
        }

        //        dp.assign(M + 1, vector<int>(M + 1, -1));
        //        cout << "Case #" << i << ": " << solve1(0, M) << endl;

        init();

        cout << "Case #" << i << ": " << solve(0, M, 0, N) << endl;

        cerr << "Case #" << i << " time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    }

    cerr << "Time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;

    return 0;
}
