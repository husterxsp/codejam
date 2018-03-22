/**
 N + M个选民对 A、B两个竞选者进行投票，其中支持A的有N人，支持B的有M人，已知 N > M.
 选民一个个地进行投票，问 每投一票，A的已有选票都多于B的情况有多少种。总共可知有 (N + M)! 中情况。
 */

 /**
    解法一：递归+记忆化搜索（动规的另一种形式）
 */
 #include <iostream>
 #include <string>
 #include <vector>
 #include <map>
 #include <set>

 using namespace std;

 vector<vector<double>> dp(2001, vector<double>(2001, -1));

 double vote(int N, int M) {
     if (dp[N][M] != -1) return dp[N][M];
     double ret = 0.0;

     if (N <= M) return dp[N][M] = 0;
     if (M == 0) return dp[N][M] = 1;

     return dp[N][M] = (double)N / (N + M) * vote(N - 1, M) + (double)M / (N + M) * vote(N, M - 1);
 }
 int main() {
     freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Practice-Round/B-large-practice.in", "r", stdin);
     freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Practice-Round/B-large-practice.out", "w", stdout);
     int T, line = 1;
     cin >> T;

     cout.precision(7);
     while(T--) {
         int N, M;
         cin >> N >> M;

         cout << "Case #" << line++ << ": " << vote(N, M) << endl;
     }

     return 0;
 }

/**
解法二：
直接动规。

难点：

加法溢出。需要用对数运算。乘除转换为对数加减。

加法转换：

c = log(e^a + e^b)。
解释：此处 a、b即是已经经过对数转换的，那么计算 a' + b'，就需要 先取幂次转换为原来的比较大的数，即 a' = e^a。
然后计算 两个比较大的数字 a' + b' = c'，再对 c' 取对数 变成比较小的 c 存储。
另外，上述的计算式 e^a + e^b 也可能溢出，需要进一步转换，c = log(e^a( 1 + e^(b - a) )) = a + log(1 + e^(b - a) )

有点问题：用二维数组和用vector的结果为啥不一样呢？？？？

参考：https://www.cnblogs.com/itcsl/p/6500797.html
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>

using namespace std;

const int maxn = 200;

vector<vector<double>> dp(maxn, vector<double>(maxn, -1));
//double dp[maxn][maxn];

void vote() {
    for(int i = 0; i < maxn; i++) {
        for(int k = 0; k < maxn; k++) {
            dp[i][k] = -1;
        }
    }
    dp[0][0] = log(1.0);

    for (int i = 0; i < maxn; i++) {
        for (int j = 0; j < maxn; j++) {
            if (j >= i) continue;
            if (dp[i - 1][j] != -1 && dp[i][j - 1] != -1) dp[i][j] = dp[i - 1][j] + log(1 + exp(dp[i][j - 1] - dp[i - 1][j]));

            else if (dp[i - 1][j] != -1) dp[i][j] = dp[i - 1][j];
            else if (dp[i][j - 1] != -1) dp[i][j] = dp[i][j - 1];
        }
    }
}

int main() {

    vote();
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Practice-Round/B-small-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Practice-Round/B-small-practice.out", "w", stdout);
    int T, line = 1;
    cin >> T;

    //
    cout.precision(7);

    while(T--) {
        int N, M;
        cin >> N >> M;

        double ret = 0;
        for (int i = 1; i <= M; i++) {
            ret += (double) log(i) - (double) log(N + i);
        }

        ret += (double)dp[N][M];

        ret = exp(ret);

        // printf("Case #%d: %.8f\n", line++, dp[N][M]);
        cout << "Case #" << line++ << ": " << ret << endl;
    }

    return 0;
}

/**
    解法三，组合数
    
*/
