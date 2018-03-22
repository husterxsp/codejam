#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>

const int mod = 1e9 + 7;

using namespace std;
int n, m, k, maxTree;

bool checkKTree(int x, int y, int h, vector<string> grid) {
    if (n - x < h || m - y < h || y < h - 1 ) return false;
    for (int i = 0; i < h; i++) {
        for (int j = y - i; j <= y + i ; j++) {
            if (grid[i][j] != '#') return false;
        }
    }
    return true;
}

int dfs(vector<string> grid, int row, int c1, int c2, vector<vector<vector<int>>>& dp) {

    if (row < 0 || c1 < 0 || c2 < 0 || row >= n || c1 >= m|| c2 >= m) return 0;
    if (dp[row][c1][c2] != -1) return dp[row][c1][c2];

    cout << row << "," << c1 << "," << c2 << endl;
    int ret = 0;
    // pos && m-Christmas
    for (int i = row; i < n; i++) {
        for (int j = c1; j < c2; j++) {
            for (int h = max(n - 1, 0); h > 0; h--) {
                if (checkKTree(i, j, h, grid)) {
                    int num = dfs(grid, i + h, j - h, j + h, dp);
                    if (num != 0) ret = max(ret, num + (h + 2 * (h - 1) * h / 2));
                }
            }
        }
    }

    return dp[row][c1][c2] = ret;
}
int solve(vector<string> grid, vector<vector<vector<int>>> dp) {
    return dfs(grid, 0, 0, m - 1, dp);
}


int main() {
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-B/C-small-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-B/C-small-practice.out", "w", stdout);
    int T, line = 1;
    cin >> T;

    while(T--) {
        cin >> n >> m >> k;


        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, -1)));

        vector<string> grid(n + 1);

        for (int i = 0; i < n; i++) cin >> grid[i];

        cout << "Case #" << line++ << ": " << solve(grid, dp) << endl;
    }

    return 0;
}


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>

const int mod = 1e9 + 7;

using namespace std;
int n, m, k;

void check(int r, int c, vector<string> grid, vector<vector<int>>& green) {
    int height = 1;

    while (r + height >= 0&& r + height <= n - 1 && c - height >= 0 && c + height <= m - 1) {
        for (int i = c - height; i <= c + height; i++) {
            if (grid[r + height][i] == 0) {
                green[r][c] = height * height;
                return;
            }
        }
        height++;
    }
    green[r][c] = height * height;
}
int solve(vector<string> grid, vector<vector<int>>& green) {
    int ret = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '#') {
                check(i, j, grid, green);
                ret = max(ret, green[i][j]);
            }
        }
    }

    return ret;
}
int main() {
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-B/C-small-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-B/C-small-practice.out", "w", stdout);
    int T, line = 1;
    cin >> T;

    while(T--) {
        cin >> n >> m >> k;
        vector<string> grid(n + 1);
        vector<vector<int>> green(100, vector<int>(100));

        for (int i = 0; i < n; i++) cin >> grid[i];

        cout << "Case #" << line++ << ": " << solve(grid, green) << endl;
    }

    return 0;
}
