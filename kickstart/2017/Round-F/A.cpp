递归解， N=10000，栈溢出
改成循环 AC

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
bool solve(vector<int> a) {
    vector<int> b, c;
    int len = a.size();
    if (len <= 2) return true;

    int pivot = (len - 1) / 2, p = a[pivot];
    for (int i = 0; i < len; i++) {
        if (i == pivot) continue;

        if (a[i] <= p) b.push_back(a[i]);
        else c.push_back(a[i]);

        if (!b.empty() && !c.empty()) return false;
    }

    if (!b.empty()) return solve(b);
    return solve(c);
}
int main() {
    clock_t tStart = clock();
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-F/A-large-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-F/A-large-practice.out", "w", stdout);
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> N;
        vector<int> arr(N);
        for (int j = 0; j < N; j++) {
            cin >> arr[j];
        }
        cout << "Case #" << i << ": " << (solve(arr) ? "YES" : "NO") << endl;
    }
    cerr << "Time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    return 0;
}

------

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

vector<int> arr;
multiset<int> arrSet;

bool solve() {
    while (1) {
        if (arr.size() <= 2) return true;

        int pivot = (arr.size() - 1) / 2, p = arr[pivot];
        if (p == *arrSet.begin()) {
            arrSet.erase(arrSet.begin());
            arr.erase(arr.begin() + pivot);
            continue;
        }
        if (p == *--arrSet.end()) {
            arrSet.erase(--arrSet.end());
            arr.erase(arr.begin() + pivot);
            continue;
        }
        return false;
    }
}

int main() {
    clock_t tStart = clock();
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-F/A-large-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-F/A-large-practice.out", "w", stdout);
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> N;

        arr.assign(N, 0);
        arrSet.clear();

        for (int j = 0; j < N; j++) {
            cin >> arr[j];
            arrSet.insert(arr[j]);
        }

        cout << "Case #" << i << ": " << (solve() ? "YES" : "NO") << endl;
    }
    cerr << "Time taken:" << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;
    return 0;
}
