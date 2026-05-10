#include<bits/stdc++.h>

using namespace std;

struct Node {
    Node* next;
    int here, all;
    Node() {
        here = 0;
        all = 0;
        next = nullptr;
    }
};

signed main() {
    freopen("snowmen.in", "r", stdin);
    freopen("snowmen.out", "w", stdout);
    Node *rt = new Node();
    int n;
    cin >> n;
    vector<Node*> all(n + 1);
    all[0] = new Node();
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        all[i] = new Node();
        int t, m;
        cin >> t >> m;
        if (m == 0) {
            all[i] = all[t]->next;
        } else {
            all[i]->next = all[t];
            all[i]->here = m;
            all[i]->all = all[t]->all + m;
        }
        ans += all[i]->all;
    }
    cout << ans << endl;
    return 0;
}
