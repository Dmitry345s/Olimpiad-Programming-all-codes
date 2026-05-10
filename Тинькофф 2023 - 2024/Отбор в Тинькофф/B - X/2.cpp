#include<bits/stdc++.h>
#define int long long

using namespace std;

int getnext(vector<pair<int, int>> & gt, vector<int> & mnext, int v) {
    if (v == gt.size() || gt[v].first > 0) {
        return v;
    }
    return mnext[v] = getnext(gt, mnext, mnext[v]);
}

signed main() {
    int n;
    cin >> n;
    vector<pair<int, int>> ch(n);
    for (int i = 0; i < n; ++i) {
        cin >> ch[i].first >> ch[i].second;
    }
    sort(ch.begin(), ch.end());
    vector<pair<int, int>> gt;
    int cnt = 1;
    for (int i = 1; i < n; ++i) {
        if (ch[i].second == ch[i - 1].second) {
            cnt++;
        } else {
            gt.push_back({cnt, ch[i - 1].second});
            cnt = 1;
        }
    }
    gt.push_back({cnt, ch.back().second});
    /*int n;
    cin >> n;
    vector<pair<int, int>> gt;
    for (int i = 0; i < n; ++i) {
        int cnt, cl;
        cin >> cnt >> cl;
        gt.push_back({cnt, cl});
    }*/
    vector<int> mnext(gt.size());
    for (int i = 0; i < gt.size(); ++i) {
        mnext[i] = i + 1;
    }
    int ans = 0;
    while (true) {
        int st = 0;
        if (gt[0].first <= 0) {
            st = getnext(gt, mnext, 0);
        }
        if (st == gt.size()) {
            cout << "Draw" << " ";
            break;
        }
        int pr = st;
        st = getnext(gt, mnext, mnext[st]);
        if (st == gt.size()) {
            if (gt[pr].second) {
                cout << "Black" << " ";
            } else {
                cout << "White" << " ";
            }
            break;
        }
        int t = 0;
        while (st != gt.size()) {
            if (gt[pr].second != gt[st].second) {
                gt[pr].first -= 1;
                gt[st].first -= 1;
                t = 1;
            }
            pr = st;
            st = getnext(gt, mnext, mnext[st]);
        }
        if (!t) {
            if (gt[pr].second) {
                cout << "Black" << " ";
            } else {
                cout << "White" << " ";
            }
            break;
        }
        ans++;
    }
    cout << ans << endl;
}
