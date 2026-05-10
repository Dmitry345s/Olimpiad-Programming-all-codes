#include<bits/stdc++.h>

using namespace std;

const int MAX = 25e3 + 1;
int p[MAX], sz[MAX], hg[MAX];
unsigned int all[MAX];
vector<unsigned int> tg[MAX];

int root(int v) {
    int x = v;
    while (p[v] != v) {
        v = p[v];
    }
    while (x != v) {
        int u = p[x];
        p[x] = v;
        x = u;
    }
    return v;
}

void unite(int v, int u) {
    /*u = root(u);
    v = root(v);
    int x = hg[u];
    if (sz[v] > sz[u]) {
        swap(u, v);
    }*/
    p[v] = u;
    /*sz[u] = max(sz[u], sz[v] + 1);
    hg[u] = x;*/
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //now.reserve(MAX);
    int n, m;
    unsigned int a, b;
    while (cin >> n >> m >> a >> b) {
        if (n == 0) return 0;
        for (int i = 0; i < n; ++i) {
            all[i] = (a * (i + 1) + b);
            p[i] = i;
            tg[i].clear();
            //sz[i] = 1;
            //hg[i] = i;
            //cout << all[i] << " ";
        }
        //cout << endl;
        unsigned l, r;
        for (int i = n; i < 2 * m + n; i += 2) {
            l = (a * (i + 1) + b) % n;
            r = (a * (i + 2) + b) % n;
            if (r < l) swap(r, l);
            tg[r].push_back(l);
            //cout << l << " " << r << endl;
        }
        //cout << 0 << endl;
        //cout << 0 << endl;
        vector<int> st;
        long long ans = 0;
        st.reserve(n);
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && all[st.back()] >= all[i]) {
                unite(st.back(), i);
                st.pop_back();
            }
            st.push_back(i);
            //cout << "# " << i << endl;
            for (int l : tg[i]) {
                //cout << hg[root(l)] << endl;
                ans += all[root(l)];
            }
        }
        cout << ans << '\n';
    }
}
