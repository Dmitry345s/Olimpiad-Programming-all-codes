#include<bits/stdc++.h>

using namespace std;

int k = 500;
int MAX = 1e5;
int t = 0;
vector<int> a(MAX);
vector<vector<array<int, 3>>> b;
vector<vector<int>> c;
vector<int> del;

void rebuild(int v, int num) {
    int cnt = 0;
    t++;
    for (int i = 0; i < v; ++i) {
        cnt += (int)c.size();
    }
    vector<int> ch;
    for (int i = 0; i < (int)c[v].size(); ++i) {
        if (i == num) continue;
        ch.push_back(c[v][i]);
    }
    //for (int i = 0;)
}

signed main() {
    int n, k2;
    cin >> n >> k2;
    c.resize((n + k - 1) / k);
    b.resize((n + k - 1) / k);
    del.resize(((n + k - 1) / k));
    for (int i = 0 i < (int)b.size(); ++i) {
        b[i].resize(k2);
    }
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        c[i / k].push_back(a[i]);
        if (a[i] > b[i / k][i % k2].first) {
            b[i / k][i % k2][0] = a[i];
            b[i / k][i % k2][1] = (int)c.size() - 1;
            b[i / k][i % k2][2] = 0;
        }
        del[i / k] = 0;
    }
    for (int i = 0; i < n; ++i) {
        cout << get() << endl;
    }
    return 0;
}
