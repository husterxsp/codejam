参考：https://zhuanlan.zhihu.com/p/28829564

small dataset: N <= 6
solve1: 3种可以粘贴复制的模式
111111: 5
121212: 5
123123: 5

solve2：dfs


large dataset:
solve：dp
需要注意粘贴板的内容每次粘贴后没变，所以也需要保存。

dp[i][j][k]，已经输入了前 i 个字母，剪贴板中的字符为 substr[j,k) 时，所需的最少的操作数。
用 dp[i][0][0] 表示 min{dp[i][j][k] | 0 ≤ j < k ≤ i}。或者另开一个一维数组来维护也行。初值为 dp[0][0][0] = 0，其他为正无穷。

#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <unordered_set>

using namespace std;

string s;
int solve1() {
    if (s.size() < 6) return s.size();
    else if (s.substr(0, 2) == s.substr(2, 2) && s.substr(2, 2) == s.substr(4) ||
             s.substr(0, 3) == s.substr(3)) {
        return 5;
    }
    return s.size();
}

// 每个节点三种操作
int solve2(int pos, string clip) {
    if (pos >= s.size()) return 0;
    // type
    int ret = solve2(pos + 1, "");
    // paste
    if (clip.size()) {
        int clipSize = clip.size();
        if (clip == s.substr(pos, clipSize)) ret = min(ret, solve2(pos + clipSize, clip));
    }
    // copy
    clip = "";
    for (int i = 0; i < pos; i++) {
        int len = 0;
        if (s[pos] == s[i]) {
            while (pos + len < s.size() && i + len < pos) {
                if (s[pos + len] == s[i + len]) len++;
                else break;
            }
        }
        if (len > clip.size()) clip = s.substr(pos, len);
    }
    if (clip.size()) ret = min(ret, 1 + solve2(pos + clip.size(), clip));

    return ret + 1;
}

vector<vector<vector<int>>> dp;
int maxStep = 100;
int solve() {
    int n = s.size();
    dp.assign(n + 1, vector<vector<int>>(n + 1, vector<int>(n + 1, 100)));
    dp[0][0][0] = 0;

    for (int i = 0; i < n; i++) {
        // type
        dp[i + 1][0][0] = min(dp[i + 1][0][0],  dp[i][0][0] + 1);

        for (int j = 0; j < i; j++) {
            for (int k = j + 1; k <= i; k++) {
                dp[i + 1][j][k] = min(dp[i + 1][j][k], dp[i][j][k] + 1);

                int clipLen = k - j;
                if (s.substr(j, clipLen) == s.substr(i, clipLen)) {
                    dp[i + k - j][j][k] = min(dp[i + k - j][j][k], min(dp[i][j][k] + 1, dp[i][0][0] + 2));
                    dp[i + k - j][0][0] = min(dp[i + k - j][0][0], min(dp[i][j][k] + 1, dp[i][0][0] + 2));
                }
            }
        }
    }

    return dp[n][0][0];
}

int main() {
    clock_t tStart = clock();
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-E/A-small-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-E/A-small-practice.out", "w", stdout);
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> s;
        cout << "Case #" << i << ": " << solve() << endl;
    }
    cerr << "Time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    return 0;
}
