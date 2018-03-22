#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <unordered_set>

#define ll long long

using namespace std;

int a, n, p;

// 取模1：暴力

ll getMod1(int a, int n, int p) {
    ll ret = 1;
    for (int i = 1; i < n; i++) {
        ret = (ret * a) % p;
    }
    return ret;
}
// 取模2：数论，蒙哥马利算法


// 取模3：分治
ll getMod3(int a, int n, int p) {

    if (n == 0) return 1;

    ll half = getMod3(a, n / 2, p);
    ll ret = (half * half) % p;

    if (n % 2 == 0) return ret;

    return (ret * a) % p;
}

ll solve() {
    ll ret = a % p;
    for (int i = 2; i <= n; i++) {
        ret = getMod3(ret, i, p);
    }
    return ret;
}

int main() {
    clock_t tStart = clock();
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-G/A-large-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-G/A-large-practice.out", "w", stdout);
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> a >> n >> p;
        cout << "Case #" << i << ": " << solve() << endl;

        cerr << "Case #" << i << " time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    }
    cerr << "Time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    return 0;
}
