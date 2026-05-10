#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> z(n);
    z[0] = n;
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r) {
            z[i] = min(z[i - l], r - i + 1);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = z[i] + i - 1;
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << z[i] << " ";
    }
    return 0;
}
