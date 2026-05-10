#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 5e6 + 5;
int tree[MAX];

void upd(int i, int x) {
    for (; i < MAX; i = (i | (i + 1))) {
        tree[i] += x;
    }
}

int get(int i) {
    int ans = 0;
    for (; i >= 0; i = (i & (i + 1)) - 1) {
        ans += tree[i];
    }
    return ans;
}

mt19937 rnd(57);

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        --a[i];
        p[a[i]] = i;
    }
    int u = -1;
    for (int i = 0; i + 1 < n; i += 2) {
        int nadd = rnd();
        int l = p[i], r = p[i + 1];
        if (l > r) swap(l, r);
        int y = get(l);
        int y2 = get(r);
        //cout << i << " " << nadd << " " << l << " " << r << " " << y << " " << y2 << endl;
        if (y != y2) {
            u = i;
            break;
        }
        upd(l, nadd);
        upd(r, -nadd);
    }
    if (u == -1) u = n - 1;
    fill(tree, tree + MAX, 0);
    int u2 = -1;
    for (int i = 1; i + 1 < n; i += 2) {
        int nadd = rnd();
        int l = p[i], r = p[i + 1];
        if (l > r) swap(l, r);
        int y = get(l);
        int y2 = get(r);
        //cout << i << " " << nadd << " " << l << " " << r << " " << y << " " << y2 << endl;
        if (y != y2) {
            u2 = i;
            break;
        }
        upd(l, nadd);
        upd(r, -nadd);
    }
    if (u2 == -1) u2 = n - 1;
    //cout << u << " " << u2 << endl;
    cout << min(u, u2) + 1 << endl;
    return 0;
}
