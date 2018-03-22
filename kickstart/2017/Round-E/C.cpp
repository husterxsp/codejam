small datsets: (max{X} - min{X}) / 6

#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <unordered_set>

using namespace std;

vector<double> x, y, z;
double solve1() {
    double maxX = max(x[0], max(x[1], x[2])), minX = min(x[0], min(x[1], x[2]));
    return (maxX - minX) / 6;
}

double disMax, disMin;
double dis1, dis2, dis3, r;

double dis(int i, int j) {
    return sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2) + pow(z[i] - z[j], 2));
}
bool connected() {
    int cnt = 0;
    cnt += dis1 <= 4*r;
    cnt += dis2 <= 4*r;
    cnt += dis3 <= 4*r;

    return cnt >= 2;
}


double solve() {
    dis1 = dis(0, 1), dis2 = dis(0, 2), dis3 = dis(1, 2);
    disMax = max(dis1, max(dis2, dis3)), disMin = min(dis1, min(dis2, dis3));

    double left = disMin / 4, right = disMax / 4;

    while (left + 1e-10 < right) {
        r = left + (right - left) / 2;
        if (connected()) right = r;
        else left = r;
    }
    return r;
}

int main() {
    clock_t tStart = clock();
//    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-E/C-small-practice.in", "r", stdin);
//    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-E/C-small-practice.out", "w", stdout);
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        x.assign(3, 0);
        y.assign(3, 0);
        z.assign(3, 0);

        for (int j = 0; j < 3; j++) {
            cin >> x[j] >> y[j] >> z[j];
        }

        // 注意保留小数位
        cout.precision(10);
        cout << "Case #" << i << ": " << solve() << endl;
    }
    cerr << "Time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    return 0;
}
