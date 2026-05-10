#include<iostream>
#include<vector>
#include<string>
#include<map>

using namespace std;

struct for_bor{
    map<char, int> next;
    int leaf;
};

vector<for_bor> bor;
int sz = 0;

void newb() {
    map<char, int> p;
    bor.push_back({p, -1});
    for (int i = 0; i < 26; ++i) {
        bor[sz].next[char(i + 97)] = -1;
        bor[sz].leaf = -1;
    }
    ++sz;
}

void add_string(string s, int num) {
    int v = 0;
    for (int i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (bor[v].next[c] == -1) {
            newb();
            bor[v].next[c] = sz - 1;
        }
        v = bor[v].next[c];
    }
    bor[v].leaf = num;
}

vector<int> tin(2.5e6);
vector<int> tout(2.5e6);
int timer = 0;

void dfs(int v) {
    if (bor[v].leaf != -1) {
        tin[bor[v].leaf] = timer++;
    }
    for (int i = 0; i < 26; ++i) {
        if (bor[v].next[char(i + 97)] != -1) {
            dfs(bor[v].next[char(i + 97)]);
        }
    }
    if (bor[v].leaf != -1) {
        tout[bor[v].leaf] = timer++;
    }
}

int main() {
    int m;
    cin >> m;
    vector<string> s(m);
    for (int i = 0; i < m; ++i) {
        cin >> s[i];
    }
    int k;
    cin >> k;
    vector<int> x(k);
    for (int i = 0; i < k; ++i) {
        cin >> x[i];
    }
    newb();
    for (int i = 0; i < m; ++i) {
        add_string(s[i], i);
    }
    dfs(0);
    int l = 0, r = 0;
    pair<int, int> ans = {-1, -1};
    int maxm = 0;
    while (l < k && r < k - 1) {
        int v = x[r] - 1;
        int to = x[r + 1] - 1;
        if (tin[v] < tin[to] && tout[v] > tout[to]) {
            r += 1;
        } else {
            if (r - l + 1 > maxm) {
                maxm = r - l + 1;
                ans = {l, r};
            }
            l = r + 1;
            r = l;
        }
    }
    if (r - l + 1 > maxm) {
        maxm = r - l + 1;
        ans = {l, r};
    }
    cout << ans.first + 1 << " " << ans.second + 1 << endl;
    return 0;
}
