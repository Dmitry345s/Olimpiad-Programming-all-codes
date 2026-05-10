#include<bits/stdc++.h>

using namespace std;

int tp = 0;

vector <int> a;
vector <int> p;

int cnt1 = 0;
int n;

int ask(int in) {
    p[a[cnt1 % n]] = 1 - p[a[cnt1 % n]];
    cnt1++;
    assert(cnt1 <= 50 * n);
    cout << "? " << in << endl;
    int y;
    cin >> y;
    //y = p[in];
    //cout << y << endl;
    if (y == tp) {
        return 0;
    }
    return 1;
}

signed main() {
    cin >> n;
    a.resize(n);
    p.resize(n, 0);
    /*for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }*/
    vector<pair<int, int>> now(n, {0, n});
    for (int i = 0; i < n; ++i) {
        if (ask(i)) {
            now[i].second = i + 1;
        } else {
            now[i].first = i + 1;
        }
    }
    tp ^= 1;
    int cnt = 1;
    while (true) {
        assert(cnt < 50);
        for (int i = 0; i < n; ++i) {
            int now_b = n;
            int in = i;
            for (int u = 0; u < n; ++u) {
                if (now[u].second <= i + 1 || i + 1 < now[u].first || now[u].first + 1 >= now[u].second) continue;
                if (abs((now[u].first + now[u].second) / 2 - i - 1) <= now_b) {
                    in = u;
                    now_b = abs((now[u].first + now[u].second) / 2 - i - 1);
                }
            }
            if (ask(in)) {
                if (i + 1 < now[in].second) now[in].second = i + 1;
            } else {
                if (now[in].first < i + 1) now[in].first = i + 1;
            }
        }
        tp ^= 1;
        int fl = 1;
        for (int i = 0; i < n; ++i) {
            if (now[i].first + 1 < now[i].second) {
                fl = 0;
            }
        }
        cnt++;
        if (fl) break;
    }
    cout << "! ";
    for (int i = 0; i < n; ++i) {
        cout << now[i].first << " ";
    }
    cout << endl;
    //cout << cnt1 << endl;
    return 0;
}
