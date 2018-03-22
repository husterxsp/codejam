small dataset: 但是以下解法只能跑出小数据集的前10个case...

#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <unordered_set>

using namespace std;

int N, K, A1, B1, C, D, E1, E2, F;
vector<vector<int>> matrix;
vector<int> A;
vector<int> B;

int calcSum(int a, int b, int c, int d, vector<vector<int>> sumRow) {
    int ret = 0;
    for (int i = a; i <= c; i++) {
        ret += sumRow[i][d] - sumRow[i][b - 1];
    }
    return ret;
}

int solve() {
    vector<vector<int>> sumRow(N + 1, vector<int>(N + 1));
    vector<vector<int>> sumAll(N + 1, vector<int>(N + 1));

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            sumRow[i][j] = sumRow[i][j - 1] + matrix[i][j];
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            sumAll[i][j] = calcSum(1, 1, i, j, sumRow);
        }
    }

    vector<int> sumMatrix;
//    priority_queue<int, vector<int>, greater<int>> q;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {

            for (int m = i; m <= N; m++) {
                for (int n = j; n <= N; n++) {
                    int tmp = sumAll[m][n] - sumAll[i-1][n] - sumAll[m][j-1] + sumAll[i - 1][j - 1];

                    sumMatrix.push_back(tmp);
//                    if (q.size() < K) q.push(tmp);
//                    else if (q.top() < tmp) {
//                        q.pop();
//                        q.push(tmp);
//                    }
//                    sumMatrix.push_back(calcSum(i,j,m,n,sumRow));
                }
            }
        }
    }
    sort(sumMatrix.begin(), sumMatrix.end(), [](int a, int b){return a > b;});
    return *(sumMatrix.begin() + K - 1);
//    return 0;
//    return q.top();
}
int main() {
    clock_t tStart = clock();
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-D/B-small-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-D/B-small-practice.out", "w", stdout);
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> N >> K >> A1 >> B1 >> C >> D >> E1 >> E2 >> F;

        matrix.assign(N + 1, vector<int>(N + 1));
        A.assign(N + 1, 0);
        B.assign(N + 1, 0);

        A[1] = A1;
        B[1] = B1;

        int x = A1, y = B1, r = 0, s = 0;
        for (int j = 2; j <= N; j++) {
            int _x, _y, _r, _s;
            _x = ( C*x + D*y + E1 ) % F;
            _y = ( D*x + C*y + E2 ) % F;

            _r = ( C*r + D*s + E1 ) % 2;
            _s = ( D*r + C*s + E2 ) % 2;

            x=_x; y=_y; r=_r; s=_s;

            A[j] = (r % 2 == 0 ? 1 : -1) * x;
            B[j] = (s % 2 == 0 ? 1 : -1) * y;
        }

        for (int j = 1; j <= N; j++) {
            for (int k = 1; k <= N; k++) {
                matrix[j][k] = A[j] * B[k];
            }
        }

        cout << "Case #" << i << ": " << solve() << endl;
    }
    cerr << "Time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    return 0;
}
