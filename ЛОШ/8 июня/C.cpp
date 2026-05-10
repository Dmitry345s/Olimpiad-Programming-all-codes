#include<iostream>
#include<vector>
#include<string>

using namespace std;

vector<int> tree(4e5);
string s;

void update (int l, int r, int v, int id, char val) {
    if (l + 1 == r) {
        tree[v] = id;
        return;
    }
    int m = (l + r) / 2;
    if (id < m) {
        update(l, m, 2 * v, id, val);
    } else {
        update(m, r, 2 * v + 1, id, val);
    }
    if (s[tree[2 * v]] >= s[tree[2 * v + 1]]) {
        tree[v] = tree[2 * v];
    } else {
        tree[v] = tree[2 * v + 1];
    }
}

int get_max(int l, int r, int v, int left, int right) {
    if (l == left && r == right) {
        return tree[v];
    }
    int m = (l + r) / 2;
    if (right <= m) {
        return get_max(l, m, 2 * v, left, right);
    } else if (left >= m) {
        return get_max(m, r, 2 * v + 1, left, right);
    }
    int k = get_max(l, m, 2 * v, left, m), k2 = get_max(m, r, 2 * v + 1, m, right);
    if (s[k] >= s[k2]) {
        return k;
    } else {
        return k2;
    }
}

string p;

void recurs (int l, int r, int k) {
    int i = get_max(0, r, 1, l, r - k);
    p.push_back(s[i]);
    if (k != 0) {
        recurs(i + 1, r, k - 1);
    }
}
int main() {
    cin >> s;
    int n = s.size();
    for (int i = 0; i < n; ++i) {
        update(0, n, 1, i, s[i]);
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        p = "";
        int k, t;
        cin >> k >> t;
        --t;
        recurs(0, n, k - 1);
        cout << p[t] << endl;
    }
    return 0;
}
