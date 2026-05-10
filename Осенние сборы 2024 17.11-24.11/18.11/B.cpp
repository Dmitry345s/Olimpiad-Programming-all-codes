#include<bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

const int INF = 1e9;
const int MAX = 1e5, K = 300;
int n;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int k;
    cin >> n >> k;
    vector<int> a(n);
    int maxm = -1;
    vector<vector<int>> b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i]--;
        maxm = max(a[i], maxm);
        b[a[i]].push_back(i);
    }
    return 0;
}
