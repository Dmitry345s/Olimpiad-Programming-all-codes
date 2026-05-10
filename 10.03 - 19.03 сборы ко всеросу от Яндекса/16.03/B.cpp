#include<bits/stdc++.h>

using namespace std;

vector<pair<int, int>> go1, go2;
int n, m;

pair<int, int> sl1(int xc, int yc) {
    int x = 0, y = 0;
    for (int i = 0; i < (int)go1.size(); ++i) {
        int x1 = x + go1[i].first, y1 = y + go1[i].second;
        if (x1 == xc && y1 == yc) continue;
        if (0 <= x1 && x1 < n && 0 <= y1 && y1 < m) {
            x = x1;
            y = y1;
        }
    }
    return {x, y};
}

pair<int, int> sl2(int xc, int yc) {
    int x = 0, y = 0;
    for (int i = 0; i < (int)go2.size(); ++i) {
        int x1 = x + go2[i].first, y1 = y + go2[i].second;
        if (x1 == xc && y1 == yc) continue;
        if (0 <= x1 && x1 < n && 0 <= y1 && y1 < m) {
            x = x1;
            y = y1;
        }
    }
    return {x, y};
}

void td1(int n1, int m1) {
    if (n1 == 1 && m1 == 1) return;
    if (n1 == 1) {
        for (int i = 0; i < m1 - 1; ++i) {
            go1.push_back({0, 1});
        }
        return;
    }
    if (m1 == 1) {
        for (int i = 0; i < n1 - 1; ++i) {
            go1.push_back({1, 0});
        }
        return;
    }
    for (int i = 0; i < n1 - 1; ++i) {
        go1.push_back({1, 0});
    }
    for (int i = 0; i < m1 - 1; ++i) {
        go1.push_back({0, 1});
    }
    for (int i = 0; i < n1 - 1; ++i) {
        go1.push_back({-1, 0});
    }
    for (int i = 0; i < m1 - 2; ++i) {
        go1.push_back({0, -1});
    }
    if (n1 <= 2) return;
    if (m1 <= 2) return;
    go1.push_back({1, 0});
    td1(n1 - 2, m1 - 2);
}

map<pair<int, int>, char> mp;

signed main() {
    mp[{1, 0}] = 'v';
    mp[{-1, 0}] = '^';
    mp[{0, 1}] = '>';
    mp[{0, -1}] = '<';
    cin >> n >> m;
    td1(m, n);
    go2 = go1;
    go1.clear();
    for (int i = 0; i < (int)go2.size(); ++i) {
        swap(go2[i].first, go2[i].second);
    }
    td1(n, m);
    int x1, y1;
    cout << "? ";
    for (int i = 0; i < (int)go1.size(); ++i) {
        cout << mp[go1[i]];
    }
    cout << endl;
    cin >> x1 >> y1;
    int x2, y2;
    cout << "? ";
    for (int i = 0; i < (int)go2.size(); ++i) {
        cout << mp[go2[i]];
    }
    cout << endl;
    cin >> x2 >> y2;
    map<pair<pair<int, int>, pair<int, int>>, vector<pair<int, int>>> mp2;
    map<pair<int, int>, vector<pair<int, int>>> mp3;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i == 0 && j == 0) continue;
            mp2[{sl1(i, j), sl2(i, j)}].push_back({i, j});
            mp3[sl1(i, j)].push_back({i, j});
        }
    }
    pair<pair<int, int>, pair<int, int>> kes = {{x1, y1}, {x2, y2}};
    for (auto [key, val] : mp3) {
        if ((int)val.size() > 1) {
            for (auto [x, y] : val) {
                cout << x << " " << y << endl;
            }
            cout << "#" << endl;
        }
    }
    return 0;
}
