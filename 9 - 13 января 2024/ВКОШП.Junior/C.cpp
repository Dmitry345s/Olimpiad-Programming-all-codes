#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main() {
    long long n, m, a, b, c;
    cin >> n;
    string s;
    cin >> s;
    vector<int> v(26, 0);
    for (int i = 0; i < n; i++) {
        if (v[(int)s[i] - 97] > 0) {
            cout << "NO" << endl;
            return 0;
        }
        v[(int)s[i] - 97] += 1;
    }
    cout << "YES" << endl;
    return 0;
}
