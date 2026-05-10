#include<bits/stdc++.h>

using namespace std;

const long long INF = 2e18;
const int INF2 = 1e9 + 1;

struct Line {
    long long k, b;
    Line(long long k = 0, long long b = -INF) : k(k), b(b) {};
    long long get(long long x) {
        return k * x + b;
    }
};

struct Node {
    Line a;
    int l_son, r_son;
    int l, r;
    Node(Line a1 = Line(), int l_son1 = -1, int r_son1 = -1, int l1 = -INF2, int r1 = INF2) {
        a = a1;
        l_son = l_son1;
        r_son = r_son1,
        l = l1;
        r = r1;
    }
};

const int MAX = 3e5 + 2;
vector<pair<int, int>> all(MAX, {-1, -1});
vector<Line> lines(MAX);
vector<long long> qs(MAX , -INF);
vector<vector<Line>> treeg(4 * MAX);
vector<Node> tree(1);
vector<vector<pair<int, Line>>> go_back;

void add(int v, int l, int r, int ql, int qr, Line tr) {
    //cout << v << " " << l << " " << r << endl;
    if (qr <= l || r <= ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        treeg[v].push_back(tr);
        return;
    }
    int m = (l + r) / 2;
    add(2 * v, l, m, ql, qr, tr);
    add(2 * v + 1, m, r, ql, qr, tr);
}

void update(Line new_line, int v) {
    go_back.back().push_back({v, tree[v].a});
    if (tree[v].l + 1 == tree[v].r) {
        if (new_line.get(tree[v].l) > tree[v].a.get(tree[v].l)) {
            swap(new_line, tree[v].a);
        }
        return;
    }
    int m = (tree[v].l + tree[v].r) / 2;
    if (new_line.get(m) > tree[v].a.get(m)) {
        swap(new_line, tree[v].a);
    }
    if (new_line.get(tree[v].l) > tree[v].a.get(tree[v].l)) {
        if (tree[v].l_son == -1) {
            tree.push_back(Node(new_line, -1, -1, tree[v].l, m));
            go_back.back().push_back({(int)tree.size() - 1, Line()});
            tree[v].l_son = (int)tree.size() - 1;
            return;
        }
        update(new_line, tree[v].l_son);
    } else {
        if (tree[v].r_son == -1) {
            tree.push_back(Node(new_line, -1, -1, m, tree[v].r));
            go_back.back().push_back({(int)tree.size() - 1, Line()});
            tree[v].r_son = (int)tree.size() - 1;
            return;
        }
        update(new_line, tree[v].r_son);
    }
}

long long get(long long x, int v) {
    if (tree[v].l + 1 == tree[v].r) {
        return tree[v].a.get(x);
    }
    int m = (tree[v].l + tree[v].r) / 2;
    if (x < m) {
        if (tree[v].l_son == -1) {
            return tree[v].a.get(x);
        }
        return max(tree[v].a.get(x), get(x, tree[v].l_son));
    } else {
        if (tree[v].r_son == -1) {
            return tree[v].a.get(x);
        }
        return max(tree[v].a.get(x), get(x, tree[v].r_son));
    }
}

vector<long long> ans(MAX);

void to_ans(int v, int l, int r) {
    //cout << v << " " << l << " " << r << endl;
    //cout << tree[0].a.k << " " << tree[0].a.b << endl;
    for (int i = 0; i < (int)treeg[v].size(); ++i) {
        //cout << treeg[v][i].k << " " << treeg[v][i].b << endl;
        go_back.push_back({});
        update(treeg[v][i], 0);
    }
    if (l + 1 == r) {
        if (qs[l] != -INF) {
            ans[l] = get(qs[l], 0);
        }
        for (int i = 0; i < (int)treeg[v].size(); ++i) {
            for (auto [whr, wht] : go_back.back()) {
                //cout << "! " << v << " " << whr << " " << wht.k << " " << wht.b << endl;
                tree[whr].a = wht;
            }
            go_back.pop_back();
        }
        return;
    }
    //cout << v << " " << l << " " << r << endl;
    int m = (l + r) / 2;
    to_ans(2 * v, l, m);
    to_ans(2 * v + 1, m, r);
    for (int i = 0; i < (int)treeg[v].size(); ++i) {
        for (auto [whr, wht] : go_back.back()) {
            tree[whr].a = wht;
        }
        go_back.pop_back();
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int op;
        cin >> op;
        if (op == 1) {
            int a, b;
            cin >> a >> b;
            all[i] = {i, n};
            lines[i] = Line(a, b);
        } else if (op == 2) {
            int in;
            cin >> in;
            --in;
            all[in].second = i + 1;
        } else {
            int a;
            cin >> a;
            qs[i] = a;
        }
    }
    for (int i = 0; i < n; ++i) {
        //cout << all[i].first << " " << all[i].second << endl;
        if (all[i] != pair<int, int>{-1, -1}) {
            add(1, 0, n, all[i].first, all[i].second, lines[i]);
        }
    }
    to_ans(1, 0, n);
    for (int i = 0; i < n; ++i) {
        if (qs[i] != -INF) {
            cout << ans[i] << endl;
        }
    }
    return 0;
}
