#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> p(n);
    p[0] = 0;
    cout << 0 << " ";
    for (int i = 1; i < n; ++i) {
        int j = p[i - 1];
        while (j > 0 && s[j] != s[i]) {
            j = p[j - 1];
        }
        if (s[i] == s[j]) {
            p[i] = j + 1;
        }
        cout << p[i] << " ";
    }
    return 0;
}
