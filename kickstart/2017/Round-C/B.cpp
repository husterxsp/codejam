约束条件：
1. 每行每列至多有两个X, 且有一个X的行/列只有一个。
2. 如果一行有两个X, 则需有另外一行也有两个X，且这两行的X对应列相同，形成矩形

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>

using namespace std;

int N;
vector<string> grid(60);

bool solve() {
    vector<vector<int>> pos(60);
    for (int i = 0; i < N; i++) {
        int columnX = 0;
        for (int j = 0; j < N; j++) {
            // check row
            if (grid[i][j] == 'X') {
                pos[i].push_back(j);
            }
            // check column
            if (grid[j][i] == 'X') {
                columnX++;
            }
        }
        // 这里只检查了0，2的情况，其实因为题目中N的个数的限制，这里 1的检查不必要了。
        if (pos[i].empty() || pos[i].size() > 2) return false;
        if (columnX == 0 || columnX > 2) return false;
    }

    vector<int> vis(60);
    for (int i = 0; i < N; i++) {
        if (vis[i] || pos[i].size() == 1) continue;

        vis[i] = 1;
        int has = 0;

        for (int j = 0; j < N; j++) {
            if (!vis[j] && pos[i] == pos[j]) {
                vis[j] = 1;
                has = 1;
                break;
            }
        }
        if (!has) return false;

    }
    return true;
}
int main() {
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-C/B-large-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-C/B-large-practice.out", "w", stdout);
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> N;

        fill(grid.begin(), grid.end(), "");
        for (int j = 0; j < N; j++) cin >> grid[j];
        cout << "Case #" << i << ": " << (solve() ? "POSSIBLE" : "IMPOSSIBLE") << endl;
    }

    return 0;
}
