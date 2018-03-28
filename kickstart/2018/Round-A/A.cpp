/*
 寻找离的最近的每一位都是偶数的数
 注意观察找出规律。。调了好久结果写的这么简单。。
 */

#include <bits/stdc++.h>
#define ll long long

using namespace std;
ll N;
ll ret;

void add(string s, int pos) {
    s[pos] = s[pos] + 1;

    for (int i = pos + 1; i < s.size(); i++) s[i] = '0';

    ret = min(ret, abs(N - stoll(s)));
}
void reduce(string s, int pos) {
    s[pos] = s[pos] - 1;

    for (int i = pos + 1; i < s.size(); i++) s[i] = '8';

    ret = min(ret, abs(N - stoll(s)));

}
void solve(string s, int pos) {
    if (pos == s.size()) {
        ret = 0;
        return;
    }

    int bit = s[pos] - '0';
    if (bit % 2 == 0) solve(s, pos + 1);

    else if (bit == 9) reduce(s, pos);
    else {
        add(s, pos);
        reduce(s, pos);
    }
}

int main() {
    clock_t tStart = clock();
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2018/Round-A/A-large-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2018/Round-A/A-large-practice.out", "w", stdout);
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> N;

        ret = LLONG_MAX;
        solve(to_string(N), 0);

        cout << "Case #" << i << ": " << ret << endl;

//        cerr << "Case #" << i << " time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    }

    cerr << "Time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;

    return 0;
}
