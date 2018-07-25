/*

 */

#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll solveSmall() {

    return ret;
}

int main() {
    clock_t tStart = clock();
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2018/Round-B/A-small-attempt0.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2018/Round-B/A-small-attempt0.out", "w", stdout);
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> F >> L;

        cout << "Case #" << i << ": " << solveSmall() << endl;

        //        cerr << "Case #" << i << " time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    }

    cerr << "Time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;

    return 0;
}
