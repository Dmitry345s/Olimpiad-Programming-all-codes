#include<bits/stdc++.h>

using namespace std;

struct Node {
    array<Node*, 26> to;
    int leaf, leaf2;
    Node() {
        for (int i = 0; i < 26; ++i) {
            to[i] = nullptr;
        }
        leaf = 0;
        leaf2 = 0;
    }
};

Node *root = new Node();

void add(string &s) {
    Node *n = root;
    for (int i = 0; i < s.size(); ++i) {
        n->leaf += 1;
        int c = s[i] - 'a';
        if (!n->to[c]) {
            n->to[c] = new Node();
        }
        n = n->to[c];
    }
    n->leaf += 1;
    n->leaf2 += 1;
}

string ans = "";

void get(Node *v, int k) {
    if (k == 0) {
        return;
    }
    for (int i = 0; i < 26; ++i) {
        if (v->to[i]) {
            if (v->to[i]->leaf >= k) {
                ans += char(i + 97);
                get(v->to[i], k - v->to[i]->leaf2);
                break;
            } else {
                k -= v->to[i]->leaf;
            }
        }
    }
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            string s;
            cin >> s;
            add(s);
        } else {
            int k;
            cin >> k;
            ans = "";
            get(root, k);
            cout << ans << endl;
        }
    }
    return 0;
}
