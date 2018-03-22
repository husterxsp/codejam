Small dataset: dfs, 注意中位数和均值均需要exactly equal。所以要判断%是否为0

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <unordered_set>
#include <numeric>

using namespace std;

int MIN, MAX, MEAN, MEDIAN;

bool dfs(vector<int> depart, int pos, int departNum, int MIN, int MAX) {
    if (pos == departNum - 1) {
        int sum = accumulate(depart.begin(), depart.end(), 0);

        if (sum % departNum != 0) return false;

        int mean = sum / departNum, mid;

        if (departNum % 2 == 1) mid = depart[departNum / 2];
        else {
            int midSum = depart[departNum / 2] + depart[departNum / 2 - 1];
            if (midSum % 2 != 0) return false;
            mid = midSum / 2;
        }

        if (mean == MEAN && mid == MEDIAN) return true;
        else return false;
    }
    for (int i = MIN; i <= MAX; i++) {
        depart[pos] = i;
        if (dfs(depart, pos + 1, departNum, depart[pos], MAX)) return true;
    }
    return false;
}
string solve() {
    if (MIN == MAX && MAX == MEAN && MEAN == MEDIAN) return "1";
    for (int i = 2; i < 14; i++) {
        vector<int> depart(i);

        depart[0] = MIN;
        depart[i - 1] = MAX;

        if (dfs(depart, 1, i, depart[0], MAX)) return to_string(i);
    }
    return "IMPOSSIBLE";
}
int main() {
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-C/D-small-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-C/D-small-practice.out", "w", stdout);
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> MIN >> MAX >> MEAN >> MEDIAN;
        cout << "Case #" << i << ": " << solve() << endl;
    }

    return 0;
}


Large dataset:
参考analysis
其实不用单独考虑每一个数，只需要考虑这些数的和满足一定的条件。比如analysis 里直接插入 MEDIAN + MIN 来减小误差。


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <unordered_set>
#include <numeric>

using namespace std;

int MIN, MAX, MEAN, MEDIAN;

int ceil(int a, int b) {
    if (b <= 0) return 0;
    return a / b + (a % b == 0 ? 0 : 1);
}

string solve() {
    if (MAX < MIN || MAX < MEDIAN || MAX < MEAN || MEDIAN < MIN || MEAN < MIN) return "IMPOSSIBLE";
    if (MIN == MAX && MAX == MEAN && MEAN == MEDIAN) return "1";
    if (MIN + MAX == 2 * MEAN && MIN + MAX == 2 * MEDIAN) return "2";

//    if (2*mean-min-median<=0 || median+max-2*mean<=0) return "IMPOSSIBLE";
//    if (MIN + MEDIAN >= 2 * MEAN || MAX + MEDIAN <= 2 * MEAN) return "IMPOSSIBLE";

    // odd
    int odd = 3, even = 4, ret = INT_MAX;
    if (MIN + MAX + MEDIAN >= 3 * MEAN) {

        odd += 2 * ceil(MIN + MAX + MEDIAN - 3 * MEAN, 2 * MEAN - (MIN + MEDIAN));
        if (2 * MEAN - (MIN + MEDIAN) > 0) ret = min(ret, odd);
    }
    else {
        odd += 2 * ceil(3 * MEAN - (MIN + MAX + MEDIAN), MAX + MEDIAN - 2 * MEAN);
        if (MAX + MEDIAN - 2 * MEAN > 0) ret = min(ret, odd);
    }
    // even
    if (MIN + MAX + 2 * MEDIAN >= 4 * MEAN) {
        even += 2 * ceil(MIN + MAX + 2 * MEDIAN - 4 * MEAN, 2 * MEAN - (MIN + MEDIAN));
        if (2 * MEAN - (MIN + MEDIAN) > 0) ret = min(ret, even);
    }
    else {
        even += 2 * ceil(4 * MEAN - (MIN + MAX + 2 * MEDIAN), MAX + MEDIAN - 2 * MEAN);
        if (MAX + MEDIAN - 2 * MEAN > 0) ret = min(ret, even);
    }
    return ret == INT_MAX ? "IMPOSSIBLE" : to_string(ret);
}
int main() {
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-C/D-large-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-C/D-large-practice.out", "w", stdout);
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> MIN >> MAX >> MEAN >> MEDIAN;
        cout << "Case #" << i << ": " << solve() << endl;
    }

    return 0;
}
