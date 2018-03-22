动态规划，01背包

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>

using namespace std;
int n, sightsee, latest;
vector<int> start, freq, duration;

int ceil(int a, int b) {
    return a / b + (a % b == 0 ? 0 : 1);
}

struct compare {
    bool operator() (const vector<int>& a, const vector<int>& b) const {
        return a[1] == b[1] ? a[0] < b[0] : a[1] < b[1];
    }
};

//auto cmp = [](vector<int> a, vector<int> b) {
//    return a[1] == b[1] ? a[0] < b[0] : a[1] < b[1];
//};
//set<int, decltype(cmp)> s(cmp);

void help(set<vector<int>, compare>& s) {
    if (s.empty()) return;
    vector<int> cur = *s.begin();
    set<vector<int>, compare> tmpS{cur};
    for (auto v : s) {
        if (v[1] > cur[1]) {
            cur = v;
            tmpS.insert(cur);
        }
    }
    s = tmpS;
}

string solve() {
    set<vector<int>, compare> s{{0, 0}};

    for (int i = 0; i < n - 1; i++) {
        set<vector<int>, compare> tmpS;
        // visit i
        for (auto v : s) {
            v[0] += sightsee;
            if (v[0] <= start[i]) v[0] =  start[i] + duration[i];
            else {
                int x = ceil(v[0] - start[i], freq[i]);
                v[0] = start[i] + x * freq[i] + duration[i];
            }
            v[1]++;
            if (v[0] <= latest) tmpS.insert(v);
        }
        // don't visit i
        for (auto v : s) {
            if (v[0] <= start[i]) v[0] =  start[i] + duration[i];
            else {
                int x = ceil(v[0] - start[i], freq[i]);
                v[0] = start[i] + x * freq[i] + duration[i];
            }
            if (v[0] <= latest) tmpS.insert(v);
        }
        s = tmpS;
        help(s);
    }

    if (s.empty()) return "IMPOSSIBLE";
    return to_string((*s.rbegin())[1]);
}
int main() {
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-D/A-large-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-D/A-large-practice.out", "w", stdout);
    int T;
    cin >> T;

    int s, f, d;
    for (int i = 1; i <= T; i++) {
        cin >> n >> sightsee >> latest;

        start.clear();
        freq.clear();
        duration.clear();

        for (int j = 0; j < n - 1; j++) {
            cin >> s >> f >> d;
            start.push_back(s);
            freq.push_back(f);
            duration.push_back(d);
        }
        cout << "Case #" << i << ": " << solve() << endl;
    }

    return 0;
}
