解法1 暴力搜索
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

int N;
ll ret, cur;
vector<int> r, b, vis;

void dfs(int pos, int boxSize) {
    if (cur >= ret) return;
    if (boxSize <= 1) {
        ret = min(ret, cur);
        return;
    }

    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            if (vis[i] || vis[j]) continue;
            ll add = min(r[i] ^ b[j], r[j] ^ b[i]);
            cur += add;

            vis[i] = 1;
            dfs(0, boxSize - 1);
            vis[i] = 0;

            vis[j] = 1;
            dfs(0, boxSize - 1);
            vis[j] = 0;

            cur -= add;
        }
    }
}
int solve() {
    ret = LLONG_MAX;
    dfs(0, N);
    return ret;
}

int main() {
    clock_t tStart = clock();
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-G/B-large-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-G/B-large-practice.out", "w", stdout);
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> N;

        r.assign(N + 1, 0);
        b.assign(N + 1, 0);
        vis.assign(N + 1, 0);

        for (int j = 1; j <= N; j++) {
            cin >> r[j];
        }

        for (int j = 1; j <= N; j++) {
            cin >> b[j];
        }

        cout << "Case #" << i << ": " << solve() << endl;

        cerr << "Case #" << i << " time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    }
    cerr << "Time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    return 0;
}

解法2， 构造图，求最小生成树

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

int N;
vector<int> r, b, vis;
vector<vector<int>> graph;

int solve() {
    
    return 0;
}

int main() {
    clock_t tStart = clock();
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-G/B-large-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-G/B-large-practice.out", "w", stdout);
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> N;

        r.assign(N + 1, 0);
        b.assign(N + 1, 0);
        vis.assign(N + 1, 0);

        graph.assign(N + 1, vector<int>(N + 1));

        for (int j = 1; j <= N; j++) cin >> r[j];

        for (int j = 1; j <= N; j++) cin >> b[j];

        for (int j = 1; j <= N; j++) {
            for (int k = 1; k <= N; k++) {
                if (j == k) continue;
                graph[j][k] = graph[k][j] = min(r[j]^b[k], r[k]^b[j]);
            }
        }

        cout << "Case #" << i << ": " << solve() << endl;

        cerr << "Case #" << i << " time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    }
    cerr << "Time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    return 0;
}
