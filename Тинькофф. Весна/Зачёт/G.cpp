#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int n;
vector<long long> tree(4e6, 0);

void update(int l, int r, int v, int i, int x) {
    if (l + 1 < r) {
        int m = (l + r) / 2;
        if (i < m) {
            update(l, m, 2 * v, i, x);
        } else {
            update(m, r, 2 * v + 1, i, x);
        }
        tree[v] = tree[2 * v] + tree[2 * v + 1];
    } else {
        tree[v] += x;
    }
}

long long get_sum(int l, int r, int left, int right, int v) {
    if (l == left && r == right) {
        return tree[v];
    }
    int m = (l + r) / 2;
    if (right <= m) {
        return get_sum(l, m, left, right, 2 * v);
    } else if (left >= m) {
        return get_sum(m, r, left, right, 2 * v + 1);
    } else {
        return get_sum(l, m, left, m, 2 * v) + get_sum(m, r, m, right, 2 * v + 1);
    }
}

int main() {
    cin >> n;
    vector<pair<long long, int>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first;
        a[i].first += i;
        a[i].second = i;
    }
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        int k = a[i].second;
        ans += get_sum(0, 2 * n, k + 1, 2 * n, 1) * (a[i].first - a[i].second);
        update(0, 2 * n, 1, a[i].first, 1);
    }
    cout << ans << endl;
    return 0;
}
