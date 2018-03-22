Small dataset: dfs

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <unordered_set>

using namespace std;

int N, Q;
vector<bitset<50>> answer(3);
vector<int> score(3);
vector<bitset<50>> possibleRight;

bool valid() {
    return true;
}

void dfs(bitset<50> ans, int wrong, int pos) {
    if (wrong == 0) {
        if (valid()) possibleRight.push_back(ans);
        return;
    }

    for (int i = pos; i <= Q - wrong; i++) {
        ans.flip(i);
        dfs(ans, wrong - 1, i + 1);
        ans.flip(i);
    }
}

int solve() {
    int wrong = Q - score[0];
    dfs(answer[0], wrong, 0);

    int ret = 0;
    for (int i = 0; i < possibleRight.size(); i++) {
        bitset<50> tmp(possibleRight[i] ^ answer[1]);
        ret = max(ret, Q - (int)tmp.count());
    }
    return ret;
}
int main() {
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-C/C-small-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-C/C-small-practice.out", "w", stdout);
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> N >> Q;

        fill(answer.begin(), answer.end(), bitset<50>(0));
        fill(score.begin(), score.end(), 0);
        possibleRight.clear();

        for (int j = 0; j <= N; j++) {
            string tmp = "";
            cin >> tmp;
            for (int k = 0; k < tmp.size(); k++) {
                if (tmp[k] == 'T') tmp[k] = '1';
                else tmp[k] = '0';
            }
            answer[j] = bitset<50>(tmp);
        }
        for (int j = 0; j < N; j++) cin >> score[j];

        cout << "Case #" << i << ": " << solve() << endl;
    }

    return 0;
}

Large dataset: dp。set集合中去掉了很多重复的元素。待再看和一般的dp区别，及dfs如何优化。

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <unordered_set>

using namespace std;

int N, Q;
vector<string> answer(3);
vector<int> score(3);

int solve() {
    set<vector<int>> s;
    if (N == 1) s.insert({0,0});
    if (N == 2) s.insert({0,0,0});

    for (int i = 0; i < Q; i++) {
        set<vector<int>> tmpS;
        // question[i] is T
        for (auto v : s) {
            for (int j = 0; j <= N; j++) {
                if (answer[j][i] == 'T') v[j]++;
            }
            tmpS.insert(v);
        }
        // question[i] is F
        for (auto v : s) {
            for (int j = 0; j <= N; j++) {
                if (answer[j][i] == 'F') v[j]++;
            }
            tmpS.insert(v);
        }
        s = tmpS;
    }

    int ret = 0;
    for (auto v : s) {
        bool valid = true;
        for (int i = 0; i < N; i++) {
            if (score[i] != v[i]) {
                valid = false;
                break;
            }
        }
        if (valid) ret = max(ret, v[N]);
    }
    return ret;
}
int main() {
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-C/C-large-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-C/C-large-practice.out", "w", stdout);
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> N >> Q;

        fill(answer.begin(), answer.end(), "");
        fill(score.begin(), score.end(), 0);

        for (int j = 0; j <= N; j++) cin >> answer[j];
        for (int j = 0; j < N; j++) cin >> score[j];

        cout << "Case #" << i << ": " << solve() << endl;
    }

    return 0;
}
