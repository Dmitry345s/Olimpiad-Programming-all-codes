#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main() {
    string s, t;
    cin >> s >> t;
    int n = s.size();
    string q = t + "#" + s, p = s + "#" + t;
    vector<int> z_s(2 * n + 1);
    int l = 0, r = 0;
    for (int i = 0; i < 2 * n + 1; ++i) {
        if (i <= r) {
            z_s[i] = min(z_s[i - l], r - i + 1);
        }
        while (i + z_s[i] < 2 * n + 1 && q[z_s[i]] == q[z_s[i] + i]) {
            ++z_s[i];
        }
        if (z_s[i] + i - 1 > r) {
            l = i;
            r = z_s[i] + i - 1;
        }
    }
    vector<int> z_t(2 * n + 2);
    l = 0, r = 0;
    for (int i = 0; i < 2 * n + 1; ++i) {
        if (i <= r) {
            z_t[i] = min(z_t[i - l], r - i + 1);
        }
        while (i + z_t[i] < 2 * n + 1 && p[z_t[i]] == p[z_t[i] + i]) {
            ++z_t[i];
        }
        if (z_t[i] + i - 1 > r) {
            l = i;
            r = z_t[i] + i - 1;
        }
    }
    for (int i = n + 1; i < 2 * n + 1; ++i) {
        if (z_s[i] + z_t[2 * n + 1 - (i - n - 1)] == n) {
            cout << z_s[i] % n << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}
