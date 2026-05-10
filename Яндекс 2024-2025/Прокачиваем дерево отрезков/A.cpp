#include<bits/stdc++.h>

using namespace std;

struct Node {
    int x, sum;
    Node* pr = nullptr;
    Node(int x1, Node* rt) {
        x = x1;
        pr = rt;
        if (rt == nullptr) {
            sum = x1;
        } else {
            sum = rt->sum + x1;
        }
    }
};

int get(Node* rt) {
    if (rt == nullptr) return 0;
    return rt->x;
}

Node* get2(Node* rt) {
    if (rt == nullptr) return nullptr;
    return rt->pr;
}

signed main() {
    int n;
    cin >> n;
    vector<Node*> st = {new Node(0, nullptr)};
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        Node* u = new Node(0, nullptr);
        int t, m;
        cin >> t >> m;
        if (m == 0) {
            u = st[t]->pr;
            st.push_back(u);
        } else {
            u = new Node(m, st[t]);
            st.push_back(u);
        }
        ans += st.back()->sum;
    }
    cout << ans << endl;
    return 0;
}
