solve1 暴力解
分为两边相等，三边相等两种情况

恩，注意读题题目明确要求exactly一对平行边相等，所以四边相等的情况不存在（平行四边形，两对相等）
另外就是注意用long避免溢出

solve1暴力解，large datasets 380s
solve 用sum数组和二分来优化，思路和solve1一样，large datasets 2s

#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <unordered_set>

using namespace std;

int N;
vector<long> len;
long solve1() {
    map<long, long> m;
    set<long> s;
    for (int i = 0; i < N; i++) {
        m[len[i]]++;
        s.insert(len[i]);
    }

    long ret = 0;
    for (long v : s) {
        long n = m[v];
        // if (n >= 4) {
        //            ret += n * (n - 1) * (n - 2) * (n - 3) / 24;
        // }
        if (n >= 3) {
            long v1 = n * (n - 1) * (n - 2) / 6, v2 = 0;
            for (long tmpV : s) {
                if (tmpV < v || (tmpV > v && 3 * v > tmpV)) v2 += m[tmpV];
            }
            ret += v1 * v2;
        }
        if (n >= 2) {
            long v1 = n * (n - 1) / 2, v2 = 0;
            for (long it1 : s) {
                for (long it2 : s) {
                    if (it1 == v || it2 == v || it1 >= it2) continue;
                    if (it1 + 2 * v > it2) {
                        v2 += m[it1] * m[it2];
                    }
                    else break;
                }
            }
            ret += v1 * v2;
        }
    }

    return ret;
}

long solve() {
    map<long, long> m;
    for (int i = 0; i < N; i++) m[len[i]]++;

    vector<long> num;
    vector<long> cnt;


    for (auto pair : m) {
        num.push_back(pair.first);
        cnt.push_back(pair.second);
    }
    int numLen = num.size();
    vector<long> sum(numLen);

    sum[0] = cnt[0];
    for (int i = 1; i < num.size(); i++) {
        sum[i] = sum[i - 1] + cnt[i];
    }

    long ret = 0;
    for (int i = 0; i < numLen; i++) {
        long n = cnt[i];

        if (n >= 3) {
            long v1 = n * (n - 1) * (n - 2) / 6, v2 = 0;
            auto low = lower_bound(num.begin() + i, num.end(), 3*num[i]);

            low = prev(low);

            v2 = sum[low - num.begin()] - cnt[i];

            ret += v1 * v2;
        }
        if (n >= 2) {
            long v1 = n * (n - 1) / 2, v2 = 0;
            for (int j = 0; j < numLen; j++) {
                if (j == i) continue;

                auto low = lower_bound(num.begin() + j + 1, num.end(), num[j] + 2*num[i]);
                low = prev(low);

                // 找不到合适的
                if (distance(num.begin(), low) <= j) continue;

                int tmp = sum[low - num.begin()] - sum[j];

                if (j < i && i <= *low) tmp -= cnt[i];
                v2 += cnt[j] * tmp;
            }
            ret += v1 * v2;
        }
    }

    return ret;
}

int main() {
    clock_t tStart = clock();
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-E/B-large-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-E/B-large-practice.out", "w", stdout);
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> N;

        len.assign(N, 0);
        for (int j = 0; j < N; j++) {
            cin >> len[j];
        }
        cout << "Case #" << i << ": " << solve() << endl;
    }
    cerr << "Time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    return 0;
}
