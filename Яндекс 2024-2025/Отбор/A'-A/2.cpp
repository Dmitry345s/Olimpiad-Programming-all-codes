#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 5e5 + 5;
int start[MAX], classid[MAX], cnt[MAX], pref[MAX], mem[MAX], ans[MAX], lcp[MAX];
int n2;

int mod(int x) {
    if (x < 0) return x + n2;
    if (x >= n2) return x - n2;
    return x;
}

void count_sort() {
    fill(cnt, cnt + n2, 0);
    for (int i = 0; i < n2; ++i) {
        cnt[classid[i]]++;
    }
    pref[0] = 0;
    for (int i = 1; i < n2; ++i) {
        pref[i] = pref[i - 1] + cnt[i - 1];
    }
    for (int i = 0; i < n2; ++i) {
        ans[pref[classid[start[i]]]++] = start[i];
    }
}

void suf_mas_lcp(vector<int> s3) {
    n2 = (int)s3.size();
    vector<pair<int, int>> u;
    for (int i = 0; i < n2; ++i) {
        u.push_back({s3[i], i});
    }
    sort(u.begin(), u.end());
    int cnt2 = 0;
    for (int i = 0; i < n2; ++i) {
        start[i] = u[i].second;
        classid[start[i]] = cnt2;
        if (i < n2 - 1 && u[i].first != u[i + 1].first) cnt2++;
    }
    int now = 0;
    while ((1 << now) < n2) {
        for (int i = 0; i < n2; ++i) {
            start[i] = mod(start[i] - (1 << now));
        }
        count_sort();
        for (int i = 0; i < n2; ++i) {
            start[i] = ans[i];
            mem[i] = classid[i];
        }
        classid[start[0]] = 0;
        for (int i = 1; i < n2; ++i) {
            classid[start[i]] = classid[start[i - 1]];
            pair<int, int> a1 = {mem[start[i]], mem[mod(start[i] + (1 << now))]};
            pair<int, int> a2 = {mem[start[i - 1]], mem[mod(start[i - 1] + (1 << now))]};
            if (a1 != a2) classid[start[i]]++;
        }
        now++;
    }
    int k2 = 0;
    for (int i = 0; i < n2; ++i) {
        int j = classid[i];
        if (j == 0) {
            lcp[j] = 0;
            continue;
        }
        int p = start[j - 1];
        while (s3[i + k2] == s3[p + k2]) k2++;
        lcp[j] = k2;
        k2 = max(k2 - 1, 0ll);
    }
}

vector<int> g[MAX];

vector<int> bfs(vector<int> a, int n) {
    vector<int> dist(n + 1, 1e9);
    queue<int> q;
    for (int i = 0; i < (int)a.size(); ++i) {
        dist[a[i]] = 0;
        q.push(a[i]);
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g[v]) {
            if (dist[to] > dist[v] + 1) {
                q.push(to);
                dist[to] = dist[v] + 1;
            }
        }
    }
    return dist;
}

signed main() {
    /*ios_base::sync_with_stdio(0);
    cin.tie(0);
    //cout.tie(0);*/
    int n;
    cin >> n;
    vector<int> t(n);
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }
    int m;
    cin >> m;
    vector<int> a(m);
    set<int> st1;
    for (int i = 0; i < m; ++i) {
        cin >> a[i];
        st1.insert(a[i]);
    }
    int k;
    cin >> k;
    vector<int> b(k);
    set<int> st2;
    for (int i = 0; i < k; ++i) {
        cin >> b[i];
        st2.insert(b[i]);
    }
    vector<int> s3 = a;
    s3.push_back(0);
    for (int i = 0; i < k; ++i) {
        s3.push_back(b[i]);
    }
    s3.push_back(-1);
    suf_mas_lcp(s3);
    set<pair<int, int>> st;
    array<int, 2> to_ch = {0, 0};
    to_ch[start[2] < m] = 1;
    int r = 3;
    int ob = 0;
    for (int l = 2; l < n2; ++l) {
        st.erase({lcp[l], l});
        while (r < n2 && (!to_ch[0] || !to_ch[1])) {
            to_ch[start[r] < m]++;
            st.insert({lcp[r], r});
            r++;
        }
        if (!to_ch[0] || !to_ch[1]) break;
        ob = max(ob, (*st.begin()).first);
        to_ch[start[l] < m]--;
    }
    if (ob != 0) {
        cout << m + k - 2 * ob << endl;
        return 0;
    }
    vector<int> now;
    for (auto v : st1) {
        now.push_back(v);
    }
    for (int i = 1; i < n - 1; ++i) {
        g[t[i - 1]].push_back(t[i]);
        g[t[i]].push_back(t[i - 1]);
        g[t[i + 1]].push_back(t[i]);
        g[t[i]].push_back(t[i + 1]);
    }
    vector<int> dist = bfs(now, n);
    int rans = 1e9;
    for (auto to : st2) {
        rans = min(rans, dist[to]);
    }
    cout << 2 * (rans - 1) + m + k << endl;
    return 0;
}
