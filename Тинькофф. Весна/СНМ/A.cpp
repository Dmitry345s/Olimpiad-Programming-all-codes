#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

int MAX = 1e5;
vector<int> p(MAX);
vector<int> size_(MAX);

int get_set(int v) {
    if (p[v] == v) {
        return v;
    }
    return p[v] = get_set(p[v]);
}

bool check(int a, int b) {
    return get_set(a) == get_set(b);
}

void union_set(int a, int b) {
    int f = get_set(a), s = get_set(b);
    if (f != s) {
        if (size_[f] < size_[s]) {
            swap(f, s);
        }
        p[s] = f;
        size_[f] += size_[s];
    }
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < m; ++i) {
        int v, to;
        cin >> v >> to;
    }
    for (int i = 0; i < n; ++i) {
        p[i] = i;
        size_[i] = 1;
    }
    vector<pair<int, pair<int, int>>> q;
    for (int i = 0; i < k; ++i) {
        string now;
        cin >> now;
        int a, b;
        cin >> a >> b;
        --a; --b;
        if (now == "ask") {
            q.push_back({1, {a, b}});
        } else {
            q.push_back({2, {a, b}});
        }
    }
    reverse(q.begin(), q.end());
    vector<bool> ans;
    for (int i = 0; i < k; ++i) {
        if (q[i].first == 1) {
            ans.push_back(check(q[i].second.first, q[i].second.second));
        } else {
            union_set(q[i].second.first, q[i].second.second);
        }
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); ++i) {
        if (ans[i]) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
