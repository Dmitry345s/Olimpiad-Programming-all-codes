#include<bits/stdc++.h>

using namespace std;

const int A = 2, LEN = 30;

struct Node {
    int cnt;
    int go[A];
    Node() {
        cnt = 0;
        for (int i = 0; i < A; ++i) {
            go[i] = -1;
        }
    }
};

vector<Node> bor(1);

void add(int n) {
    int v = 0;
    bor[v].cnt++;
    for (int i = LEN; i >= 0; --i) {
        int ch = (n >> i) & 1;
        if (bor[v].go[ch] == -1) {
            bor.push_back(Node());
            bor[v].go[ch] = (int)bor.size() - 1;
        }
        v = bor[v].go[ch];
        bor[v].cnt++;
    }
}

void del(int n) {
    int v = 0;
    bor[v].cnt--;
    for (int i = LEN; i >= 0; --i) {
        int ch = (n >> i) & 1;
        if (bor[v].go[ch] == -1) {
            bor.push_back(Node());
            bor[v].go[ch] = (int)bor.size() - 1;
        }
        v = bor[v].go[ch];
        bor[v].cnt--;
    }
}

int ans(int n) {
    int v = 0;
    int ans = 0;
    for (int i = LEN; i >= 0; --i) {
        int ch = (n >> i) & 1;
        if (bor[v].go[ch ^ 1] != -1 && bor[bor[v].go[ch ^ 1]].cnt > 0) {
            ans += (1 << i);
            v = bor[v].go[ch ^ 1];
        } else {
            v = bor[v].go[ch];
        }
    }
    return ans;
}

signed main() {
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        char t;
        cin >> t;
        if (t == '+') {
            int num;
            cin >> num;
            add(num);
        } else if (t == '-') {
            int num;
            cin >> num;
            del(num);
        } else {
            int num;
            cin >> num;
            if (bor[0].cnt == 0) {
                cout << num << endl;
                continue;
            }
            cout << max(ans(num), num) << endl;
        }
    }
    return 0;
}
