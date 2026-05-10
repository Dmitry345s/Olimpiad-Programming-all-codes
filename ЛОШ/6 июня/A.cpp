#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main() {
    int n;
    cin >> n;
    string s, _;
    getline(cin, _);
    getline(cin, s);
    n = s.size();
    int i = 0;
    int ans = 0;
    while (i < n) {
        int p = int(s[i]);
        if ((p >= 97 && p <= 122) || s[i] == '.' || s[i] == ',' || (s[i] - '0' >= 0 && s[i] - '0' <= 9) || s[i] == ' ') {
            while (i < n && ((p >= 97 && p <= 122) || s[i] == '.' || s[i] == ',' || s[i] == ' ' || (s[i] - '0' >= 0 && s[i] - '0' <= 9))) {
                ++i;
                if (i >= n) {
                    break;
                }
                p = int(s[i]);
            }
        } else {
            ans += 1;
            while (i < n && !((p >= 97 && p <= 122) || s[i] == '.' || s[i] == ',' || (s[i] - '0' >= 0 && s[i] - '0' <= 9))) {
                ++i;
                if (i >= n) {
                    break;
                }
                p = int(s[i]);
            }
        }
    }
    cout << n + ans << endl;
    return 0;
}
