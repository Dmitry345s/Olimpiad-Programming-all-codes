#include<bits/stdc++.h>

# define int long long

using namespace std;

const int MAX = (1 << 19) + 1, INF = 2e9 + 10;
int n, m;
int a[MAX], b[MAX];

int geta(int in) {
    if (in < 0 || in >= n) return INF;
    return a[in];
}

int getb(int in) {
    if (in < 0) return -INF * in;
    if (in >= m) return INF * (in - m + 1);
    return b[in];
}

struct Fi {
    int i;
    Fi(int i = -1) : i(i) {}
    int get(int x) {
        return geta(i) + getb(x - i);
    }
};

vector<Fi> tree(1);
vector<pair<int, int>> sns(1, {-1, -1});

void add(int v, int l, int r, Fi now) {
    int m = (l + r) / 2;
    if (now.get(m) <= tree[v].get(m)) {
        swap(now, tree[v]);
    }
    if (l + 1 == r) return;
    if (now.get(l) <= tree[v].get(l)) {
        if (sns[v].first == -1) {
            sns[v].first = (int)tree.size();
            sns.push_back({-1, -1});
            tree.push_back(Fi());
        }
        add(sns[v].first, l, m, now);
    } else if (now.get(r) <= tree[v].get(r)) {
        if (sns[v].second == -1) {
            sns[v].second = (int)tree.size();
            sns.push_back({-1, -1});
            tree.push_back(Fi());
        }
        add(sns[v].second, m, r, now);
    }
}

int get(int v, int l, int r, int x) {
    int u = tree[v].get(x);
    //cout << u << " " << v << " " << tree[v].i << " " << x << endl;
    if (l + 1 == r) return u;
    int m = (l + r) / 2;
    if (x < m) {
        if (sns[v].first == -1) {
            sns[v].first = (int)tree.size();
            sns.push_back({-1, -1});
            tree.push_back(Fi());
        }
        return min(u, get(sns[v].first, l, m, x));
    }
    if (sns[v].second == -1) {
        sns[v].second = (int)tree.size();
        sns.push_back({-1, -1});
        tree.push_back(Fi());
    }
    return min(u, get(sns[v].second, m, r, x));
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> m >> n;
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        //cout << i << endl;
        add(0, 0, 2 * MAX, Fi(i));
    }
    for (int i = 0; i < n + m - 1; ++i) {
        cout << get(0, 0, 2 * MAX, i) << " ";
    }
    cout << endl;
    return 0;
}
