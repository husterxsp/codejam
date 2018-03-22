//#include <iostream>
//#include <cstdio>
//#include <cmath>
//#include <cstring>
//#include <algorithm>
//#include <string>
//#include <vector>
//#include <stack>
//#include <queue>
//#include <set>
//#include <map>
//#include <sstream>
//#include <complex>
//#include <ctime>
//#include <cassert>
//#include <functional>
//
//using namespace std;
//
//typedef long long ll;
//typedef vector<int> VI;
//typedef pair<int,int> PII;
//
//#define REP(i,s,t) for(int i=(s);i<(t);i++)
//#define FILL(x,v) memset(x,v,sizeof(x))
//
//const int INF = (int)1E9;
//#define MAXN 105
//
//char s[MAXN];
//int main() {
//        freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Practice-Round-2/A-small-practice.in", "r", stdin);
//        freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Practice-Round-2/A-small-practice.out", "w", stdout);
//
//
//    int cs;
//    cin >> cs;
//    REP(csn, 1, cs + 1) {
//        printf("Case #%d: ", csn);
//        //cerr << csn << endl;
//        ll l, r;
//        cin >> s >> l >> r; l--; r--;
//        int n = strlen(s);
//        ll ans = 0;
//        if (l / n == r / n) {
//            REP(i,l%n,r%n+1) ans += s[i] == 'B';
//        } else {
//            REP(i,l%n,n) ans += s[i] == 'B';
//            REP(i,0,r%n+1) ans += s[i] == 'B';
//            ll cnt = 0;
//            REP(i,0,n) cnt += s[i] == 'B';
//            ans += cnt * (r/n-l/n-1);
//        }
//        cout << ans << endl;
//    }
//    return 0;
//}


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>

using namespace std;
//
long I, J;
string S;
//long I = 4391, J = 998016;
//string S = "BBBRRBBRBBBRRBRRRRBRRBRBBBRRRR";

long solve() {

    long len = S.size(), bNum = 0;
    for (long i = 0; i < len; i++) {
        if (S[i] == 'B') bNum++;
    }

    long ret = 0, remainAll = (J - I + 1) % len, remainJ = J % len, remainI = remainAll - remainJ;
    ret = (J - I + 1) / len *  bNum;

    for (long i = 0; i < remainJ; i++) {
        if (S[i] == 'B') ret++;
    }
    for (long i = len - remainI; i < len; i++) {
        if (S[i] == 'B') ret++;
    }

    return ret;
}
int main() {
        freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Practice-Round-2/A-small-practice.in", "r", stdin);
        freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Practice-Round-2/A-small-practice.out", "w", stdout);
        int T, line = 1;
        cin >> T;

        while(T--) {
            cin >> S;
            cin >> I >> J;
            cout << "Case #" << line++ << ": " << solve() << endl;
        }

//    cout << __SIZEOF_DOUBLE__ << endl;
//    cout << LONG_MAX << endl;
    solve();
    return 0;
}
