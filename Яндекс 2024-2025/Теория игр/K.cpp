#include<iostream>
#include<vector>
#include<bitset>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")
#pragma GCC target("fma")
#pragma GCC target("bmi2")
#pragma GCC target("bmi")

using namespace std;

const long long MAX = 1e8;
short int deg[MAX];
bitset<MAX> used;
bitset<MAX> who;
long long n1, n2;
const long long MAX2 = 1e4;
vector<long long> g1[MAX2], g2[MAX2];
long long st1[MAX2 + 1], st2[MAX2 + 1];
long long g3[MAX2], g4[MAX2];
long long deg1[MAX2], deg2[MAX2];

void dfs(long long v1, long long v2, bool t) {
    used[v1 * n2 + v2] = 1;
    who[v1 * n2 + v2] = t;
    if (t) {
        for (long long i = st1[v1]; i < st1[v1 + 1]; ++i) {
            long long to1 = g3[i];
            if (!(--deg[to1 * n2 + v2]) && !used[to1 * n2 + v2]) {
                dfs(to1, v2, 0);
            }
        }
        for (long long i = st2[v2]; i < st2[v2 + 1]; ++i) {
            long long to2 = g4[i];
            if (!(--deg[v1 * n2 + to2]) && !used[v1 * n2 + to2]) {
                dfs(v1, to2, 0);
            }
        }
        return;
    }
    for (long long i = st1[v1]; i < st1[v1 + 1]; ++i) {
        if (!used[g3[i] * n2 + v2]) {
            dfs(g3[i], v2, 1);
        }
    }
    for (long long i = st2[v2]; i < st2[v2 + 1]; ++i) {
        if (!used[v1 * n2 + g4[i]]) {
            dfs(v1, g4[i], 1);
        }
    }
}

/*void dfs(long long x, bool t) {
    used[x] = 1;
    who[x] = t;
    long long v1 = x / n2, v2 = x % n2;
    for (long long to1 : g1[v1]) {
        long long y = to1 * n2 + v2;
        if ((!t || !(--deg[y])) && !used[y]) {
            dfs(y, !t);
        }
    }
    for (long long to2 : g2[v2]) {
        long long y = v1 * n2 + to2;
        if ((!t || !(--deg[y])) && !used[y]) {
            dfs(y, !t);
        }
    }
}*/

/*void bfs(long long vs1, long long vs2, long long ts) {
    used[vs1 * n2 + vs2] = 1;
    who[vs1 * n2 + vs2] = ts;
    queue<long long> q;
    q.push(vs1 * n2 + vs2);
    while (!q.empty()) {
        long long x = q.front();
        long long v1 = x / n2, v2 = x % n2;
        q.pop();
        for (long long to1 : g1[v1]) {
            long long y = to1 * n2 + v2;
            if ((!who[x] || !(--deg[y])) && !used[y]) {
                used[y] = 1; who[y] = !who[x];
                q.push(y);
            }
        }
        for (long long to2 : g2[v2]) {
            long long y = v1 * n2 + to2;
            if ((!who[x] || !(--deg[y])) && !used[y]) {
                used[y] = 1; who[y] = !who[x];
                q.push(y);
            }
        }
    }
}*/

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    long long m1;
    cin >> n1 >> m1;
    for (long long i = 0; i < m1; ++i) {
        long long a, b;
        cin >> a >> b;
        --a; --b;
        deg1[a]++;
        g1[b].push_back(a);
    }
    long long now = 0;
    for (long long i = 0; i < n1; ++i) {
        for (long long j = 0; j < (long long)g1[i].size(); ++j) {
            g3[now + j] = g1[i][j];
        }
        st1[i] = now;
        now += (long long)g1[i].size();
    }
    st1[n1] = now;
    long long m2;
    cin >> n2 >> m2;
    for (long long i = 0; i < m2; ++i) {
        long long a, b;
        cin >> a >> b;
        --a; --b;
        deg2[a]++;
        g2[b].push_back(a);
    }
    now = 0;
    for (long long i = 0; i < n2; ++i) {
        for (long long j = 0; j < (long long)g2[i].size(); ++j) {
            g4[now + j] = g2[i][j];
        }
        st2[i] = now;
        now += (long long)g2[i].size();
    }
    st2[n2] = now;
    long long x = 0;
    for (long long i = 0; i < n1; ++i) {
        for (long long j = 0; j < n2; ++j) {
            deg[x] = deg1[i] + deg2[j];
            x++;
        }
    }
    x = 0;
    for (long long i = 0; i < n1; ++i) {
        for (long long j = 0; j < n2; ++j) {
            if (!deg[x] && !used[x]) {
                dfs(i, j, 0);
            }
            x++;
        }
    }
    long long t;
    cin >> t;
    for (long long i = 0; i < t; ++i) {
        long long a, b;
        cin >> a >> b;
        --a; --b;
        if (!used[a * n2 + b]) {
            cout << "draw\n";
        } else if (!who[a * n2 + b]) {
            cout << "second\n";
        } else {
            cout << "first\n";
        }
    }
    return 0;
}
