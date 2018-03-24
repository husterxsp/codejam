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
数据比较大，注意用 long long.
prim 算法模板

#include <bits/stdc++.h>

#define ll long long
#define ld long double

using namespace std;

int N;
vector<ll> r, b, vis;
vector<vector<ll>> graph;

ll prim() {
    vector<ll> dis(N + 1, LLONG_MAX), vis(N + 1, 0);
    ll ret = 0;

    // 初始时假设1节点也没访问
    dis[1] = 0;

    // 外层循环，合并N次
    for (int i = 1; i <= N; i++) {

        int v = -1;
        for (int j = 1; j <= N; j++) {
            if (vis[j]) continue;
            if (v == -1 || dis[j] < dis[v]) v = j;
        }

        //没合并 n 条边就已经要结束了，说明图不联通
        if (v == -1) return -1;

        vis[v] = 1;
        ret += dis[v];

        // 合并v节点的过程
        for (int j = 1; j <= N; j++) {
            dis[j] = min(dis[j], graph[v][j]);
        }
    }
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

        graph.assign(N + 1, vector<ll>(N + 1));

        for (int j = 1; j <= N; j++) cin >> r[j];

        for (int j = 1; j <= N; j++) cin >> b[j];

        for (int j = 1; j <= N; j++) {
            for (int k = 1; k <= N; k++) {
                if (j == k) continue;
                graph[j][k] = graph[k][j] = min(r[j]^b[k], r[k]^b[j]);
            }
        }

        cout << "Case #" << i << ": " << prim() << endl;

        cerr << "Case #" << i << " time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    }
    cerr << "Time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    return 0;
}
