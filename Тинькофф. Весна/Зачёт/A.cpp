#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> tree(8e5);
vector<int> ts(2e5);

void update(int l, int r, int v, int id, int x) {
    if (l + 1 < r) {
        int m = (l + r) / 2;
        if (id < m) {
            update(l, m, 2 * v, id, x);
        } else {
            update(m, r, 2 * v + 1, id, x);
        }
        if (ts[tree[2 * v]] <= ts[tree[2 * v + 1]]) {
            tree[v] = tree[2 * v];
        } else {
            tree[v] = tree[2 * v + 1];
        }
    } else {
        tree[v] = id;
    }
}
int get_min(int l, int r, int v, int left, int right) {
    if (l == left && r == right) {
        return tree[v];
    }
    int m = (l + r) / 2;
    if (right <= m) {
        return get_min(l, m, 2 * v, left, right);
    } else if (left >= m) {
        return get_min(m, r, 2 * v + 1, left, right);
    } else {
        int in1 =  get_min(l, m, 2 * v, left, m), in2 = get_min(m, r, 2 * v + 1, m, right);
        if (ts[in1] <= ts[in2]) {
            return in1;
        } else {
            return in2;
        }
    }
}

int main() {
    cin >> n;
    int k = 0;
    vector<vector<int>> v(n, vector<int> (3));
    for (int i = 0; i < n; ++i) {
        int t, p;
        cin >> t >> p;
        v[i] = {p, t, i};
        k = max(k, t);
    }
    for (int i = 0; i < k; ++i) {
        update(0, k, 1, 1, 0);
    }
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    long long ans = 0;
    vector<int> ansv(n);
    int timer = k + 1;
    for (int i = 0; i < v.size(); ++i) {
        int in = get_min(0, k, 1, k - v[i][1], k);
        if (ts[in] > 0) {
            ans += v[i][0];
            ansv[v[i][2]] = timer;
            timer += 1;
        } else {
            ts[in] = 1;
            update(0, k, 1, in, 1);
            ansv[v[i][2]] = k - in;
        }
    }
    cout << ans << endl;
    for (int i = 0; i < ansv.size(); ++i) {
        cout << ansv[i] << " ";
    }
    return 0;
}
