// 暴力解，过小数据集
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>

const int mod = 1e9 + 7;
using namespace std;

double solve(vector<vector<double>> point, int N) {
    int x_min = INT_MAX, x_max = INT_MIN, y_min = INT_MAX, y_max = INT_MIN;
    for (int i = 0; i < N; i++) {
        x_min = min((double)x_min, point[i][0]);
        x_max = max((double)x_max, point[i][0]);

        y_min = min((double)y_min, point[i][1]);
        y_max = max((double)y_max, point[i][1]);
    }
    double ret = 0;
    for (int i = x_min; i < x_max; i++) {
        for (int j = y_min; j < y_max; j++) {
            double tmp = 0;
            for (int k = 0; k < N; k++) {
                tmp += max(abs(point[k][0] - i), abs(point[k][1] - j)) * point[k][2];
            }
            if (ret == 0 || tmp < ret) ret = tmp;
        }
    }
    return ret;
}
int main() {
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-B/B-small-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-B/B-small-practice.out", "w", stdout);
    int T, line = 1;
    cin >> T;

    while(T--) {
        int N;
        cin >> N;

        vector<vector<double>> point(N, vector<double>(3));

        for (int i = 0; i < N; i++) cin >> point[i][0] >> point[i][1] >> point[i][2];

        cout << "Case #" << line++ << ": " << solve(point, N) << endl;
    }


    //        vector<int> num{1,2,3,4,5};
    //        cout << solve(num, 5) << endl;
    return 0;
}

// 三分搜索。
问题：
1. 以下代码中的三分搜索for循环执行多少次？
2. vector的问题

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>

const int mod = 1e9 + 7;
using namespace std;


int N;
double point[10005][3];
//static vector<vector<double>> point(10005, vector<double>(3));

double calc(double x, double y) {
    double ret = 0;
    for (int i = 0; i < N; i++) {
        ret += point[i][2] * max(fabs(point[i][0] - x), fabs(point[i][1] - y));
    }
    return ret;
}
double calc(double x) {
    double low = -1000, high = 1000;
    for (int i = 0; i < 200; i++) {
        double p1 = low + (high - low) / 3;
        double p2 = low + 2 * (high - low) / 3;

        if (calc(x, p1) > calc(x, p2)) low = p1;
        else high = p2;
    }
    return calc(x, low);
}
double solve() {
    double low = -1000, high = 1000;
    for (int i = 0; i < 200; i++) {
        double p1 = low + (high - low) / 3;
        double p2 = low + 2 * (high - low) / 3;

        if (calc(p1) > calc(p2)) low = p1;
        else high = p2;
    }

    return calc(low);
}
int main() {
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-B/B-large-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-B/B-large-practice.out", "w", stdout);
    int T, line = 1;
    cin >> T;

    while(T--) {
        //        point.clear();
        memset(point, 0, sizeof(point));

        cin >> N;

        for (int i = 0; i < N; i++) cin >> point[i][0] >> point[i][1] >> point[i][2];

        printf("Case #%d: %.9lf\n", line++, solve());
//        cout << "Case #" << line++ << ": " <<  solve() << endl;
    }

    return 0;
}
