small dataset

数学题。抛物线。待再看。。心累

#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <unordered_set>

using namespace std;

int N, P, H;
vector<vector<int>> obstacle;
double solve() {

}
int main() {
    clock_t tStart = clock();
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-D/C-small-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-D/C-small-practice.out", "w", stdout);
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> N >> P >> H;

        obstacle.clear();
        for (int j = 0; j < N; j++) {
            cin >> x >> y;
            obstacle.push_back({x, y});
        }
        cout << "Case #" << i << ": " << solve() << endl;
    }
    cerr << "Time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    return 0;
}
