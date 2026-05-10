#include<bits/stdc++.h>

using namespace std;

mt19937 rnd(228);

struct Node {
    int x, h, y, cnt, ps, left_or_right;
    pair<int, int> ans;
    Node *l, *r, *pr;
    Node(int x1, int h1) {
        x = x1;
        h = h1;
        ans = {h1, x1};
        y = rnd();
        cnt = 1;
        ps = 0;
        left_or_right = -1;
        pr = nullptr;
        l = nullptr;
        r = nullptr;
    }
};

int get_cnt(Node* r) {
    if (r == nullptr) return 0;
    return r->cnt;
}

void push(Node* r) {
    if (r == nullptr) return;
    int ps = r->ps;
    r->ps = 0;
    if (r->l != nullptr) {
        r->l->ps += ps;
        r->l->ans.first += ps;
        r->l->h += ps;
    }
    if (r->r != nullptr) {
        r->r->ps += ps;
        r->r->ans.first += ps;
        r->r->h += ps;
    }
}

void upd(Node* r) {
    if (r == nullptr) return;
    pair<int, int> ans = {r->h, r->x};
    int cnt = 1;
    if (r->l != nullptr) {
        ans = min(ans, r->l->ans);
        cnt += r->l->cnt;
    }
    if (r->r != nullptr) {
        ans = min(ans, r->r->ans);
        cnt += r->r->cnt;
    }
    r->ans = ans;
    r->cnt = cnt;
}

Node* mmerge(Node* r1, Node* r2) {
    if (r1 == nullptr) return r2;
    if (r2 == nullptr) return r1;
    if (r1->y < r2->y) {
        push(r2);
        Node* now1 = mmerge(r1, r2->l);
        r2->l = now1;
        if (now1 != nullptr) {
            now1->left_or_right = 0;
            now1->pr = r2;
        }
        upd(r2);
        return r2;
    } else {
        push(r1);
        Node* now1 = mmerge(r1->r, r2);
        r1->r = now1;
        if (now1 != nullptr) {
            now1->left_or_right = 1;
            now1->pr = r1;
        }
        upd(r1);
        return r1;
    }
}

pair<Node*, Node*> split_k(Node* r, int k) {
    if (r == nullptr) return {nullptr, nullptr};
    if (r->cnt == k) return {r, nullptr};
    push(r);
    if (get_cnt(r->l) >= k) {
        auto [r1, r2] = split_k(r->l, k);
        r->l = r2;
        if (r2 != nullptr) {
            r2->pr = r;
            r2->left_or_right = 0;
        }
        upd(r);
        return {r1, r};
    } else {
        auto [r1, r2] = split_k(r->r, k - get_cnt(r->l) - 1);
        r->r = r1;
        if (r1 != nullptr) {
            r1->pr = r;
            r1->left_or_right = 1;
        }
        upd(r);
        return {r, r2};
    }
}

const int MAX = 5e4 + 5;
vector<vector<int>> g(MAX);
vector<int> p(MAX), h(MAX);
vector<int> tin(MAX), del(MAX);
vector<int> ord;

int root(int v) {
    if (p[v] == v) {
        return v;
    }
    int k = root(p[v]);
    del[v] += del[p[v]];
    return p[v] = k;
}

void dfs(int v, int p) {
    ord.push_back(v);
    tin[v] = (int)ord.size() - 1;
    h[v] = h[p] + 1;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        ord.push_back(v);
    }
}

void cout_tree(Node* r) {
    if (r == nullptr) return;
    cout_tree(r->l);
    cout << "! " << r->x << " " << r->h << " " << r->cnt << endl;
    cout_tree(r->r);
}

int num(Node* r) {
    if (r->pr == nullptr) {
        return get_cnt(r->l);
    }
    if (r->left_or_right == 0) {
        return num(r->pr) - get_cnt(r->r) - 1;
    }
    return num(r->pr) + get_cnt(r->l) + 1;
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        --p[i];
        if (p[i] == -1) {
            p[i] = i;
        }
        g[p[i]].push_back(i);
    }
    vector<Node*> all(n, nullptr);
    vector<Node*> st(n, nullptr);
    for (int i = 0; i < n; ++i) {
        if (p[i] == i) {
            h[i] = -1;
            ord.clear();
            dfs(i, i);
            for (int j = 0; j < (int)ord.size(); ++j) {
                Node* u = new Node(ord[j], h[ord[j]]);
                if (st[ord[j]] == nullptr) {
                    st[ord[j]] = u;
                }
                all[i] = mmerge(all[i], u);
            }
        }
    }
    int now = 0;
    int q;
    cin >> q;
    for (int _ = 0; _ < q; ++_) {
        int t;
        cin >> t;
        if (t == 0) {
            int x, y;
            cin >> x >> y;
            int u = (x - 1 + now) % n;
            int v = (y - 1 + now) % n;
            /*int u, v;
            cin >> u >> v;*/
            if (root(u) != root(v)) {
                now = 0;
            } else {
                int l = num(st[u]), r = num(st[v]);
                if (l > r) {
                    swap(l, r);
                }
                //cout << l << " " << r << endl;
                auto [r1, r2] = split_k(all[root(u)], r + 1);
                auto [r3, r4] = split_k(r1, l);
                now = r4->ans.second + 1;
                all[root(u)] = mmerge(mmerge(r3, r4), r2);
            }
            cout << now << endl;
        } else {
            int x, y;
            cin >> x >> y;
            int u = (x - 1 + now) % n;
            int v = (y - 1 + now) % n;
            /*int u, v;
            cin >> u >> v;*/
            int rv = root(v);
            int in = num(st[v]);
            //cout << in << endl;
            //cout << rv << endl;
            auto [r1, r2] = split_k(all[rv], in + 1);
            //cout_tree(r1);
            auto [r3, r4] = split_k(r1, in);
            //cout_tree(r4);
            int hh = r4->h;
            all[u]->ps += hh + 1;
            all[u]->h += hh + 1;
            all[u]->ans.first += hh + 1;
            Node *to = new Node(v, hh);
            all[u] = mmerge(all[u], to);
            all[rv] = mmerge(mmerge(mmerge(r3, r4), all[u]), r2);
            //cout_tree(all[rv]);
            p[u] = v;
        }
    }
    return 0;
}
