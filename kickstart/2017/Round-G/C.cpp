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

int N, M;

vector<vector<int>> matrix;

int solve() {
    vector<vector<int>> sum(N + 1, vector<int>(M + 1, INT_MAX));

    
    return ret;
}

int main() {
    clock_t tStart = clock();
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-G/C-small-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-G/C-small-practice.out", "w", stdout);
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> N >> M;

        matrix.assign(N + 1, vector<int>(M + 1, INT_MAX));

        for (int j = 1; j <= N; j++) {
            for (int k = 1; k <= M; k++) {
                cin >> matrix[j][k];
            }
        }

        cout << "Case #" << i << ": " << solve() << endl;

        cerr << "Case #" << i << " time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    }

    cerr << "Time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;

    return 0;
}
