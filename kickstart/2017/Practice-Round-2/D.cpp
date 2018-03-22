#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>

using namespace std;

long solve(vector<vector<long>> intervals, long N) {
    
}

int main() {
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Practice-Round-2/C-large-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Practice-Round-2/C-large-practice.out", "w", stdout);
    int T, line = 1;
    cin >> T;

    long N, L1, R1, A, B, C1, C2, M;
    while(T--) {
        cin >> N >> L1 >> R1 >> A >> B >> C1 >> C2 >> M;
        cerr << "test:" << T << endl;

        vector<vector<long>> intervals(N, vector<long>(2));

        intervals[0] = {L1, R1};
        for (int i = 1; i < N; i++) {
            vector<long> pre = intervals[i - 1];
            vector<long> cur(2);
            cur[0] = (A * pre[0] + B * pre[1] + C1) % M;
            cur[1] = (A * pre[0] + B * pre[1] + C2) % M;

            intervals.push_back(pre);
        }

        cout << "Case #" << line++ << ": " << solve(intervals, N) << endl;
    }

    return 0;
}
