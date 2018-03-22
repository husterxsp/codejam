/**
    给定一组字符串，找到其中含有字母最多的一个字符串
    思路：用map对每个字符串的字母进行统计
*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>

using namespace std;
string countryLeader(vector<string> persons) {
    map<string, int> myMap;
    for (string s : persons) {
        unordered_set<char> tmp;
        for (char c : s) {
            if (c != ' ') tmp.insert(c);
        }
        myMap[s] = tmp.size();
    }
    string ret = "";
    int letters = 0;
    for (auto itor : myMap) {
        if (itor.second > letters) {
            letters = itor.second;
            ret = itor.first;
        }
    }
    return ret;
}
int main() {
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Practice-Round/A-large-practice.in", "r", stdin);
    freopen("/Users/xushaopeng/Desktop/codejam/kickstart/2017/Practice-Round/A-large-practice.out", "w", stdout);
    int T, line = 1;
    cin >> T;

    while(T--) {
        int N;
        cin >> N;

        vector<string> persons(N);
        // cin and getline skipping input
        // https://stackoverflow.com/questions/10553597/cin-and-getline-skipping-input
        // https://stackoverflow.com/questions/5739937/using-getlinecin-s-after-cin
        cin.ignore (numeric_limits<streamsize>::max(), '\n');

        while (N--) getline(cin, persons[N]);

        cout << "Case #" + to_string(line++) + ": " + countryLeader(persons) << endl;
    }

    return 0;
}
