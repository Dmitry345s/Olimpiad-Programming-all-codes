#include<bits/stdc++.h>

using namespace std;

const long long MAX = 1e5 + 5;

long long tree[4 * MAX], update_tree[4 * MAX], tree2[4 * MAX];
long long a[MAX], p[MAX];
const long long INF = 2e9;

void build(long long v, long long l, long long r) {
    update_tree[v] = 0;
    if (l + 1 == r) {
        tree[v] = a[l];
        return;
    }
    long long m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = min(tree[2 * v], tree[2 * v + 1]);
}

void build2(long long v, long long l, long long r) {
    if (l + 1 == r) {
        tree2[v] = p[l];
        return;
    }
    long long m = (l + r) / 2;
    build2(2 * v, l, m);
    build2(2 * v + 1, m, r);
    tree2[v] = max(tree2[2 * v], tree2[2 * v + 1]);
}

void push(long long v) {
    long long x = update_tree[v];
    update_tree[v] = 0;
    tree[2 * v] += x;
    tree[2 * v + 1] += x;
    update_tree[2 * v + 1] += x;
    update_tree[2 * v] += x;
}

void update(long long v, long long l, long long r, long long ql, long long qr, long long x) {
    if (r <= ql || qr <= l) {
        return;
    }
    if (ql <= l && r <= qr) {
        tree[v] += x;
        update_tree[v] += x;
        return;
    }
    long long m = (l + r) / 2;
    push(v);
    update(2 * v, l, m, ql, qr, x);
    update(2 * v + 1, m, r, ql, qr, x);
    tree[v] = min(tree[2 * v], tree[2 * v + 1]);
}

void update2(int v, int l, int r, int in, int x) {
    if (l + 1 == r) {
        tree2[v] = x;
        return;
    }
    int m = (l + r) / 2;
    if (in < m) {
        update2(2 * v, l, m, in, x);
    } else {
        update2(2 * v + 1, m, r, in, x);
    }
    tree2[v] = max(tree2[2 * v], tree2[2 * v + 1]);
}

long long get(long long v, long long l, long long r, long long ql, long long qr) {
    if (r <= ql || qr <= l) {
        return INF;
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    long long m = (l + r) / 2;
    push(v);
    return min(get(2 * v, l, m, ql, qr), get(2 * v + 1, m, r, ql, qr));
}

long long get2(long long v, long long l, long long r, long long ql, long long qr) {
    if (ql == qr) return 0;
    if (r <= ql || qr <= l) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return tree2[v];
    }
    long long m = (l + r) / 2;
    return max(get2(2 * v, l, m, ql, qr), get2(2 * v + 1, m, r, ql, qr));
}

void to_z(long long v, long long l, long long r, vector<long long> & a) {
    if (l + 1 == r) {
        if (tree[v] == 0) {
            a.push_back(l);
            tree[v] = INF;
        }
        return;
    }
    long long m = (l + r) / 2;
    push(v);
    if (tree[2 * v] == 0) {
        to_z(2 * v, l, m, a);
    }
    if (tree[2 * v + 1] == 0) {
        to_z(2 * v + 1, m, r, a);
    }
    tree[v] = min(tree[2 * v], tree[2 * v + 1]);
}

long long ans = 0;

void to_ans(long long l, long long r, long long n) {
    if (l == r) return;
    long long minm = get(1, 0, n, l, r);
    long long maxm = get2(1, 0, n, l, r);
    set<pair<long long, long long>> st;
    st.insert({r, maxm});
    st.insert({l - 1, 0});
    long long sum = maxm;
    while (true) {
        minm = get(1, 0, n, l, r);
        ans += minm * maxm;
        update(1, 0, n, l, r, -minm);
        vector<long long> new_z;
        to_z(1, 0, n, new_z);
        for (auto in : new_z) {
            update2(1, 0, n, in, 0);
        }
        if (sum < maxm) break;
    }
    auto it = st.begin(), it2 = it;
    ++it2;
    for (long long i = 0; i < (long long)st.size() - 1; ++i) {
        to_ans((*it).first + 1, (*it2).first, n);
        ++it;
        ++it2;
    }
}

signed main() {
    long long n;
    cin >> n;
    for (long long i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (long long i = 0; i < n; ++i) {
        cin >> p[i];
    }
    build(1, 0, n);
    build2(1, 0, n);
    to_ans(0, n, n);
    cout << ans << endl;
    return 0;
}
/*
            auto it2 = st.upper_bound({in, INF});
            auto it = it2--;
            auto [whr, wht] = *it;
            auto [whr2, wht2] = *it2;
            st.erase(it);
            sum -= wht;
            long long new1 = get2(1, 0, n, whr2 + 1, in);
            long long new2 = get2(1, 0, n, in + 1, whr);
            sum += new1;
            sum += new2;
            st.insert({in, new1});
            st.insert({whr, new2});
*/

#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 1e6, MOD = 998244353;
vector<int> g[MAX];
int fup[MAX], used[MAX], h[MAX];
int to_ans = 0;
vector<vector<int>> now;
int whr[MAX];
int n, m;

int mult(int a, int b) {
    return (1ll * a * b) % MOD;
}

int fpow(int a, int x) {
    int ans = 1;
    while (x >= 1) {
        if (x % 2 == 1) {
            ans = mult(ans, a);
        }
        a = mult(a, a);
        x /= 2;
    }
    return ans;
}

void dfs(int v, int p) {
    used[v] = 1;
    h[v] = h[p] + 1;
    fup[v] = h[v];
    int cnt = 0;
    for (int to : g[v]) {
        if (p == to) continue;
        if (used[to]) {
            fup[v] = min(fup[v], h[to]);
            continue;
        }
        cnt++;
        dfs(to, v);
        fup[v] = min(fup[v], fup[to]);
        if (v != p) {
            if ((fup[to] >= h[v]) && v < m) {
                whr[v] = -1;
            }
        }
    }
    if (v == p) {
        if (cnt > 1 && v < m) {
            whr[v] = -1;
        }
    }
}

int fup2[MAX], used2[MAX], h2[MAX];
int whr2[MAX];

void dfs2(int v, int p) {
    if (whr[v] == -1) return;
    used2[v] = 1;
    h2[v] = h2[p] + 1;
    fup2[v] = h2[v];
    int cnt = 0;
    for (int to : g[v]) {
        if (p == to) continue;
        if (whr[to] == -1) continue;
        if (used2[to]) {
            fup2[v] = min(fup2[v], h2[to]);
            continue;
        }
        cnt++;
        dfs2(to, v);
        fup2[v] = min(fup2[v], fup2[to]);
        if (v != p) {
            if (!(fup2[to] < h2[v]) && v >= m) {
                whr2[v] = -1;
            }
        }
    }
    if (v == p) {
        if (cnt > 1 && v >= m) {
            whr2[v] = -1;
        }
    }
}

int used3[MAX];

void dfs3(int v, int p, int num) {
    if (whr[v] == -1) return;
    used3[v] = 1;
    if (whr2[v] != -1) {
        whr2[v] = num;
        if (v < m) {
            now[num].push_back(v);
        }
    }
    for (int to : g[v]) {
        if (p == to) continue;
        if (whr[to] == -1) continue;
        if (used3[to]) {
            if (whr2[v] != -1 && whr2[to] != -1) {
                whr2[to] = num;
                if (to < m) {
                    now[num].push_back(to);
                }
            }
        } else {
            //cout << v << " " << to << " " << fup2[to] << " " << h2[v] << endl;
            if ((v != p && fup2[to] >= h2[v])){
                now.push_back({});
                dfs3(to, v, (int)now.size() - 1);
            } else {
                dfs3(to, v, num);
            }
        }
    }
}

signed main() {
    cin >> n >> m;
    for (int i = 0; i < n - 1; ++i) {
        int p;
        cin >> p;
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        a += m;
        b += m;
        g[i].push_back(a);
        g[i].push_back(b);
        g[a].push_back(i);
        g[b].push_back(i);
    }
    int num = 0;
    for (int i = 0; i < n + m; ++i) {
        ////cout << i << " " << used[i] << endl;
        if (!used[i]) {
            num += 1;
            h[i] = -1;
            dfs(i, i);
        }
    }
    for (int i = 0; i < n + m; ++i) {
        //cout << whr[i] << " ";
    }
    //cout << endl;
    for (int i = 0; i < n + m; ++i) {
        if (!used2[i]) {
            h2[i] = -1;
            dfs2(i, i);
        }
    }
    for (int i = 0; i < n + m; ++i) {
        //cout << whr2[i] << " ";
    }
    //cout << endl;
    for (int i = 0; i < m; ++i) {
        if (!used3[i]) {
            now.push_back({});
            dfs3(i, i, (int)now.size() - 1);
        }
    }
    for (int i = 0; i < n + m; ++i) {
        //cout << whr2[i] << " ";
    }
    //cout << endl;
    ////cout << num << endl;
    int ans = fpow(2, num - 1);
    ////cout << ans << endl;
    set<int> st;
    for (int i = 0; i < (int)now.size(); ++i) {
        sort(now[i].begin(), now[i].end());
        now[i].erase(unique(now[i].begin(), now[i].end()), now[i].end());
        for (int j = 0; j < (int)now[i].size(); ++j) {
            //cout << "! " << now[i][j] << " ";
            st.insert(now[i][j]);
        }
        //cout << endl;
    }
    st.insert(-1);
    int last = m;
    int cnt = 0;
    while (true) {
        if (st.empty()) break;
        int now_last = (*(--st.end()));
        cnt += (last - now_last);
        int now_minm = now_last;
        //cout << now_last << endl;
        if (now_last == -1) break;
        int flag = 1;
        while ((int)st.size() > 0 && (*(--st.end())) >= now_minm) {
            int hm = whr2[(*(--st.end()))];
            //cout << hm << endl;
            if ((int)now[hm].size() <= 1) {
                flag = 0;
                break;
            }
            st.erase(now[hm].back());
            now[hm].pop_back();
            now_minm = min(now_minm, now[hm].back());
            st.erase(now[hm].back());
            now[hm].pop_back();
        }
        if (!flag) break;
        last = now_minm;
        //cnt += 1;
    }
    cout << mult(cnt, ans) << endl;
    return 0;
}
/*
3
4
1 1
2 3
1 2
1 2
2 3*/

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

int tree1[4 * MAX], tree2[4 * MAX];

void update1(int v, int l, int r, int in, int x) {
    if (l + 1 == r) {
        tree1[v] = x;
        return;
    }
    int m = (l + r) / 2;
    if (in < m) {
        update1(2 * v, l, m, in, x);
    } else {
        update1(2 * v + 1, m, r, in, x);
    }
    tree1[v] = min(tree1[2 * v], tree1[2 * v + 1]);
}

int get1(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return 1e9;
    }
    if (ql <= l && r <= qr) {
        return tree1[v];
    }
    int m = (l + r) / 2;
    return min(get1(2 * v, l, m, ql, qr), get1(2 * v + 1, m, r, ql, qr));
}

void update2(int v, int l, int r, int in, int x) {
    if (l + 1 == r) {
        tree2[v] = x;
        return;
    }
    int m = (l + r) / 2;
    if (in < m) {
        update2(2 * v, l, m, in, x);
    } else {
        update2(2 * v + 1, m, r, in, x);
    }
    tree2[v] = min(tree2[2 * v], tree2[2 * v + 1]);
}

int get2(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return 1e9;
    }
    if (ql <= l && r <= qr) {
        return tree2[v];
    }
    int m = (l + r) / 2;
    return min(get2(2 * v, l, m, ql, qr), get2(2 * v + 1, m, r, ql, qr));
}

void update3(int v, int l, int r, int in, int x) {
    if (l + 1 == r) {
        tree1[v] = x;
        return;
    }
    int m = (l + r) / 2;
    if (in < m) {
        update3(2 * v, l, m, in, x);
    } else {
        update3(2 * v + 1, m, r, in, x);
    }
    tree1[v] = max(tree1[2 * v], tree1[2 * v + 1]);
}

int get3(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return -1e9;
    }
    if (ql <= l && r <= qr) {
        return tree1[v];
    }
    int m = (l + r) / 2;
    return max(get3(2 * v, l, m, ql, qr), get3(2 * v + 1, m, r, ql, qr));
}

void update4(int v, int l, int r, int in, int x) {
    if (l + 1 == r) {
        tree2[v] = x;
        return;
    }
    int m = (l + r) / 2;
    if (in < m) {
        update4(2 * v, l, m, in, x);
    } else {
        update4(2 * v + 1, m, r, in, x);
    }
    tree2[v] = max(tree2[2 * v], tree2[2 * v + 1]);
}

int get4(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return -1e9;
    }
    if (ql <= l && r <= qr) {
        return tree2[v];
    }
    int m = (l + r) / 2;
    return max(get4(2 * v, l, m, ql, qr), get4(2 * v + 1, m, r, ql, qr));
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
    //st.insert({lcp[0], 0});
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
    //assert(n == 9);
    int last1 = (int)1e9, last2 = (int)2e9;
    int rans = 2e9;
    for (int i = 0; i < n; ++i) {
        if (st1.find(t[i]) != st1.end()) {
            last1 = i;
        }
        if (st2.find(t[i]) != st2.end()) {
            last2 = i;
        }
        rans = min(rans, 2 * (abs(last1 - last2) - 1));
    }
    assert(rans != 2e9);
    cout << rans + m + k << endl;
    /*vector<int> s = a;
    s.push_back(0);
    for (int i = 0; i < n; ++i) {
        s.push_back(t[i]);
    }
    s.push_back(-1);
    suf_mas_lcp(s);
    vector<int> ans1(n);
    int minm = 0;
    for (int i = 2; i < n2; ++i) {
        //cout << start[i] << endl;
        if (start[i] < m) {
            minm = 1e9;
        } else {
            minm = min(minm, lcp[i]);
            ans1[start[i] - m - 1] = minm;
        }
    }
    minm = 0;
    for (int i = n2 - 1; i >= 2; --i) {
        if (start[i] < m) {
            minm = lcp[i];
        } else {
            ans1[start[i] - m - 1] = max(ans1[start[i] - m - 1], minm);
            minm = min(minm, lcp[i]);
        }
    }
    s = b;
    s.push_back(0);
    for (int i = 0; i < n; ++i) {
        s.push_back(t[i]);
    }
    s.push_back(-1);
    suf_mas_lcp(s);
    vector<int> ans2(n);
    minm = 0;
    for (int i = 2; i < n2; ++i) {
        if (start[i] < k) {
            minm = 1e9;
        } else {
            minm = min(minm, lcp[i]);
            ans2[start[i] - k - 1] = minm;
        }
    }
    minm = 0;
    for (int i = n2 - 1; i >= 2; --i) {
        if (start[i] < k) {
            minm = lcp[i];
        } else {
            ans2[start[i] - k - 1] = max(ans2[start[i] - k - 1], minm);
            minm = min(minm, lcp[i]);
        }
    }
    /*vector<int> ans3;
    for (int i = 0; i < n; ++i) {
        if (ans2[i] != 0) {
            ans4.push_back(i + ans2[i] - 1);
        } else if (ans1[i] != 0) {
            ans3.push_back(i + ans1[i] - 1);
        }
    }
    int rans = 2e9;
    sort(ans3.begin(), ans3.end());
    sort(ans4.begin(), ans4.end());
    for (int i = 0; i < n; ++i) {
        if (ans1[i] != 0) {
            int j = upper_bound(ans4.begin(), an4.end(), i) - ans4.begin();
            j -= 1;
            if (0 <= j) {
                rans = min(rans, )
            }
        }
    }*/
    /*int rans = 1e9;
    fill(tree1, tree1 + 4 * MAX, 1e9);
    fill(tree2, tree2 + 4 * MAX, 1e9);
    for (int i = n - 1; i >= 0; --i) {
        if (ans1[i] != 0) {
            update1(1, 0, n, ans1[i], i);
            rans = min(rans, 2 * (get2(1, 0, n, ans1[i], n) - i - ans1[i]));
        } else if (ans2[i] != 0) {
            update2(1, 0, n, ans2[i], i);
            //cout << get1(1, 0, n, ans2[i], n) << endl;
            rans = min(rans, 2 * (get1(1, 0, n, ans2[i], n) - i - ans2[i]));
        }
        //cout << i << " " << rans << endl;
    }
    fill(tree1, tree1 + 4 * MAX, -1e9);
    fill(tree2, tree2 + 4 * MAX, -1e9);
    for (int i = 0; i < n; ++i) {
        if (ans1[i] != 0) {
            update3(1, 0, n, ans1[i], i);
            rans = min(rans, 2 * (i - get4(1, 0, n, ans1[i], n) - ans1[i]));
        } else if (ans2[i] != 0) {
            update4(1, 0, n, ans2[i], i);
            rans = min(rans, 2 * (i - get3(1, 0, n, ans2[i], n) - ans2[i]));
        }
    }*/
    //cout << rans + m + k << endl;
    return 0;
}

