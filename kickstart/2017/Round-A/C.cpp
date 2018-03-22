给定坐标系中有若干球体，用两个边长相同的正方体来包括这些球，求该正方体的最小边长。要求该正方体边平行于坐标轴。

思路：二分。先用两个最小的截面确定一个cube，再用二分 确定另外一个cube。

//A codejam 的题其实可以直接写全局变量，和LeetCode不太一样。因为leetcode规定了函数的形式。

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>

const int mod = 1e9 + 7;

using namespace std;

int N;
int star[2010][4];
bool vis[2010];

bool cover(int x_min, int y_min, int z_min, int r) {

    for (int i = 0; i < N; i++) {
        if (star[i][0] - star[i][3] >= x_min &&
            star[i][0] + star[i][3] <= x_min + r &&
            star[i][1] - star[i][3] >= y_min &&
            star[i][1] + star[i][3] <= y_min + r &&
            star[i][2] - star[i][3] >= z_min &&
            star[i][2] + star[i][3] <= z_min + r
            ) vis[i] = true;
        else vis[i] = false;
    }

    int xMax = INT_MIN, xMin = INT_MAX;
    int yMax = INT_MIN, yMin = INT_MAX;
    int zMax = INT_MIN, zMin = INT_MAX;
    for (int i = 0; i < N; i++) {
        if (!vis[i]) {
            xMin = min(xMin, star[i][0] - star[i][3]);
            xMax = max(xMax, star[i][0] + star[i][3]);

            yMin = min(yMin, star[i][1] - star[i][3]);
            yMax = max(yMax, star[i][1] + star[i][3]);

            zMin = min(zMin, star[i][2] - star[i][3]);
            zMax = max(zMax, star[i][2] + star[i][3]);
        }
    }

    if (xMax - xMin <= r && yMax - yMin <= r && zMax - zMin <= r) return true;
    return false;
}

int solve() {
    int xMax = INT_MIN, xMin = INT_MAX;
    int yMax = INT_MIN, yMin = INT_MAX;
    int zMax = INT_MIN, zMin = INT_MAX;
    for (int i = 0; i < N; i++) {
        xMin = min(xMin, star[i][0] - star[i][3]);
        xMax = max(xMax, star[i][0] + star[i][3]);

        yMin = min(yMin, star[i][1] - star[i][3]);
        yMax = max(yMax, star[i][1] + star[i][3]);

        zMin = min(zMin, star[i][2] - star[i][3]);
        zMax = max(zMax, star[i][2] + star[i][3]);
    }

    int left = 0, right = 1e9;
    while (left < right) {
        int r = left + (right - left) / 2;
        if (cover(xMin, yMin, zMin, r) ||
            cover(xMin, yMin, zMax - r, r) ||
            cover(xMin, yMax - r, zMin, r) ||
            cover(xMin, yMax - r, zMax - r, r) ||
            cover(xMax - r, yMin, zMin, r) ||
            cover(xMax - r, yMin, zMax - r, r) ||
            cover(xMax - r, yMax - r, zMin, r) ||
            cover(xMax - r, yMax - r, zMax - r, r)
            ) right = r;
        else left = r + 1;
    }

// 这里其实都一样
   return left;
    // return right;
}

int main() {
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-A/C-small-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-A/C-small-practice.out", "w", stdout);
    int T, line = 1;
    cin >> T;

    while(T--) {
        cin >> N;

        for (int i = 0; i < N; i++) {
            cin >> star[i][0] >> star[i][1] >> star[i][2] >> star[i][3];
        }

        cout << "Case #" << line++ << ": " << solve() << endl;
    }

    return 0;
}
