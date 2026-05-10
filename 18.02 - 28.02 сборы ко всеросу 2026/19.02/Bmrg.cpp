#include <bits/stdc++.h>
using namespace std;


// #define int long long
using ld = double;

const int INF = 100000, MAXN = 501, MAXK = 70, MX = 1e9;

int dst[MAXK][MAXN][MAXN], dst1[MAXK][MAXK];
pair<int, int> st;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


int calc(vector<int>& perm, vector<pair<int, int>>& pos) {
    int sz = (int)pos.size();
    vector<int> dp((int)perm.size() + 1);
    for (int i = 1; i <= (int)perm.size(); i++) {
        dp[i] = dp[i - 1] + 2 * dst1[sz - 1][perm[i - 1]];
        if (i > 1) {
            dp[i] = min(dp[i],
                dp[i - 2] +
                dst1[sz - 1][perm[i - 1]] +
                dst1[sz - 1][perm[i - 2]] +
                dst1[perm[i - 1]][perm[i - 2]]);
        }
    }
    return dp.back();
}

ld rd() {
    int a = rng() % MX;
    return (ld)a / (ld)MX;
}

const int MAX = 100;
int f[MAX][MAX];

int solve1(int n, int m, int k, vector<vector<char>>& v) {
    vector<pair<int, int>> pos;
    int fre =0 ;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (v[i][j] == 'X') {
                pos.push_back({i, j});
            }
            if (v[i][j] == 'S') {
                st = {i, j};
            }
        }
    }
    pos.push_back(st);
    for (int i = 0; i < (int)pos.size(); i++) {
        queue<pair<int, int>> q;
        q.push(pos[i]);
        dst[i][pos[i].first][pos[i].second] = 0;
        while (!q.empty()) {
            auto [a, b] = q.front();
            q.pop();
            if (a && v[a - 1][b] != '#' && dst[i][a - 1][b] == INF) {
                dst[i][a - 1][b] = dst[i][a][b] + 1;
                q.push({a - 1, b});
            }
            if (b && v[a][b - 1] != '#' && dst[i][a][b - 1] == INF) {
                dst[i][a][b - 1] = dst[i][a][b] + 1;
                q.push({a, b - 1});
            }
            if (a + 1 < n && v[a + 1][b] != '#' && dst[i][a + 1][b] == INF) {
                dst[i][a + 1][b] = dst[i][a][b] + 1;
                q.push({a + 1, b});
            }
            if (b + 1 < m && v[a][b + 1] != '#' && dst[i][a][b + 1] == INF) {
                dst[i][a][b + 1] = dst[i][a][b] + 1;
                q.push({a, b + 1});
            }
        }
        for (int j = i + 1; j < (int)pos.size(); j++) {
            dst1[i][j] = dst[i][pos[j].first][pos[j].second];
            dst1[j][i] = dst1[i][j];
        }
    }
    for (int i = 0; i < k + 1; ++i) {
        for (int j = 0; j < k + 1; ++j) {
            f[i][j] = dst1[i][j];
        }
    }
    for (int i = 0; i < (int)pos.size(); i++) {
        if (dst[i][st.first][st.second] == INF) {
            cout << -1 << '\n';
            exit(0);
        }
    }
    int BST = INF;
    for (int _ = 0; _ < 10; _++) {
        vector<int> perm(k);
        for (int i = 0; i < k; i++) {
            perm[i] = i;
        }
        ld T = 1;
        if (_) shuffle(perm.begin(), perm.end(), rng);
        int cura = calc(perm, pos);
        for (int _ = 0; _ < 15000; _++) {
            T *= 0.998;
            int f = rng() % k, s = rng() % k;
            swap(perm[f], perm[s]);
            int ca = calc(perm, pos);
            BST = min(BST, ca);
            if (ca < cura || exp((cura - ca) / T) > rd()) {
                cura = ca;
            } else {
                swap(perm[f], perm[s]);
            }
        }
        // if (!_) cout  q   << T << '\n';
    }
    return BST;
}

const ld C = 0.999;


int solve(int k) {
    int rans = INF;
    int cnt = 1300;
    while (cnt > 0) {
        int nans = 0;
        vector<int> go(k);
        for (int i = 0; i < k; i += 2) {
            go[i] = i + 1;
            go[i + 1] = i;
            nans += f[i][i + 1];
        }
        rans = min(rans, nans);
        if (k == 2) return rans;
        ld T = 1;
        int cnt2 = 10000;
        while (cnt2 > 0) {
            T *= C;
            int y1 = rng() % k;
            int y2 = rng() % k;
            cnt2--;
            if (y1 == y2 || y1 == go[y2]) continue;
            int trans = nans - f[y1][go[y1]] - f[y2][go[y2]] + f[y1][go[y2]] + f[y2][go[y1]];
            if (trans < nans || exp((nans - trans) / T) - rd() > 0) {
                nans = trans;
                swap(go[y1], go[y2]);
                go[go[y1]] = y1;
                go[go[y2]] = y2;
            }
            rans = min(rans, nans);
        }
        //cout << T << endl;
        cnt--;
    }
    return rans;
}



int solve2(int n, int m, int k, vector<vector<char>>& all) {
    int is, js;
    vector<pair<int, int>> sp;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (all[i][j] == 'S') {
                sp.push_back({i, j});
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (all[i][j] == 'X') {
                sp.push_back({i, j});
            }
        }
    }
    /*int alldist[k + 1][n][m];
    for (int i = 0; i < k + 1; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int u = 0; u < m; ++u) {
                alldist[i][j][u] = INF;
            }
        }
    }*/
    /*int cnt = 0;
    for (auto [stx, sty] : sp) {
        alldist[cnt][stx][sty] = 0;
        queue<pair<int, int>> q;
        q.push({stx, sty});
        vector<pair<int, int>> go = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        while (!q.empty()) {
            auto [vx, vy] = q.front();
            q.pop();
            for (auto [dx, dy] : go) {
                int nx = vx + dx;
                int ny = vy + dy;
                if (nx < 0 || nx >= n || ny < 0 || ny >= m || all[nx][ny] == '#') continue;
                if (alldist[cnt][nx][ny] == INF) {
                    q.push({nx, ny});
                    alldist[cnt][nx][ny] = alldist[cnt][vx][vy] + 1;
                }
            }
        }
        cnt++;
    }*/
    int ans = 0;
    for (int i = 0; i < k; ++i) {
        ans += f[k][i];
    }
    if (k % 2 == 0) {
        /*for (int i = 0; i < k; ++i) {
            for (int j = 0; j < k; ++j) {
                f[i][j] = f[]
                if (f[i][j] == INF) {
                    cout << -1 << endl;
                    exit(0);
                }
            }
        }*/
        ans += solve(k);
    } else {
        /*for (int i = 0; i < k + 1; ++i) {
            for (int j = 0; j < k + 1; ++j) {
                f[i][j] = alldist[i][sp[j].first][sp[j].second];
                if (f[i][j] == INF) {
                    cout << -1 << endl;
                    exit(0);
                }
            }
        }*/
        ans += solve(k + 1);
    }
    return  ans;
}

signed main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("out1.txt", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    for (int i = 0; i < MAXK; i++) {
        for (int j= 0 ; j < MAXN; j++) {
            fill(dst[i][j], dst[i][j] + MAXN, INF);
        }
    }
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<char>> v(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> v[i][j];
        }
    }
    int a = solve1(n, m, k, v);
    int b = solve2(n, m, k, v);
    //cout << a << " " << b << endl;
    cout << min(a, b) << endl;
}
