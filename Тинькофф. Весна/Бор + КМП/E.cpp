#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    string t;
    t = s + "#";
    for (int i = n - 1; i >= 0; --i) {
        t += s[i];
    }
    vector<int> z(2 * n + 1);
    z[0] = 2 * n + 1;
    int l = 0, r = 0;
    for (int i = 1; i < 2 * n + 1; ++i) {
        if (i <= r) {
            z[i] = min(z[i - l], r - i);
        }
        while (i + z[i] < 2 * n + 1 && t[z[i]] == t[z[i] + i]) {
            ++z[i];
        }
        if (z[i] + i > r) {
            l = i;
            r = z[i] + i;
        }
    }
    for (int i = 2 * n; i > n; --i) {
        cout << z[i] << " ";
    }
    return 0;
}
