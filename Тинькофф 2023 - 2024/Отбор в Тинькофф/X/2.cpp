#include<bits/stdc++.h>
#define int long long

using namespace std;

int getcnt(int a) {
    int cnt = 0;
    for (int i = 0; i < 20; ++i) {
        cnt += ((a >> i) & 1);
    }
    return cnt;
}
signed main() {
    int now = 0;
    vector<int> get = {0};
    vector<int> ch = {0};
    int mcnt = 0;
    int ans = 0;
    for (int i = 1; i < (1 << 20) + 160; ++i) {
        now = (487237 * now + 1011807) % (1 << 20);
        get.push_back(now);
        ch.push_back(getcnt(now) % 2);
        if (ch.back() == 0) {
            mcnt ++;
        } else {
            ans = max(ans, mcnt);
            mcnt = 0;
        }
    }
    int n;
    cin >> n;
    vector<int> p, p2;
    for (int i = 0; i < 160 - 18; ++i) {
        cout << 1 << endl;
        int nn;
        cin >> nn;
        if (nn < n) {
            p.push_back(0);
            p2.push_back(0);
        } else {
            p.push_back(1);
            p2.push_back(1);
        }
        n = nn;
        if (n == -1) {
            return 0;
        }
    }
    p.push_back(3);
    for (int i = 0; i < ch.size(); ++i) {
        p.push_back(ch[i]);
    }
    int st = -1;
    int cnt = 0;
    vector<int> z(p.size());
    z[0] = p.size();
    int l = 0, r = 1;
    for (int i = 1; i < p.size(); ++i) {
        z[i] = min(z[i - l], max((long long) 0, r - i));
        while (i + z[i] < p.size() && p[z[i]] == p[i + z[i]]) {
            z[i]++;
        }
        if (z[i] + i > r) {
            r = z[i] + i;
            l = i;
        }
        if (z[i] == 160 - 18) {
            st = i - 1;
            cnt++;
        }
    }
    if (cnt > 1) {
        cout << 1 << endl;
        int nn;
        cin >> nn;
        if (nn < n) {
            p.push_back(0);
            p2.push_back(0);
        } else {
            p.push_back(1);
            p2.push_back(1);
        }
        n = nn;
        if (n == -1) {
            return 0;
        }
        p2.push_back(3);
        for (int i = 0; i < ch.size(); ++i) {
            p2.push_back(ch[i]);
        }
        vector<int> z2(p2.size());
        z2[0] = p2.size();
        int l = 0, r = 1;
        for (int i = 1; i < p2.size(); ++i) {
            z2[i] = min(z2[i - l], max((long long) 0, r - i));
            while (i + z2[i] < p2.size() && p2[z2[i]] == p2[i + z2[i]]) {
                z2[i]++;
            }
            if (z2[i] + i > r) {
                r = z[i] + i;
                l = i;
            }
            if (z2[i] == 160 - 17) {
                st = i - 1;
                cnt++;
            }
        }
    }
    st %= (1 << 20);
    while (n != -1) {
        if (ch[st] == 0) {
            cout << 1 << endl;
            cin >> n;
        } else {
            cout << n << endl;
            cin >> n;
        }
        st++;
        st %= (1 << 20);
    }
    return 0;
}

