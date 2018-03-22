能过small, large 溢出
#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <iomanip>

#define ld long double
using namespace std;

class Edge {
public:
    ld u, v, weight;
    Edge(int u, int v, int w)
    :u(u), v(v), weight(w) {}
};

int N, M, P;

vector<Edge*> edges;
vector<ld> dis, sumdis;

vector<ld> powN;

void BellmanFord() {
    for (int i = 1; i <= N - 1; i++) {
        bool flag = 0;
        for (int j = 1; j <= M; j++) {
            int u = edges[j]->u, v = edges[j]->v, weight = edges[j]->weight;

            if (dis[u] > dis[v] + weight) {
                dis[u] = dis[v] + weight;
                flag = 1;
            }
            if (dis[v] > dis[u] + weight) {
                dis[v] = dis[u] + weight;
                flag = 1;
            }
        }
        // flag=0表示一次遍历中没有松弛操作，提前直接退出
        if (!flag) break;
    }
}

void init() {
    for (int i = 1; i <= N; i++) {
        dis.assign(N + 1, 1e9);

        dis[i] = 0;
        BellmanFord();

        sumdis[i] = accumulate(dis.begin() + 1, dis.end(), 0);
    }

    powN.assign(P + 1, 1);
    for (int i = 1; i <= P; i++) {
        powN[i] = powN[i - 1] * (N - 1);
    }

}

ld solve() {
    ld ret = 0;
    vector<ld> leaf(N + 1);
    leaf[1] = 1;

    for (int p = 1; p <= P; p++) {

        vector<ld> tmpLeaf(N + 1);
        for (int i = 1; i <= N; i++) {
            if (leaf[i] == 0) continue;

//            if (p == 1) ret += ((ld)1/(N-1))* sumdis[i];
//            else ret += (leaf[i] * sumdis[i]);

            ret += (leaf[i] * sumdis[i]) / powN[p];
            for (int j = 1; j <= N; j++) {
                if (j == i) continue;
//                tmpLeaf[j] += leaf[i] / powN[p + 1];
//                tmpLeaf[j] += leaf[i]  / powN[p+1];
//                tmpLeaf[j] += leaf[i] / (N-1);
                 tmpLeaf[j] += leaf[i];
            }
        }
        leaf = tmpLeaf;
//        for (int i=0;i < leaf.size(); i++) {
//            leaf[i] /= N-1;
//        }
    }

    return ret;
}

int main() {
    clock_t tStart = clock();
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-F/C-small-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-F/C-small-practice.out", "w", stdout);
    int T;
    cin >> T;

    setprecision(15);

    for (int i = 1; i <= T; i++) {
        cin >> N >> M >> P;

        int u, v, d;

        edges.assign(M + 1, NULL);
        sumdis.assign(N + 1, 0);

        for (int j = 1; j <= M; j++) {
            cin >> u >> v >> d;
            edges[j] = new Edge(u, v, d);
        }

        init();

        cout << "Case #" << i << ": " << solve() << endl;

        cerr << "Case #" << i << ": " << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    }
    cerr << "Time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    return 0;
}
