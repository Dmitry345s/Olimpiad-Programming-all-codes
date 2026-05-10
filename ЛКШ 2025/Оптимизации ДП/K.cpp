#include<bits/stdc++.h>

//#define int long long

using namespace std;
using ull = unsigned long long;

const int C = 62;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ull n;
    vector<ull> q;
    vector<ull> ans;
    vector<ull> all;
    unordered_map<ull, int> pr;
    while (cin >> n) {
        int a, b, c;
        cin >> a >> b >> c;
        pr.clear();
        pr[n] = -1;
        q.clear();
        q.push_back(n);
        while (!q.empty()) {
            all.clear();
            for (ull v : q) {
                if (v % a == 0) {
                    ull u = v / a;
                    if (pr.find(u) == pr.end()) {
                        all.push_back(u);
                        pr[u] = 0;
                    }
                }
                if (v % b == 0) {
                    ull u = v / b;
                    if (pr.find(u) == pr.end()) {
                        all.push_back(u);
                        pr[u] = 1;
                    }
                }
                if (v > c) {
                    ull u = v - c;
                    if (pr.find(u) == pr.end()) {
                        all.push_back(u);
                        pr[u] = 2;
                    }
                }
                if (v > 1) {
                    ull u = v - 1;
                    if (pr.find(u) == pr.end()) {
                        all.push_back(u);
                        pr[u] = 3;
                    }
                }
            }
            sort(all.begin(), all.end());
            if ((int)all.size() > C) {
                all.resize(C);
            }
            swap(q, all);
            if (q.empty() || q[0] == 1) break;
        }
        ull key = 1;
        ans.clear();
        ans.push_back(key);
        while (pr[key] != -1) {
            int u = pr[key];
            if (u == 0) {
                ans.push_back(ans.back() * a);
            } else if (u == 1) {
                ans.push_back(ans.back() * b);
            } else if (u == 2) {
                ans.push_back(ans.back() + c);
            } else if (u == 3) {
                ans.push_back(ans.back() + 1);
            }
            key = ans.back();
        }
        cout << (int)ans.size() << " ";
        for (ull x : ans) cout << x << " ";
        cout << endl;
    }
}
