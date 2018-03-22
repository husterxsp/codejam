/**
 给定两个字符串，其中 * 可以匹配 0-4的字符，判断两个给定的字符串是否匹配。
 */

/**
 解法一：DFS，可以解决small数据集

 调试中遇到的两个问题:
 1. 当 a[0]='*'，遍历 b[0]~b[4]时，要考虑 b[i]='*'的情况，例如 a="ifJ*k", b="*"
 2. solve函数一开始删除a, b相同的字符串时把 '*' 也删了，故while判断加上 a[p] != '*'
 */
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>

using namespace std;

bool solve(string a, string b) {
    int p = 0;
    while (p < a.size() && p < b.size() && a[p] == b[p] && a[p] != '*') p++;
    a = a.substr(p, a.size() - p);
    b = b.substr(p, b.size() - p);

    if (a == "" || b == "") {
        if (b == "") swap(a, b);
        for (int i = 0; i < b.size(); i++) {
            if (b[i] != '*') return false;
        }
        return true;
    }

    if (a[0] == '*' || b[0] == '*') {
        if (b[0] == '*') swap(a, b);
        for (int i = 0; i <= 4 && i <= b.size(); i++) {
            int cnt = 0, k = 0;
            for (k = 0; k < b.size() && cnt < i; k++) {
                if (b[k] != '*') cnt++;
            }
            if (solve(a.substr(1, a.size() - 1), b.substr(k, b.size() - k))) return true;
        }
    }
    return false;
}

int main() {
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-A/B-small-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-A/B-small-practice.out", "w", stdout);
    int T, line = 1;
    cin >> T;

    while(T--) {
        string a, b;
        cin >> a >> b;

        cout << "Case #" << line++ << ": " << (solve(a, b) ? "TRUE" : "FALSE") << endl;
    }

//    cout << solve("*", "*CFFE") << endl;
    return 0;
}


/**
    解法二：动规
*/

/**
 给定两个字符串，其中 * 可以匹配 0-4的字符，判断两个给定的字符串是否匹配。
 */

/**
 解法一：DFS
 需要注意的是 当 a[0]='*'，遍历 b[0]~b[4]时，要考虑 b[i]='*'的情况，例如 a="ifJ*k", b="*"
 */
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>

using namespace std;

bool solve(string a, string b, vector<vector<int>>& dp) {

    a = 'a' + a;
    b = 'a' + b;
    for (int i = 1; i <= a.size(); i++) {
        for (int j = 1; j <= b.size(); j++) {
            if (dp[][])
            if (a[i] == b[j] && a[i] != '*') dp[i][j] = dp[i - 1][j - 1];
            else if (a[i] == '*' && dp[i - 1][j - 1]) {
                int cnt = 0, k = 0;
                for (k = 0; cnt < 4; k++) {
                    if (b[k] != '*') cnt++;
                    dp[i][j + k] = 1;
                }
            }
            else if (b[j] == '*' && dp[i - 1][j - 1]) {
                int cnt = 0, k = 0;
                for (k = 0; cnt < 4; k++) {
                    if (b[k] != '*') cnt++;
                    dp[i + k][j] = 1;
                }
            }
        }
    }

    return dp[a.size() - 1][b.size() - 1];
}
int main() {

//    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-A/B-small-practice.in", "r", stdin);
//    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-A/B-small-practice.out", "w", stdout);
//    int T, line = 1;
//    cin >> T;
//
//    while(T--) {
//        string a, b;
//        cin >> a >> b;
//
//        vector<vector<int>> dp(210, vector<int>(210));
//        dp[0][0] = 1;
//        cout << "Case #" << line++ << ": " << (solve("a" + a, "a" + b, dp) ? "TRUE" : "FALSE") << endl;
//    }

    vector<vector<int>> dp(200, vector<int>(200));
    dp[0][0] = 1;
//    cout << (solve("THAkZYrkUWgcTpZ**v*GyMlROpiIDUZyJjh", "*THAkZYrkUWgcTpZYa*nBvIFuGyMlROpiIDUZyJjh", dp) ? "TRUE" : "FALSE") << endl;
    cout << (solve("T", "*T", dp) ? "TRUE" : "FALSE") << endl;
    return 0;
}
