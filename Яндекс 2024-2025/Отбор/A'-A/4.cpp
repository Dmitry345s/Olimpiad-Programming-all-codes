#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")

#define int long long

using namespace std;

struct Node {
    int val, l_son, r_son;
    Node(int val = 0, int l_son = -1, int r_son = -1) : val(val), l_son(l_son), r_son(r_son) {}
};

const long long MAX = 2e5 + 5, INF = 3e14 + 2;
long long a[MAX], b[MAX];
long long x;
long long ans = 0;
vector<Node> tree(1);

void update(int v, long long l, long long r, int in, int x) {
    //cout << v << " " << l << " " << r << endl;
    if (l + 1 == r) {
        tree[v].val += x;
        return;
    }
    long long m = (l + r) / 2;
    if (in < m) {
        if (tree[v].l_son == -1) {
            tree.push_back(Node());
            tree[v].l_son = (int)tree.size() - 1;
        }
        //cout << tree[v].l_son << endl;
        update(tree[v].l_son, l, m, in, x);
    } else {
        if (tree[v].r_son == -1) {
            tree.push_back(Node());
            tree[v].r_son = (int)tree.size() - 1;
        }
        //cout << tree.size() << endl;
        //cout << tree[v].r_son << endl;
        update(tree[v].r_son, m, r, in, x);
    }
    //cout << l << " " << r << endl;
    tree[v].val = 0;
    if (tree[v].l_son != -1) {
        tree[v].val += tree[tree[v].l_son].val;
    }
    if (tree[v].r_son != -1) {
        tree[v].val += tree[tree[v].r_son].val;
    }
    //cout << l << " " << r << endl;
}

int get(int v, long long l, long long r, int ql, int qr) {
    if (v == -1) return 0;
    if (qr <= l || r <= ql) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return tree[v].val;
    }
    int m = (l + r) / 2;
    return get(tree[v].l_son, l, m, ql, qr) + get(tree[v].r_son, m, r, ql, qr);
}

void to_ans(int l, int r) {
    if (l + 1 == r) {
        if (a[l] + b[l] <= x) {
            ans += 1;
        }
        return;
    }
    long long m = (l + r) / 2;
    to_ans(l, m);
    to_ans(m, r);
    //cout << l << " " << r << endl;
    long long now_min = INF;
    long long now_sum = 0;
    int j = m;
    long long now_sum2 = 0;
    vector<int> last;
    for (int i = m - 1; i >= l; --i) {
        now_sum += b[i];
        now_min = min(now_min, a[i]);
        while (j < r && a[j] >= now_min) {
            now_sum2 += b[j];
            last.push_back(now_sum2);
            //cout << j << endl;
            j++;
        }
        //cout << j << endl;
        if (now_min + now_sum > x) continue;
        ans += upper_bound(last.begin(), last.end(), x - now_min - now_sum) - last.begin();
    }
    now_min = INF;
    now_sum = 0;
    j = m - 1;
    now_sum2 = 0;
    last.clear();
    for (int i = m; i < r; ++i) {
        now_sum += b[i];
        now_min = min(now_min, a[i]);
        while (j >= l && a[j] > now_min) {
            now_sum2 += b[j];
            last.push_back(now_sum2);
            //cout << j << endl;
            j--;
        }
        if (now_min + now_sum > x) continue;
        ans += upper_bound(last.begin(), last.end(), x - now_min - now_sum) - last.begin();
    }
    //cout << l << " " << r << " " << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n >> x;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    to_ans(0, n);
    cout << ans << endl;
    return 0;
}
