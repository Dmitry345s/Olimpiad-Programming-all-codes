#include<bits/stdc++.h>

#define int long long

using namespace std;

struct Node {
    int l; int r;
    int cnt[3];
    int vl, vr;
    Node(int l1, int r1) {
        cnt[2] = (r1 - l1);
        cnt[1] = 0;
        cnt[0] = 0;
        r = r1;
        l = l1;
        vl = -1;
        vr = -1;
    }
};

vector<Node> tree;
vector<int> update_tree;

void push(int v, int l, int r) {
    int x = update_tree[v];
    int u[3];
    u[0] = 0;
    u[1] = 0;
    u[2] = 0;
    for (int i = 0; i < 3; ++i) {
        u[max(0ll, i + x)] += tree[v].cnt[i];
    }
    for (int i = 0; i < 3; ++i) {
        tree[v].cnt[i] = u[i];
    }
    int m = (l + r) / 2;
    update_tree[v] = 0;
    if (tree[v].vl == -1) {
        tree[v].vl = (int)tree.size();
        tree.push_back(Node(l, m));
        update_tree.push_back(0);
    }
    if (tree[v].vr == -1) {
        tree[v].vr = (int)tree.size();
        tree.push_back(Node(m, r));
        update_tree.push_back(0);
    }
    update_tree[tree[v].vl] += x;
    update_tree[tree[v].vr] += x;
}

void update(int v, int l, int r, int ql, int qr, int x) {
    push(v, l, r);
    //cout << v << endl;
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        update_tree[v] = x;
        push(v, l, r);
        return;
    }
    int m = (l + r) / 2;
    if (tree[v].vl == -1) {
        tree[v].vl = (int)tree.size();
        tree.push_back(Node(l, m));
        update_tree.push_back(0);
    }
    if (tree[v].vr == -1) {
        tree[v].vr = (int)tree.size();
        tree.push_back(Node(m, r));
        update_tree.push_back(0);
    }
    update(tree[v].vl, l, m, ql, qr, x);
    update(tree[v].vr, m, r, ql, qr, x);
    for (int i = 0; i < 3; ++i) {
        tree[v].cnt[i] = tree[tree[v].vl].cnt[i] + tree[tree[v].vr].cnt[i];
    }
}

int get(int v, int l, int r, int ql, int qr, int x) {
    push(v, l, r);
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) {
        return tree[v].cnt[1] + tree[v].cnt[2] * (x + 1);
    }
    int m = (l + r) / 2;
    if (tree[v].vl == -1) {
        tree[v].vl = (int)tree.size();
        tree.push_back(Node(l, m));
        update_tree.push_back(0);
    }
    if (tree[v].vr == -1) {
        tree[v].vr = (int)tree.size();
        tree.push_back(Node(m, r));
        update_tree.push_back(0);
    }
    return get(tree[v].vl, l, m, ql, qr, x) + get(tree[v].vr, m, r, ql, qr, x);
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> all(m);
    for (int i = 0; i < m; ++i) {
        cin >> all[i].first >> all[i].second;
        --all[i].first;
        all[i].second *= -1;
    }
    sort(all.begin(), all.end());
    vector<pair<int, int>> st;
    for (int i = 0; i < m; ++i) {
        if (st.empty() || -all[i].second > st.back().second) {
            st.push_back({all[i].first, -all[i].second});
        }
    }
    tree.push_back(Node(0, n));
    update_tree.push_back(0);
    int last = -1;
    int j = 0;
    int sum = 2 * n;
    int cntt = 0;
    //cout << (int)st.size() << endl;
    while (j < (int)st.size()) {
        int cnt = 0;
        while (j < (int)st.size() && st[j].first <= last) {
            j++;
            cnt++;
        }
        if (cnt != 0) {
            j--;
        }
        sum -= get(0, 0, n, st[j].first, st[j].second, 1);
        update(0, 0, n, st[j].first, st[j].second, -2);
        cntt += 2;
        last = st[j].second;
        //cout << j << endl;
        j++;
    }
    cout << sum + cntt << endl;
    //cout << get(0, 0, n, 0, n, 1) << endl;
    /*int ans = 2 * n;
    int sum = 2 * n;
    for (int i = 0; i < 2 * m; ++i) {
        int maxm = 0, in = 0;
        for (int j = 0; j < m; ++j) {
            //cout << j << endl;
            int u = get(0, 0, n, all[j].first, all[j].second);
            //cout << j << " " << u << endl;
            if (u >= maxm) {
                maxm = u;
                in = j;
            }
        }
        //cout << i << endl;
        if (maxm != 0) {
            update(0, 0, n, all[in].first, all[in].second, -1);
        }
        sum -= maxm;
        ans = min(ans, sum + i + 1);
    }
    cout << ans << endl;*/
    return 0;
}
