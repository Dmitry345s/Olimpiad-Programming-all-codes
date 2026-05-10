#include<bits/stdc++.h>

using namespace std;

const int MAX = 60001;
int up[MAX];
int dw[MAX];
int s[MAX];
int upsz = 0;
int dwsz = 0;

bool cmp(int a, int b) {
    if (s[a] == s[b]) return a < b;
    return s[a] < s[b];
}

int tt = 0;
int used[MAX];
int pru[MAX];
int prd[MAX];

int try_kuhn(int v) {
    if (used[v] == tt) return 0;
    used[v] = tt;
    if (upsz < dwsz) {
        if (pru[up[v]] == -1 || try_kuhn(pru[up[v]])) {
            upsz += s[v];
            if (pru[up[v]] != -1) upsz -= s[pru[up[v]]];
            pru[up[v]] = v;
            return 1;
        }
        if (prd[dw[v]] == -1 || try_kuhn(prd[dw[v]])) {
            dwsz += s[v];
            if (prd[dw[v]] != -1) dwsz -= s[prd[dw[v]]];
            prd[dw[v]] = v;
            return 1;
        }
    } else {
        if (prd[dw[v]] == -1 || try_kuhn(prd[dw[v]])) {
            dwsz += s[v];
            if (prd[dw[v]] != -1) dwsz -= s[prd[dw[v]]];
            prd[dw[v]] = v;
            return 1;
        }
        //cout << v << " " << -1 << endl;
        if (pru[up[v]] == -1 || try_kuhn(pru[up[v]])) {
            upsz += s[v];
            if (pru[up[v]] != -1) upsz -= s[pru[up[v]]];
            pru[up[v]] = v;
            return 1;
        }
    }
    return 0;
}

signed main() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < 2 * n; ++i) {
        cin >> up[i] >> dw[i] >> s[i];
        --up[i];
        --dw[i];
    }
    return 0;
}
