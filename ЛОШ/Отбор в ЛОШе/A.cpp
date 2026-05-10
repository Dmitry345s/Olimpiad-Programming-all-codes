#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'b') {
            cnt++;
        }
    }
    long long cnt2 = 0, ans = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'a') {
            ans += cnt - cnt2;
        } else {
            cnt2++;
        }
    }
    cout << ans << endl;
}
