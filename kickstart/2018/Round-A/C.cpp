/**
 优化了好多large依旧超时。。。
 */


/**

1. 一开始将string 用dp数组的存着，依旧很慢, large 无法AC
*/
#include <bits/stdc++.h>
#define ll long long
#define ld long double

using namespace std;
struct word {
    int len;
    char first, last;
    map<char, int> m;
    word(int len, char first, char last, map<char, int> m) : len(len), first(first), last(last), m(m) {}
};
ll l, n, a, b, c, d;
string s, s1, s2;
map<char, vector<ll>> sMap;

struct KeyHash {
    std::size_t operator()(const word& k) const {
        return k.first ^ k.last ^ k.len;
    }
};
struct KeyEqual {
    bool operator()(const word& a, const word& b) const {
        return a.first == b.first && a.last == b.last && a.len == b.len && a.m == b.m;
    }
};
unordered_map<word, int, KeyHash, KeyEqual> wordMap;
vector<map<char, int>> dp;

bool mapEqual(int i, int j, map<char, int> m) {
    map<char, int> tmp = dp[j];

    if (i > 0) {
        for (char c = 'a'; c <= 'z'; c++) {
            tmp[c] -= dp[i - 1][c];
        }
    }
    for (char c = 'a'; c <= 'z'; c++) {
        if (tmp[c] != m[c]) return false;
    }

    return true;
}
ll solve() {
    ll ret = 0;

    int cnt = 0;
    for (auto pair : wordMap) {
        cerr << wordMap.size() << endl;
        cerr << cnt++ << endl;
        word w = pair.first;
        int len = w.len;

        for (int j = 0; j < sMap[w.first].size(); j++) {
            int last = sMap[w.first][j] + len - 1;

            if (last >= s.size()) break;

            if (s[last] == w.last) {
                if (mapEqual(sMap[w.first][j], last, w.m)) {
                    ret += wordMap[w];
                    break;
                }
            }
//            cerr << j << endl;
        }
    }

    return ret;
}

int main() {
    clock_t tStart = clock();
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2018/Round-A/C-large-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2018/Round-A/C-large-practice.out", "w", stdout);
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> l;

        wordMap.clear();
        sMap.clear();

        string str;
        for (int j = 0; j < l; j++) {
            cin >> str;

            word w = word(str.size(), str[0], str.back(), map<char, int>());

            map<char, int> m;
            for (int k = 0; k < str.size(); k++) {
                m[str[k]]++;
            }
            w.m = m;
            wordMap[w]++;
        }

        cin >> s1 >> s2 >> n >> a >> b >> c >> d;

        s = s1 + s2;

        ll x1 = s1[0] - 'a' + 97, x2 = s2[0] - 'a' + 97;

        sMap[s1[0]].push_back(0);
        sMap[s2[0]].push_back(1);

        /**
         。。。
         题目中写的
         x1 = ord(S1), x2 = ord(S2).
         xi = ( A * xi-1 + B * xi-2 + C ) modulo D.

         那么一开始计算的应该是 A * x2 + B * X1 。。。而不是 A * x1 + B * x2

         另外注意整型溢出
         */
        for (int j = 2; j < n; j++) {
            ll x = (a * x2 + b * x1 + c) % d;

            char tmp = 'a' + x % 26;
            s += tmp;

            x1 = x2;
            x2 = x;

            sMap[tmp].push_back(j);
        }

        int sLen = s.size();
        dp.assign(sLen, map<char, int>());

        dp[0] = map<char, int>();
        dp[0][s[0]]++;
        for (int j = 1; j < s.size(); j++) {
            dp[j] = dp[j - 1];
            dp[j][s[j]]++;
        }

        cout << "Case #" << i << ": " << solve() << endl;

        cerr << "Case #" << i << " time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    }

    cerr << "Time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;

    return 0;
}

/*
    以下代码small也有错误。。
*/

/**
 优化了好多large依旧超时。。。
 */

#include <bits/stdc++.h>
#define ll long long
#define ld long double

using namespace std;
struct word {
    int len;
    char first, last;
    map<char, int> m;
    word(int len, char first, char last, map<char, int> m) : len(len), first(first), last(last), m(m) {}
};
ll l, n, a, b, c, d;
string s, s1, s2;

struct KeyHash {
    std::size_t operator()(const word& k) const {
        return k.first ^ k.last ^ k.len;
    }
};
struct KeyEqual {
    bool operator()(const word& a, const word& b) const {
        return a.first == b.first && a.last == b.last && a.len == b.len && a.m == b.m;
    }
};
unordered_map<word, int, KeyHash, KeyEqual> wordMap;
vector<map<char, int>> dp;

ll solve() {
    ll ret = 0;

    int cnt = 0;
    for (auto pair : wordMap) {
        cerr << wordMap.size() << endl;
        cerr << cnt++ << endl;
        word w = pair.first;
        int len = w.len;

        map<char, int> tmpMap;
        for (char c = 'a'; c <= 'z'; c++) tmpMap[c] = tmpMap[c] || 0;
        for (int i = 0; i < len; i++) tmpMap[s[i]]++;

        if (tmpMap == w.m) {
            ret += pair.second;
            continue;
        }

        for (int j = len; j < s.size(); j++) {
            tmpMap[s[j]]++;
            tmpMap[s[j - len]]--;

            if (tmpMap == w.m) {
                ret += pair.second;
                break;
            }
        }
    }

    return ret;
}

int main() {
    clock_t tStart = clock();
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2018/Round-A/C-small-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2018/Round-A/C-small-practice.out", "w", stdout);
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> l;

        wordMap.clear();

        string str;
        for (int j = 0; j < l; j++) {
            cin >> str;

            word w = word(str.size(), str[0], str.back(), map<char, int>());

            map<char, int> m;
            for (int k = 0; k < str.size(); k++) {
                m[str[k]]++;
            }
            for (char c = 'a'; c <= 'z'; c++) m[c] = m[c];
            w.m = m;
            wordMap[w]++;
        }

        cin >> s1 >> s2 >> n >> a >> b >> c >> d;

        s = s1 + s2;

        ll x1 = s1[0] - 'a' + 97, x2 = s2[0] - 'a' + 97;

        /**
         。。。
         题目中写的
         x1 = ord(S1), x2 = ord(S2).
         xi = ( A * xi-1 + B * xi-2 + C ) modulo D.

         那么一开始计算的应该是 A * x2 + B * X1 。。。而不是 A * x1 + B * x2

         另外注意整型溢出
         */
        for (int j = 2; j < n; j++) {
            ll x = (a * x2 + b * x1 + c) % d;

            char tmp = 'a' + x % 26;
            s += tmp;

            x1 = x2;
            x2 = x;

        }

        cout << "Case #" << i << ": " << solve() << endl;

        cerr << "Case #" << i << " time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    }

    cerr << "Time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;

    return 0;
}
