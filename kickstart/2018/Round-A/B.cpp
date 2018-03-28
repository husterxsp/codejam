
/*
 一开始想错了。以为前面的轮次只有选到最大值才保留。但是参考analysis，选到的值比平均值大就可以保留。。。
 */

1. rate 计算会溢出。

#include <bits/stdc++.h>
#define ll long long
#define ld long double

using namespace std;

int N, K;
vector<ld> v;

ld solve() {
    sort(v.begin(), v.end());

    vector<ld> sum(N);
    sum[0] = v[0];
    for (int i = 1; i < N; i++) {
        sum[i] = sum[i - 1] + v[i];
    }

    ld p = lower_bound(v.begin(), v.end(), sum[N - 1] / N) - v.begin();
    ld sumLeft = sum[p - 1], sumRight = sum[N - 1] - sum[p - 1];

    ld ret = 0;
    ld rate = 1;
    for (int i = 0; i < K; i++) {
        ret += rate * sumRight / N;

        rate *= p / N;
    }
    ret += rate * sum[N - 1] / N;

    return ret;
}

int main() {
    clock_t tStart = clock();
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2018/Round-A/B-large-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2018/Round-A/B-large-practice.out", "w", stdout);
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> N >> K;
        v.assign(N, 0);

        for (int j = 0; j < N; j++) cin >> v[j];

        cout << "Case #" << i << ": " << setprecision(15) << solve() << endl;

        // cerr << "Case #" << i << " time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    }

    cerr << "Time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;

    return 0;
}


2.
。。。有毒，
5
4 0
1 2 3 4
3 1
1 10 1
3 15
80000 80000 80000
1 1
10
5 3
16 11 7 4 1

#include <bits/stdc++.h>
#define ll long long
#define ld long double

using namespace std;

int N, K;
vector<ld> v;

ld solve() {
    sort(v.begin(), v.end());

    vector<ld> sum(N);
    sum[0] = v[0];
    for (int i = 1; i < N; i++) {
        sum[i] = sum[i - 1] + v[i];
    }

    ld average = sum[N - 1] / N;

    ld p = lower_bound(v.begin(), v.end(), average) - v.begin();

    if (p == 0) return average;


    ld sumLeft = sum[p - 1], sumRight = sum[N - 1] - sum[p - 1];

    if (K == 0) return sum[N - 1] / N;

    vector<ld> avg(K + 1);

    avg[0] = sumRight / N;

    for (int i = 1; i < K; i++) {
        avg[i] = (p / N) * avg[i - 1];
    }

    avg[K] = sum[N - 1] / N;
    for (int i = 0; i < K; i++) avg[K] *= (p / N);

    ld ret = 0;
    for (int i = 0; i <= K; i++) ret += avg[i];

    return ret;
}

int main() {
    clock_t tStart = clock();
        freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2018/Round-A/B-large-practice.in", "r", stdin);
        freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2018/Round-A/B-large-practice.out", "w", stdout);
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> N >> K;
        v.assign(N, 0);

        for (int j = 0; j < N; j++) cin >> v[j];

        cout << "Case #" << i << ": " << setprecision(15) << solve() << endl;

        // cerr << "Case #" << i << " time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    }

    cerr << "Time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;

    return 0;
}
