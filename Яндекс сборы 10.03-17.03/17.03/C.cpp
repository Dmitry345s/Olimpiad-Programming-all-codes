#include<bits/stdc++.h>

using namespace std;

const int MAX = 3e5 + 1;
int a[MAX];
int b[MAX];
long long ans[MAX];

struct Line {
    int k, b;
    Line(int k = 0, int b = 0) : k(k), b(b);
    long long get(int x) {
        return 1ll * k * x + b;
    }
};

vector<array<int, 4>> all;
vector<array<int, 4>> now;
vector<Line> ls;
vector<int> st;


void solve(int l, int r, vector<array<int, 4>> all) {
    if (l + 1 == r) {
        for (auto [ql, qr, t, in] : all) {
            ans[in] = 1ll * a[l] * t + b[l];
        }
        return;
    }
    vector<array<int, 4>> now;
    for (auto [ql, qr, t, in] : all) {
        if (ql < m && m <= qr) {
            now.push_back({ql, qr, t, in});
        }
    }
}

signed main() {
    int n, q;
    cin >> n >> q;
}
