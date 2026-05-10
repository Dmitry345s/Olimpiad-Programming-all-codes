#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5;
vector<int> gl[MAX];

mt19937 rnd(179);

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, d;
    cin >> n >> d;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < d; ++j) {
            int to;
            cin >> to; --to;
            gl[i].push_back(to);
        }
    }
    vector<int> pr(n, -1);
    for (int i = 0; i < n; ++i) {
        int v = i;
        while (v != -1) {
            swap(pr[gl[v][rnd() % d]], v);
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << pr[i] + 1 << " " << i + 1 << endl;
    }
    return 0;
}
