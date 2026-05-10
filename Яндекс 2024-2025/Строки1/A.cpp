#include<bits/stdc++.h>

using namespace std;

const int A = 26;

struct Node {
    vector<int> fl;
    int go[A];
    int sl, spl, pr, pr2;
    Node() {
        sl = 0;
        spl = 0;
        pr = 0;
        pr2 = -1;
        for (int i = 0; i < A; ++i) {
            go[i] = -1;
        }
    }
};

vector<Node> bor(1);

void add(string t, int u) {
    int v = 0;
    for (char c : t) {
        int cc = (int)c - 97;
        if (bor[v].go[cc] == -1) {
            bor[v].go[cc] = (int)bor.size();
            bor.push_back(Node());
        }
        int k = v;
        v = bor[v].go[cc];
        bor[v].pr = k;
        bor[v].pr2 = cc;
    }
    bor[v].fl.push_back(u);
}

void stat() {
    queue<int> q;
    for (int i = 0; i < A; ++i) {
        if (bor[0].go[i] != -1) {
            q.push(bor[0].go[i]);
            //cout << bor[0].go[i] << endl;
        } else {
            bor[0].go[i] = 0;
        }
    }
    //cout << "#" << endl;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        //cout << v << endl;
        if (bor[v].pr != 0) {
            bor[v].sl = bor[bor[bor[v].pr].sl].go[bor[v].pr2];
        } else {
            bor[v].sl = 0;
        }
        if ((int)bor[bor[v].sl].fl.size() != 0) {
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

signed main() {
    string s;
    cin >> s;
    int n;
    cin >> n;
    vector<int> sz(n);
    for (int i = 0; i < n; ++i) {
        string t;
        cin >> t;
        add(t, i);
        sz[i] = (int)t.size();
    }
    stat();
    int v = 0;
    vector<vector<int>> ans(n);
    for (int i = 0; i < (int)s.size(); ++i) {
        v = bor[v].go[(int)s[i] - 97];
        int u = v;
        while (u != 0) {
            for (auto x : bor[u].fl) {
                ans[x].push_back(i - sz[x] + 1);
            }
            u = bor[u].spl;
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << (int)ans[i].size() << " ";
        for (int j : ans[i]) {
            cout << j + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}
