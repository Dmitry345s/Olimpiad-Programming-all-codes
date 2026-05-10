#include<bits/stdc++.h>

using namespace std;

const int A = 26;

struct Node {
    vector<int> fl;
    int p;
    int pr, sl, spl;
    int to[A];
    int go[A];
    Node() {
        fl = {};
        p = -1;
        pr = -1;
        sl = -1;
        spl = -1;
        for (int i = 0; i < A; ++i) {
            to[i] = -1;
            go[i] = -1;
        }
    }
};

vector<Node> bor(1);

void add(string s, int v, int u) {
    for (auto c : s) {
        //cout << v << " " << (int)bor.size() << endl;
        int ch = (int)c - 97;
        if (bor[v].to[ch] == -1) {
            bor.push_back(Node());
            bor[v].to[ch] = (int)bor.size() - 1;
            bor.back().pr = v;
            bor.back().p = ch;
        }
        v = bor[v].to[ch];
    }
    bor[v].fl.push_back(u);
}

void bfs() {
    queue<int> q;
    for (int i = 0; i < A; ++i) {
        if (bor[0].to[i] != -1) {
            q.push(bor[0].to[i]);
            bor[0].go[i] = bor[0].to[i];
        } else {
            bor[0].go[i] = 0;
        }
    }
    bor[0].sl = 0;
    bor[0].spl = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (bor[v].pr != 0) {
            bor[v].sl = bor[bor[bor[v].pr].sl].go[bor[v].p];
        } else {
            bor[v].sl = 0;
        }
        if ((int)bor[bor[v].sl].fl.size() != 0) {
            bor[v].spl = bor[v].sl;
        } else {
            bor[v].spl = bor[bor[v].sl].spl;
        }
        //cout << v << " " << bor[v].sl << " " << bor[v].spl << endl;
        for (int i = 0; i < A; ++i) {
            if (bor[v].to[i] != -1) {
                bor[v].go[i] = bor[v].to[i];
                continue;
            }
            bor[v].go[i] = bor[bor[v].sl].go[i];
        }
        for (int i = 0; i < A; ++i) {
            if (bor[v].to[i] == -1) continue;
            q.push(bor[v].to[i]);
        }
    }
}

signed main() {
    string s;
    cin >> s;
    int n;
    cin >> n;
    vector<int> allstr(n);
    for (int i = 0; i < n; ++i) {
        string now;
        cin >> now;
        allstr[i] = (int)now.size();
        add(now, 0, i + 1);
    }
    bfs();
    int now = 0;
    vector<vector<int>> ans(n + 1);
    for (int i = 0; i < (int)s.size(); ++i) {
        //cout << now << " ";
        char c = s[i];
        int ch = (int)c - 97;
        if (now == 0 && bor[now].to[ch] == -1) continue;
        now = bor[now].go[ch];
        int now2 = now;
        //cout << now << " ";
        while (now2 != 0) {
            //cout << now2 << " ";
            if ((int)bor[now2].fl.size() != 0) {
                //cout << bor[now2].fl << " ";
                for (int _ = 0; _ < (int)bor[now2].fl.size(); ++_) {
                    ans[bor[now2].fl[_]].push_back(i - allstr[bor[now2].fl[_] - 1] + 1);
                }
            }
            now2 = bor[now2].spl;
        }
        //cout << endl;
    }
    for (int i = 1; i <= n; ++i) {
        cout << (int)ans[i].size() << " ";
        for (int j = 0; j < (int)ans[i].size(); ++j) {
            cout << ans[i][j] + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}
