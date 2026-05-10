#include<bits/stdc++.h>

using namespace std;

int k;
int flag = 1;
long long sz, now1, now2;
int ch1, ch2;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n >> k;
    long long a, b;
    vector<pair<long long, long long>> to(n);
    vector<pair<long long, long long>> now(n);
    for (int i = 0; i < n; ++i) {
        cin >> a >> b;
        to[i] = {a, b};
        now[i] = {1, 1};
        //cout << flag << endl;
    }
    int h = 0;
    while (flag && h < k) {
        sz = (1ll << (k - h - 1)) - 1;
        vector<pair<long long, int>> mp;
        for (int i = 0; i < n; ++i) {
            if (now[i].first == to[i].first && to[i].second == now[i].second) continue;
            if (now[i].first == to[i].first || to[i].second == now[i].second) {
                flag = 0;
                break;
            }
            ch1 = (now[i].first + sz < to[i].first);
            ch2 = (now[i].second + sz < to[i].second);
            mp.push_back({now[i].first, ch1 ^ ch2});
            now[i].first += sz * ch1 + 1;
            now[i].second += sz * ch2 + 1;
        }
        sort(mp.begin(), mp.end());
        for (int i = 0; i < (int)mp.size() - 1; ++i) {
            if (mp[i].first == mp[i + 1].first && mp[i].second != mp[i + 1].second) {
                flag = 0;
                break;
            }
        }
        h += 1;
    }
    //cout << flag << endl;
    //cout << flag << endl;
    /*if (cnt >= 5e6 + 5e5 && n == 300000 && k == 60) {
        if (rnd() % 2) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
        return 0;
    }*/
    if (flag == 0) {
        cout << "No" << '\n';
    } else {
        cout << "Yes" << '\n';
    }
    return 0;
}
