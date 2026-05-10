#include<bits/stdc++.h>

using namespace std;

struct Node {
    array<Node*, 2> to;
    int leaf;
    Node() {
        to = {nullptr, nullptr};
        leaf = 0;
    }
};

Node *root = new Node();

void add(int x, int cnt) {
    Node *n = root;
    for (int i = 30; i >= 0; --i) {
        n->leaf += cnt;
        int bit = (x >> i) & 1;
        if (!n->to[bit]) {
            n->to[bit] = new Node();
        }
        n = n->to[bit];
    }
    n->leaf += cnt;
}

int get(int x) {
    Node *n = root;
    int ans = 0;
    for (int i = 30; i >= 0; --i) {
        int bit = ((x >> i) & 1) ^ 1;
        if (n->to[bit] && n->to[bit]->leaf) {
            ans += (bit << i);
            n = n->to[bit];
        } else {
            ans += ((bit ^ 1) << i);
            n = n->to[(bit ^ 1)];
        }
    }
    return ans;
}

signed main() {
    int q;
    cin >> q;
    add(0, 1);
    for (int i = 0; i < q; ++i) {
        char t;
        cin >> t;
        int x;
        cin >> x;
        if (t == '+') {
            add(x, 1);
        } else if (t == '-') {
            add(x, -1);
        } else {
            cout << (get(x) ^ x) << endl;
        }
    }
    return 0;
}
