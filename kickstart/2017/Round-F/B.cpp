有点贪心的意味

#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <unordered_set>

using namespace std;

int energy, honor, N;

vector<int> skill;
void solve() {
    sort(skill.begin(), skill.end());

    int l = 0, r = skill.size() - 1, tmpH;
    while (l <= r) {
        if (energy > skill[l]) {
            energy -= skill[l];
            l++;

            tmpH++;
            honor = max(honor, tmpH);
        }
        else {
            energy += skill[r];
            r--;

            if (tmpH == 0) return;
            tmpH--;
        }
    }
}

int main() {
    clock_t tStart = clock();
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-F/B-large-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-F/B-large-practice.out", "w", stdout);
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> energy >> N;

        honor = 0;
        skill.assign(N, 0);
        for (int j = 0; j < N; j++) {
            cin >> skill[j];
        }

        solve();
        cout << "Case #" << i << ": " << honor << endl;
    }
    cerr << "Time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    return 0;
}
