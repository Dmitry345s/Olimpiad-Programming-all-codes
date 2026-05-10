#include<iostream>
#include<vector>

using namespace std;

vector<pair<int, int>> tree(1200000, {0, 0});
vector<int> a(300000);

void update (int l, int r, int v, int id) {
    if (l + 1 == r) {
        tree[v] = {id, id};
    } else {
        int m = (l + r) / 2;
        if (id < m) {
            update(l, m, 2 * v, id);
        } else {
            update(m, r, 2 * v + 1, id);
        }
        if (a[tree[2 * v].first] <= a[tree[2 * v + 1].first]) {
            tree[v].first = tree[2 * v].first;
        } else {
            tree[v].first = tree[2 * v + 1].first;
        }
        if (a[tree[2 * v + 1].second] >= a[tree[2 * v].second]) {
            tree[v].second = tree[2 * v + 1].second;
        } else {
            tree[v].second = tree[2 * v].second;
        }
    }
}

int get_min(int l, int r, int v, int left, int right) {
    if (left == l && right == r) {
        return tree[v].first;
    }
    int m = (l + r) / 2;
    if (right <= m) {
        return get_min(l, m, 2 * v, left, right);
    } else if (left >= m) {
        return get_min(m, r, 2 * v + 1, left, right);
    } else {
        int i1 = get_min(l, m, 2 * v, left, m);
        int i2 = get_min(m, r, 2 * v + 1, m, right);
        if (a[i1] <= a[i2]) {
            return i1;
        } else {
            return i2;
        }
    }
}

int get_max(int l, int r, int v, int left, int right) {
    if (left == l && right == r) {
        return tree[v].second;
    }
    int m = (l + r) / 2;
    if (right <= m) {
        return get_max(l, m, 2 * v, left, right);
    } else if (left >= m) {
        return get_max(m, r, 2 * v + 1, left, right);
    } else {
        int i1 = get_max(l, m, 2 * v, left, m);
        int i2 = get_max(m, r, 2 * v + 1, m, right);
        if (a[i1] <= a[i2]) {
            return i2;
        } else {
            return i1;
        }
    }
}

vector<pair<int, int>> ans;

void recurs(int l, int r, int & n) {
    int i1 = get_min(0, n, 1, l, r);
    int i2 = get_max(0, n, 1, i1, r);
    ans.push_back({i1, i2});
    if (i1 != l) {
        recurs(l, i1, n);
    }
    if (i2 != r - 1) {
        recurs(i2 + 1, r, n);
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        update(0, n, 1, i);
    }
    recurs(0, n, n);
    cout << ans.size() << endl;
    return 0;
    /*long long ans1, ans2, ans3, maxm = 0;
    for (long long i = a; i < n; i += a) {
        for (long long j = b; j < n - i; j += b) {
            long long may_maxm = (i / a) * (j / b) * ((n - i - j) / c);
            if (may_maxm >= maxm) {
                maxm = may_maxm;
                ans1 = i;
                ans2 = j;
                ans3 = n - i - j;
            }
        }
    }
    cout << ans1 << " " << ans2 << " " << ans3 << endl;*/
}
