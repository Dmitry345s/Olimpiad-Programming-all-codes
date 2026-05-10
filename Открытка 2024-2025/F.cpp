#include<bits/stdc++.h>

#define int long long

using namespace std;

const int A = 26, MAX = 5e5 + A + 1, MAX2 = 3e5 + 1;
string all[MAX];
int cl[MAX];
vector<int> all2[MAX];
const int MOD = 9223372036854775783, P = 179, LN = 19;
__int128 pows[2 * MAX];
int up[MAX][LN];
int up2[MAX][LN];

struct Node {
    int go[A];
    int fl, sl, spl, ps, ps2;
    Node() {
        sl = 0;
        spl = 0;
        ps = 0;
        ps2 = -1;
        fl = -1;
        for (int i = 0; i < A; ++i) {
            go[i] = -1;
        }
    }
};

vector<Node> bor(1);

void add(string s, int i) {
    int v = 0;
    for (int c : s) {
        int cc = c - 'a';
        if (bor[v].go[cc] == -1) {
            bor[v].go[cc] = (int)bor.size();
            bor.push_back(Node());
        }
        int k = v;
        v = bor[v].go[cc];
        bor[v].ps = k;
        bor[v].ps2 = cc;
    }
    bor[v].fl = i;
}

void bfs() {
    queue<int> q;
    for (int i = 0; i < A; ++i) {
        if (bor[0].go[i] == -1) {
            bor[0].go[i] = 0;
        } else {
            q.push(bor[0].go[i]);
        }
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (bor[v].ps == 0) {
            bor[v].sl = 0;
        } else {
            bor[v].sl = bor[bor[bor[v].ps].sl].go[bor[v].ps2];
        }
        if (bor[bor[v].sl].fl != -1) {
            bor[v].spl = bor[v].sl;
        } else {
            bor[v].spl = bor[bor[v].sl].spl;
        }
        for (int i = 0; i < A; ++i) {
            if (bor[v].go[i] == -1) {
                bor[v].go[i] = bor[bor[v].sl].go[i];
            } else {
                q.push(bor[v].go[i]);
            }
        }
    }
}

vector<pair<int, int>> qs[MAX2];
pair<int, int> to_ans[MAX2];
vector<int> g[MAX];
int num = 0;

void dfs(int v) {
    cl[v] = num;
    for (int to : g[v]) {
        if (cl[to] == 0) {
            dfs(to);
        }
    }
}

bool cmp(int a, int b) {
    if ((int)all[a].size() == (int)all[b].size()) {
        return a < b;
    }
    return (int)all[a].size() < (int)all[b].size();
}

signed main() {
    pows[0] = 1;
    for (int i = 1; i < 2 * MAX; ++i) {
        pows[i] = (pows[i - 1] * P) % MOD;
    }
    string t;
    cin >> t;
    reverse(t.begin(), t.end());
    vector<int> now;
    for (int i = 0; i < 26; ++i) {
        string _ = "";
        _.push_back((char)(i + 97));
        all[i] = _;
        add(all[i], i);
        now.push_back(i);
    }
    int n, k;
    cin >> n >> k;
    for (int i = 26; i < n + 26; ++i) {
        cin >> all[i];
        reverse(all[i].begin(), all[i].end());
        add(all[i], i);
        now.push_back(i);
    }
    sort(now.begin(), now.end(), cmp);
    bfs();
    ////cout << 0 << endl;
    for (int i = 0; i < k; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 0; i < n + 26; ++i) {
        if (cl[i] == 0) {
            num++;
            dfs(i);
        }
    }
    ////cout << 0 << endl;
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        --a; --b; --c; --d;
        a = ((int)t.size() - 1 - a);
        b = ((int)t.size() - 1 - b);
        c = ((int)t.size() - 1 - c);
        d = ((int)t.size() - 1 - d);
        qs[a].push_back({b, i});
        qs[c].push_back({d, i});
    }
    for (int i = 0; i < (int)t.size(); ++i) {
        sort(qs[i].begin(), qs[i].end());
    }
    for (int i : now) {
        all2[i].assign((int)all[i].size() + 1, 0);
        vector<int> vs((int)all[i].size());
        int v = 0;
        //cout << i << endl;
        for (int j = 0; j < (int)all[i].size(); ++j) {
            v = bor[v].go[all[i][j] - 'a'];
            if (bor[v].fl != -1) {
                vs[j] = v;
            } else {
                vs[j] = bor[v].spl;
            }
        }
        all2[i][(int)all[i].size()] = 0;
        all2[i][0] = cl[i];
        vs.back() = bor[vs.back()].spl;
        int cnt = 0;
        for (int j = (int)all[i].size() - 1; j > 0;) {
            int j2 = j - (int)all[bor[vs[j]].fl].size();
            for (int u = j; u > max(j2, 0ll); --u) {
                int x = u - j2 - 1;
                all2[i][u] = (all2[i][j + 1] + pows[cnt] * all2[bor[vs[j]].fl][x]) % MOD;
            }
            j = j2;
            cnt++;
        }
    }
    fill(to_ans, to_ans + q, pair<int, int>{-1, -1});
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < LN; ++j) {
            up[i][j] = -2;
        }
    }
    int st = 0;
    vector<int> vss((int)t.size() + 1);
    for (int i = 0; i < (int)t.size(); ++i) {
        st = bor[st].go[t[i] - 'a'];
        if (bor[st].fl != -1) {
            vss[i] = st;
        } else {
            vss[i] = bor[st].spl;
        }
        //cout << i << " " << bor[vss[i]].fl << endl;
        up[i][0] = i - (int)all[bor[vss[i]].fl].size();
        up2[i][0] = cl[bor[vss[i]].fl];
        for (int j = 1; j < LN; ++j) {
            if (up[i][j - 1] == -1 || up[up[i][j - 1]][j - 1] == -2) break;
            up[i][j] = up[up[i][j - 1]][j - 1];
            up2[i][j] = (up2[i][j - 1] + up2[up[i][j - 1]][j - 1] * pows[(1 << (j - 1))]) % MOD;
        }
        //cout << up2[i][2] << endl;
        for (auto [l, in] : qs[i]) {
            int hs = 0;
            int v = i;
            int cnt2 = 0;
            for (int j = LN - 1; j >= 0; --j) {
                if (v >= 0 && up[v][j] >= l - 1) {
                    //cout << "# " << v << " " << up[v][j] << endl;
                    hs = (hs + up2[v][j] * pows[cnt2]) % MOD;
                    v = up[v][j];
                    cnt2 += (1 << j);
                }
            }
            if (v > l - 1) {
                hs = (hs + all2[bor[vss[v]].fl][(int)all[bor[vss[v]].fl].size() - 1 - (v - l)] * pows[cnt2]) % MOD;
            }
            if (to_ans[in].first != -1) {
                to_ans[in].second = hs;
            } else {
                to_ans[in].first = hs;
            }
        }
    }
    for (int i = 0; i < q; ++i) {
        //cout << to_ans[i].first << " " << to_ans[i].second << endl;
        if (to_ans[i].first == to_ans[i].second) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
