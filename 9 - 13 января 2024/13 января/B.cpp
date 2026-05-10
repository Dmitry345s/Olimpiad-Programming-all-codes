#include<bits/stdc++.h>

using namespace std;

int MAX = 1e7 + 1;
vector<int> mpr(MAX);
int mcnt = 0;

void start() {
    for (int i = 2; i < MAX; ++i) {
        if (mpr[i] == 0) {
            mcnt += 1;
            for (int j = i; j < MAX; j += i) {
                mpr[j] = i;
            }
        }
    }
}

map<int, array<int, 25>> mp;

void get(int a) {
    while (a != 1) {
        int ch = mpr[a], cnt = 0;
        while (a % ch == 0) {
            cnt++;
            a /= ch;
        }
        mp[ch][cnt] += 1;
    }
}

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    start();
    cout << mcnt << endl;
    //cout << 1 << endl;
    for (int i = 0; i < n; ++i) {
        get(a[i]);
    }
    //cout << 1 << endl;
    int ans = 0;
    for (auto [key, val] : mp) {
        //cout << key << endl;
        int sum = 0;
        for (int i = 0; i < 25; ++i) {
            sum += val[i];
        }
        val[0] = n - sum;
        int cnt = 1e9;
        for (int i = 0; i < 25; ++i) {
            int ch = 0;
            for (int j = 0; j < 25; ++j) {
                ch += abs(j - i) * val[j];
            }
            //cout << "! " << i << " " << ch << endl;
            cnt = min(ch, cnt);
        }
        ans += cnt;
        //cout << key << " " << cnt << endl;
    }
    cout << ans << endl;
    return 0;
}
