#include<bits/stdc++.h>

using namespace std;

const int ln = 18;

struct Node {
    Node* up[ln];
    int val;
    int len;
    Node() {
        val = 0;
        for (int i = 0; i < ln; ++i) {
            up[i] = nullptr;
        }
        len = 0;
    }
};

void cop(Node* v, Node* now) {
    for (int i = 0; i < ln; ++i) {
        now->up[i] = v->up[i];
    }
    now->len = v->len;
    now->val = v->val;
}

int get(Node* v) {
    int len = v->len;
    len -= 1;
    Node* now = new Node();
    cop(v, now);
    for (int i = ln - 1; i >= 0; --i) {
        if ((len >> i) & 1) {
            now = now->up[i];
        }
    }
    return now->val;
}

signed main() {
    freopen("queue.in", "r", stdin);
    freopen("queue.out", "w", stdout);
    int n;
    cin >> n;
    vector<Node*> qs(1);
    qs[0] = new Node();
    for (int _ = 0; _ < n; ++_) {
        int t;
        cin >> t;
        if (t == 1) {
            int in, vl;
            cin >> in >> vl;
            Node* ls = new Node();
            ls->up[0] = qs[in];
            for (int i = 1; i < ln; ++i) {
                if (ls->up[i - 1] == nullptr) break;
                ls->up[i] = (ls->up[i - 1])->up[i - 1];
            }
            ls->val = vl;
            ls->len = qs[in]->len + 1;
            qs.push_back(ls);
        } else {
            int in;
            cin >> in;
            cout << get(qs[in]) << endl;
            Node* ls = new Node();
            cop(qs[in], ls);
            ls->len -= 1;
            qs.push_back(ls);
        }
    }
    return 0;
}
