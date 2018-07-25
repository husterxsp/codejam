/*
 概率问题
 */

#include <bits/stdc++.h>
#define ll long long

using namespace std;

int R, C, Rs, Cs, S;
double P, Q;

vector<vector<char>> matrix;
vector<vector<int>> vis;

double ret;
int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

double calcProbability(int x, int y) {
    double probability;
    if (matrix[x][y] == 'A') {
        probability = P * pow(1 - P, vis[x][y]);
    }
    else {
        probability = Q * pow(1 - Q, vis[x][y]);
    }
    return probability;
}

void dfs(int x, int y, int steps, double cur) {
    if (steps == 0) {
        ret = max(ret, cur);
        return;
    }
    for (int i = 0; i < 4; i++) {
        int tmpX = x + dir[i][0];
        int tmpY = y + dir[i][1];
        if (tmpX < 0 || tmpX >= R || tmpY < 0 || tmpY >= C) continue;

        double probability = calcProbability(tmpX, tmpY);

        vis[tmpX][tmpY]++;
        dfs(tmpX, tmpY, steps - 1, cur + probability);
        vis[tmpX][tmpY]--;
    }
}

double solve() {
    ret = 0;
    dfs(Rs, Cs, S, 0);

    return ret;
}

int main() {
    clock_t tStart = clock();

    freopen("/Users/xushaopeng/Desktop/codejam/apac/2017/Round-C/A-large-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/apac/2017/Round-C/A-large-practice.out", "w", stdout);

    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> R >> C >> Rs >> Cs >> S;
        cin >> P >> Q;

        matrix.assign(R, vector<char>(C));
        vis.assign(R, vector<int>(C));

        for (int j = 0; j < R; j++) {
            for (int k = 0; k < C; k++) {
                cin >> matrix[j][k];
            }
        }

        cout.setf(ios::fixed);
        cout << "Case #" << i << ": " << setprecision(10) << solve() << endl;

        cerr << "Case #" << i << endl;
    }

    cerr << "Time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;

    return 0;
}
