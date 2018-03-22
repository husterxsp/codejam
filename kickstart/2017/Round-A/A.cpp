/**

1.
    参考：http://blog.csdn.net/dormousenone/article/details/60559460
    公式： ret = (c - r) * (r^3 - r) / 6  + (r^4 - r^2) / 12
2. http://blog.csdn.net/lzedo/article/details/60742524

主要参考 2 推公式吧...

碰见这种大数题还是绕着C++
发现python这样的动态语言的好处了，不会有溢出的问题，
另外java 的BigInteger 也挺好。

最后，公式是记不住了，实际A题的时候，可以 用2中的递推公式，写个for循环。。。
*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>

const int mod = 1e9 + 7;

using namespace std;

int main() {
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-A/A-small-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-A/A-small-practice.out", "w", stdout);
    int T, line = 1;
    cin >> T;

    while(T--) {
        long r, c;
        cin >> r >> c;

        if (r > c) swap(r, c);

        long ret = (c - r) * (r * r * r / 6 - r / 6) + (r * r * r * r / 12 - r * r / 12);

        cout << "Case #" << line++ << ": " << ret % mod << endl;
    }

    return 0;
}
