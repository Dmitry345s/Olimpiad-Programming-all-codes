#include<bits/stdc++.h>

using namespace std;

struct Node {
    int m, sum;
    Node *p = nullptr;
    Node(int m1 = 0) {
        m = m1;
        sum = m1;
    }
};

signed main() {
    int n;
    cin >> n;
    vector<Node*> ts(n + 1);
    ts[0] = new Node();
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        int t, m;
        cin >> t >> m;
        if (m == 0) {
            ts[i + 1] = ts[t]->p;
        } else {
            ts[i + 1] = new Node(m);
            ts[i + 1]->p = ts[t];
            ts[i + 1]->sum += ts[t]->sum;
        }
        ans += ts[i + 1]->sum;
    }
    cout << ans << endl;
    return 0;
}
