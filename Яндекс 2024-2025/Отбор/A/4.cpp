#include<bits/stdc++.h>

//#define int long long

using namespace std;

mt19937 rnd(228);

struct Node {
    int x, y, cnt, ch;
    Node *l, *r, *p;
    Node (int x1) {
        x = x1;
        y = rnd();
        cnt = 1;
        l = nullptr;
        r = nullptr;
        p = nullptr;
        ch = -1;
    }
};

int get_sz(Node* r) {
    if (r == nullptr) return 0;
    return r->cnt;
}

void upd(Node* r) {
    int cnt = 1;
    cnt += get_sz(r->l);
    cnt += get_sz(r->r);
    r->cnt = cnt;
}

Node* merge(Node* r1, Node* r2) {
    if (r1 != nullptr) {
        r1->p = nullptr;
        r1->ch = -1;
    }
    if (r2 != nullptr) {
        r2->p = nullptr;
        r2->ch = -1;
    }
    if (r1 == nullptr) return r2;
    if (r2 == nullptr) return r1;
    if (r1->y < r2->y) {
        Node *r3 = merge(r1, r2->l);
        r2->l = r3;
        if (r3 != nullptr) {
            r3->p = r2;
            r3->ch = 0;
        }
        upd(r2);
        return r2;
    } else {
        Node *r3 = merge(r1->r, r2);
        r1->r = r3;
        if (r3 != nullptr) {
            r3->p = r1;
            r3->ch = 1;
        }
        upd(r1);
        return r1;
    }
}

pair<Node*, Node*> split_k(Node* r, int k) {
    if (r != nullptr) {
        r->p = nullptr;
        r->ch = -1;
    }
    //assert(r == nullptr && k);
    //if (r == nullptr) return {nullptr, nullptr};
    if (k == 0) return {nullptr, r};
    if (k == get_sz(r)) return {r, nullptr};
    //assert(!(r == nullptr));
    //////cout << r->x << " " << k << endl;
    if (get_sz(r->l) >= k) {//???
        auto [r1, r2] = split_k(r->l, k);
        r->l = r2;
        if (r2 != nullptr) {
            r2->p = r;
            r2->ch = 0;
        }
        upd(r);
        return {r1, r};
    } else {
        auto [r1, r2] = split_k(r->r, k - get_sz(r->l) - 1);
        r->r = r1;
        if (r1 != nullptr) {
            r1->p = r;
            r1->ch = 1;
        }
        upd(r);
        return {r, r2};
    }
}

int find_num(Node* r) {
    if (r->p == nullptr) return get_sz(r->l);
    if (r->ch == 0) {
        return find_num(r->p) - 1 - get_sz(r->r);
    }
    return find_num(r->p) + get_sz(r->l) + 1;
}

Node* get_root(Node* r) {
    if (r->p == nullptr) return r;
    return get_root(r->p);
}

const int MAX = 2e5 + 1, MOD = 998244353, LN = 21;

Node* mp[MAX * LN + 5];
map<pair<int, int>, Node*> mp2;

int in_one(int a, int b) {
    //cout << mp[a]->x << " " << mp[a]->cnt << " " << mp[b]->x << " " << mp[b]->cnt << endl;
    return get_root(mp[a]) == get_root(mp[b]);
}

void print_tree(Node* a) {
    if (a == nullptr) return;
    print_tree(a->l);
    //cout << a->x << " ";
    print_tree(a->r);
}

void add(int a, int b) {
    int whr = find_num(mp[a]);
    int whr2 = find_num(mp[b]);
    if (whr < 0) {
        //cout << whr << " ";
        //cout << a << " " << get_sz(get_root(mp[a])) << " ";
        print_tree(get_root(mp[a]));
        exit(0);
    }
    //assert(whr2 >= 0);
    //assert(get_sz(get_root(mp[a])) >= whr);
    auto [a1, a2] = split_k(get_root(mp[a]), whr);
    //assert(get_sz(get_root(mp[b])) >= whr2);
    auto [b1, b2] = split_k(get_root(mp[b]), whr2);
    auto add = new Node(a);
    mp2[{a, b}] = add;
    mp[a] = add;
    auto a3 = merge(a1, add);
    auto add2 = new Node(b);
    mp[b] = add2;
    mp2[{b, a}] = add2;
    auto b3 = merge(b1, add2);
    assert(get_sz(b2) > 0);
    auto [b4, _] = split_k(b2, get_sz(b2) - 1);
    auto [b5, b6] = split_k(b3, 1);
    mp[b5->x] = b5;
    auto root = merge(merge(a3, b4), merge(merge(b5, b6), a2));
    ////cout << get_sz(root) << endl;
}

void del(int a, int b) {
    auto r1 = mp2[{a, b}];
    auto r2 = mp2[{b, a}];
    int whr = find_num(r1);
    assert(whr >= 0);
    int whr2 = find_num(r2);
    assert(whr2 >= 0);
    if (whr2 < whr) {
        swap(whr, whr2);
        swap(a, b);
    }
    assert(whr <= whr2);
    auto r = get_root(r1);
    assert(get_sz(r) >= whr2 + 1);
    auto [a0, a3] = split_k(r, whr2 + 1);
    assert(get_sz(a3) >= 1);
    auto [a5, a6] = split_k(a3, 1);
    mp[a5->x] = a5;
    assert(get_sz(a0) >= whr + 1);
    auto [a1, a2] = split_k(a0, whr + 1);
    assert(get_sz(a1) > 0);
    auto [a4, _] = split_k(a1, get_sz(a1) - 1);
    auto rr = merge(a4, merge(a5, a6));
}

set<pair<int, int>> gr[LN], f[LN];
map<pair<int, int>, int> mp3;
pair<int, int> mp4[MAX];
int n;

void add2(int a, int b) {
    mp3[{a, b}] = 0;
    gr[0].insert({a, b});
    if (!in_one(a, b)) {
        add(a, b);
        f[0].insert({a, b});
    }
}

void del2(int a, int b) {
    int num = mp3[{a, b}];
    ////cout << num << endl;
    if (f[num].find({a, b}) == f[num].end()) {
        gr[num].erase({a, b});
        return;
    }
    for (int i = 0; i <= num; ++i) {
        f[i].erase({a, b});
        gr[i].erase({a, b});
        del(a + n * i, b + n * i);
    }
    for (int i = num; i >= 0; --i) {
        int sz1 = get_sz(get_root(mp[a + n * i])), sz2 = get_sz(get_root(mp[b + n * i]));
        if (sz1 > sz2) {
            swap(a, b);
        }
        for (auto [a2, b2] : f[i]) {
            if (in_one(a2 + n * i, a + n * i)) {
                if (f[i + 1].find({a2, b2}) == f[i + 1].end()) {
                    add(a2 + n * (i + 1), b2 + n * (i + 1));
                    mp3[{a2, b2}] = i + 1;
                    f[i + 1].insert({a2, b2});

                }
            }
        }
        vector<pair<int, int>> to_remove;
        for (auto [a2, b2] : gr[i]) {
            if (f[i].find({a2, b2}) != f[i].end()) continue;
            if (!(in_one(a2 + n * i, a + n * i) && in_one(b2 + n * i, a + n * i))) {
                ////cout << "# " << a2 << " " << b2 << endl;
                //gr[i].erase({a2, b2});
                to_remove.push_back({a2, b2});
                mp3[{a2, b2}] = i + 1;
                gr[i + 1].insert({a2, b2});
            } else {
                ////cout << "# " <<  a2 << " " << b2 << endl;
                for (int j = 0; j <= i; ++j) {
                    f[j].insert({a2, b2});
                    add(a2 + n * j, b2 + n * j);
                }
                for (auto to : to_remove) {
                    gr[i].erase(to);
                }
                return;
            }
        }
    }
}

const int MAX2 = 5e5 + 1;
vector<int> g[MAX2];
int used[MAX2];
int m;

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

void dfs(int v) {
    used[v] = 1;
    int cnt = 0;
    for (int to : g[v]) {
        if (used[to]) continue;
        dfs(to);
    }
}

signed main() {
    /*cin >> n >> m;
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
        mp4[i] = {a - m, b - m};
    }
    int num = 0;
    for (int i = 0; i < n + m; ++i) {
        if (!used[i]) {
            num += 1;
            dfs(i);
        }
    }
    int ans = fpow(2, num - 1);
    for (int i = 0; i < MAX * LN + 5; ++i) {
        mp[i] = new Node(i);
    }
    for (int i = m - 1; i >= 0; --i) {
        add2(mp4[i].first, mp4[i].second, i);
    }
    int cnt = 1;
    int last = m;
    vector<pair<int, int>> now;
    int j = 0;
    for (int i = m - 1; i >= 0; --i) {
        if (mp4[i].first == mp4[i].second) break;
        del2(mp4[i].first, mp4[i].second, i);
        now.push_back({mp4[i].first, mp4[i].second});
        while (j < (int)now.size() && !(in_one(now[j].first, now[j].second))) {
            j++;
        }
        if (j == (int)now.size()) {
            cnt += 1;
            for (int k = i; k < last; ++k) {
                add2(mp4[k].first, mp4[k].second, k);
            }
            now.clear();
            last = i;
            j = 0;
        }
    }*/
    int n;
    cin >> n;
    for (int i = 0; i < n * LN; ++i) {
        mp[i] = new Node(i);
    }
    set<pair<int, int>> st;
    int q;
    cin >> q;
    int last = 0;
    int cnt = 0;
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        int a, b;
        cin >> a >> b;
        --a; --b;
        a = (a + last) % n;
        b = (b + last) % n;
        if (a > b) {
            swap(a, b);
        }
        //cout << t << " " << a << " " << b << endl;
        if (t == 1) {
            if (st.find({a, b}) == st.end()) {
                add2(a, b);
                st.insert({a, b});
            } else {
                ////cout << "#" << endl;
                del2(a, b);
                st.erase({a, b});
            }
        } else {
            cnt++;
            last = in_one(a, b);
            cout << last;
        }
    }
    //////cout << mult(cnt, ans) << endl;
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
