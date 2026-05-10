#include<iostream>
#include<vector>

using namespace std;

int lg = 20;
vector<vector<int>> up(1, vector<int> (lg, 0));
vector<int> ch(2e5, 1), tin(2e5, 0), tout(2e5, 2e5 + 1), p(2e5);

void add_new(int v) {
    up.push_back(vector<int> (lg));
    up.back()[0] = v;
    for (int i = 1; i < lg; ++i) {
        up.back()[i] = up[up.back()[i - 1]][i - 1];
    }
    tin[up.size() - 1] = tin[v] + 1;
    tout[up.size() - 1] = tout[v] - 1;
    p[up.size() - 1] = v;
}

int del(int v) {
    if (ch[p[v]]) {
        return p[v];
    }
    return p[v] = del(p[v]);
}

bool par(int a, int b) {
    return (tin[a] < tin[b] && tout[a] > tout[b]) || (a == b);
}

int lca(int a, int b) {
    if (par(a, b)) {
        return a;
    }
    if (par(b, a)) {
        return b;
    }
    for (int i = lg - 1; i >= 0; --i) {
        if (!par(up[a][i], b)) {
            a = up[a][i];
        }
        cout << a << endl;
    }
    return del(a);
}

int main() {
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        char p;
        cin >> p;
        if (p == '+') {
            int v;
            cin >> v;
            --v;
            add_new(v);
        } else if (p == '-') {
            int v;
            cin >> v;
            --v;
            ch[v] = 0;
            int ok = del(v);
        } else {
            int a, b;
            cin >> a >> b;
            --a; --b;
            cout << lca(a, b) + 1 << endl;
        }
    }
    return 0;
}
