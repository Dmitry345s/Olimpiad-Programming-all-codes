#include<bits/stdc++.h>

using namespace std;

const int MAX = 3e5 + 1;
vector<pair<int, int>> g[MAX];
vector<int> ans[MAX];

bool ch(int x, int m) {
    set<pair<int, int>> st;
    for (int i = 1; i <= m; ++i) {
        ans[i].clear();
        for (auto u : g[i]) {
            st.insert(u);
        }
        while (!st.empty() && (int)ans[i].size() < x) {
            if ((*st.begin()).first < i) return 0;
            ans[i].push_back((*st.begin()).second);
            st.erase(st.begin());
        }
    }
    return st.empty();
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int s, f;
        cin >> s >> f;
        g[s].push_back({f, i});
    }
    for (int i = 1; i <= m; ++i) {
        sort(g[i].begin(), g[i].end());
    }
    int l = 0, r = n;
    while (l + 1 < r) {
        int c = (l + r) / 2;
        if (ch(c, m)) {
            r = c;
        } else {
            l = c;
        }
    }
    ch(r, m);
    cout << r << endl;
    for (int i = 1; i <= m; ++i) {
        cout << (int)ans[i].size() << " ";
        for (int to : ans[i]) {
            cout << to + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}

/*const int MAX = 1e5, K = 100, NUM = (MAX + K - 1) / K, MX = 51;
int a[MAX];
int first[NUM][MX], last[NUM][MX];
long long pref[NUM][K + 1], suf[NUM][K + 1];

void update(int in, int x) {
    a[in] = x;
    int num = in / K;
    int l = num * K, r = (num + 1) * K;
    pref[num][0] = 0;
    for (int i = 0; i < MX; ++i) {
        last[num][i] = -1;
        first[num][i] = -1;
    }
    for (int i = l; i < r; ++i) {
        last[num][a[i]] = i - l;
        pref[num][i - l + 1] = (pref[num][i - l] | (1ll << a[i]));
    }
    suf[num][r] = 0;
    for (int i = r - 1; i >= l; --i) {
        first[num][a[i]] = i - l;
        suf[num][i - l] = (suf[num][i - l + 1] | (1ll << a[i]));
    }
}

int get(int k) {
    int l = 0, r = 0;
    int ans = 0;
    int cnt = 0;
    vector<int> mask(MX);
    while (r < NUM) {
        while (r < NUM) {
        if (l + 1 != r) {
            int right = 0, left = 0;
            vector<pair<int, int>> now;
            for (int i = 1; i <= k; ++i) {
                if (first)
            }
        } else {
            ans = min(ans, tans[l]);
        }
            int cnt2 = cnt;
            for (int i = k; i > 0; --i) {
                if ((suf[r][0] >> i) & 1) {
                    if (mask[i] == 0) {
                        cnt2++;
                    }
                }
            }
            if (cnt2 == k) {
                break;
            } else {
                for (int i = k; i > 0; --i) {
                    if ((suf[r][0] >> i) & 1) {
                        if (mask[i] == 0) {
                            cnt++;
                        }
                        mask[i]++;
                    }
                }
                r++;
            }
        }
        if (l < r) {
            for (int i = k; i > 0; --i) {
                if ((suf[l][0] >> i) & 1) {
                    mask[i]--;
                    if (mask[i] == 0) cnt--;
                }
            }
        }
        l++;
        r = max(r, l);
    }
}*/
