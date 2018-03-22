easy, 两层循环

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>

const int mod = 1e9 + 7;

using namespace std;

string decrypted;
int success = 0;

string solve() {

    int size = decrypted.size();
    string messages(size, '0'), ret;

    messages[1] = decrypted[0];
    for (int i = 0; i < 26; i++) {
        messages[0] = 'A' + i;
        for (int j = 1; j < size - 1; j++) {
            letter[j + 1] = decrypted[j] - 'A' - (letter[j - 1] - 'A');
            if (letter[j + 1] < 'A') letter[j + 1] += 26;
        }
        if (decrypted[size - 1] == letter[size - 2]) {
            if (success) return "AMBIGUOUS";
            else {
                success = 1;
                ret = message;
            }
        }
    }

    return ret;
}
int main() {
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-C/A-small-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Round-C/A-small-practice.out", "w", stdout);
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> decrypted;
        cout << "Case #" << i << ": " << solve() << endl;
    }

    return 0;
}
