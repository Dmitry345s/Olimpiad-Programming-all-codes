#include<bits/stdc++.h>

using namespace std;

signed main() {
    int r;
    cin >> r;
    int t;
    cin >> t;
    while (t--) {
        if (r == 1) {
            int n;
            cin >> n;
            vector<pair<int, int>> ch(7);
            for (int i = 0; i < 7; ++i) {
                int x, y;
                cin >> x >> y;
                ch[i] = {x, y};
            }
            vector<vector<int>> a(n, vector<int> (n));
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    for (int l = 6; l >= 0; --l) {
                        a[i][j] *= 4;
                        if (ch[l].first - i > 0) {
                            a[i][j] += 3;
                            continue;
                        }
                        if (ch[l].first - i < 0) {
                            a[i][j] += 2;
                            continue;
                        }
                        if (ch[l].second - j > 0) {
                            a[i][j] += 1;
                            continue;
                        }
                    }
                    a[i][j]++;
                }
            }
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    cout << a[i][j] << " ";
                }
                if (i != n - 1) {
                    cout << endl;
                }
            }
            cout << endl;
        } else {
            for (int _ = 0; _ < 7; ++_) {
                while (true) {
                    vector<vector<int>> a(3, vector<int> (3));
                    for (int i = 0; i < 3; ++i) {
                        for (int j = 0; j < 3; ++j) {
                            cin >> a[i][j];
                            a[i][j]--;
                        }
                    }
                    int g1 = (a[1][1] >> (2 * _)) % 4;
                    int g2 = (a[1][0] >> (2 * _)) % 4;
                    if (g1 == 0 && g2 == 1) {
                        cout << "S" << endl;
                        break;
                    }
                    if (g1 == 0) {
                        cout << "L" << endl;
                    } else if (g1 == 1) {
                        cout << "R" << endl;
                    } else if (g1 == 2) {
                        cout << "U" << endl;
                    } else if (g1 == 3) {
                        cout << "D" << endl;
                    }
                }
            }
        }
    }
    return 0;
}
