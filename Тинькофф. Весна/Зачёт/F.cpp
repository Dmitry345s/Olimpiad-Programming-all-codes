#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main() {
    string s;
    cin >> s;
    s += 'T';
    int n = s.size();
    int x, y;
    cin >> x >> y;
    vector<int> a, b;
    int cnt = 0, cnt2 = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == 'T') {
            if (cnt % 2 == 0) {
                a.push_back(cnt2);
            } else {
                b.push_back(cnt2);
            }
            cnt2 = 0;
            cnt += 1;
        } else {
            cnt2 += 1;
        }
    }
    if (b.size() == 0) {
        if (x == a[0] && y == 0) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
        return 0;
    }
    vector<vector<bool>> bag(a.size(), vector<bool> (2 * s.size() + 1, false)), bag2(b.size(), vector<bool> (2 * n + 1, false));
    bag[0][n + a[0]] = true;
    for (int i = 1; i < a.size(); ++i) {
        for (int j = 0; j < n * 2 + 1; ++j) {
            if (bag[i - 1][j]) {
                if (j - a[i] >= 0) {
                    bag[i][j - a[i]] = true;
                }
                if (j + a[i] <= 2 * n) {
                    bag[i][j + a[i]] = true;
                }
            }
        }
    }
    bag2[0][n - b[0]] = true;
    bag2[0][n + b[0]] = true;
    for (int i = 1; i < b.size(); ++i) {
        for (int j = 0; j < n * 2 + 1; ++j) {
            if (bag2[i - 1][j]) {
                if (j - b[i] >= 0) {
                    bag2[i][j - b[i]] = true;
                }
                if (j + b[i] <= 2 * n) {
                    bag2[i][j + b[i]] = true;
                }
            }
        }
    }
    if (bag.back()[x + n] && bag2.back()[y + n]) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}
