#include<bits/stdc++.h>
#include "meetings.h"

using namespace std;

const int MAX = 2e3 + 5;
//int cnt[MAX];
int glcnt = 0;
mt19937 rnd(57);

vector<pair<int, int>> nans;

void Rsolve(vector<int> vs) {
    if ((int)vs.size() == 1) return;
    int rt = vs[0];
    sort(vs.begin() + 1, vs.end());
    vector<vector<int>> und;
    for (int i = 1; i < (int)vs.size(); ++i) {
        int fl = 0;
        for (int u = 0; u < (int)und.size(); ++u) {
            int y = Query(rt, vs[i], und[u][0]);
            if (y != rt) {
                und[u].push_back(vs[i]);
                if (y == vs[i]) {
                    swap(und[u][0], und[u].back());
                }
                for (int jj = 0; jj < u; ++jj) {
                    if ((int)und[u].size() > (int)und[jj].size()) {
                        swap(und[u], und[jj]);
                    }
                }
                fl = 1;
            }
        }
        if (!fl) {
            und.push_back({vs[i]});
        }
    }
    for (auto val : und) {
        nans.push_back({val[0], rt});
        Rsolve(val);
    }
}

void Solve(int n) {
    vector<int> nv(n);
    for (int i = 0; i < n; ++i) {
        nv[i] = i;
    }
    //shuffle(nv.begin(), nv.end(), rnd);
    Rsolve(nv);
    for (auto [u, v] : nans) {
        Bridge(min(u, v), max(u, v));
    }
}
