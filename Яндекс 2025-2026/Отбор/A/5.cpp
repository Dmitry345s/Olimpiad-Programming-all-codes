#include<bits/stdc++.h>

using namespace std;

const int MAX = 2e5;

set<int> all;
pair<int, int> allin[MAX];
int a[2 * MAX + 5];
int ans = 0;

void add(int in) {
    if (all.find(in) != all.end()) return;
    auto it = all.upper_bound(in);
    auto it2 = it;
    --it2;
    int l = *it2, r = *it;
    if (a[r] == a[r - 1] && (r - l) % 2 == 0) {
        ans++;
    }
    //cout << "# " << l << " " << r << " " << in << endl;
    ans -= (r - l) / 2;
    all.insert(in);
    ans += (in - l) / 2;
    ans += (r - in) / 2;
    if (a[r] == a[r - 1] && (r - in) % 2 == 0) {
        ans--;
    }
    if (a[in] == a[in - 1] && (in - l) % 2 == 0) {
        ans--;
    }
    //cout << ans << endl;
}

void del(int in) {
    auto it = all.lower_bound(in);
    if (*it != in) return;
    auto it2 = it, it3 = it;
    it2--; it3++;
    int l = *it2, r = *it3;
    if (a[in] == a[in - 1] && (in - l) % 2 == 0) {
        ans++;
    }
    ans -= (in - l) / 2;
    if (a[r] == a[r - 1] && (r - in) % 2 == 0) {
        ans++;
    }
    ans -= (r - in) / 2;
    all.erase(in);
    if (a[r] == a[r - 1] && (r - l) % 2 == 0) {
        ans--;
    }
    ans += (r - l) / 2;
}

signed main() {
    int n, q;
    cin >> n >> q;
    all.insert(-1);
    all.insert(2 * n);
    for (int i = 0; i < n; ++i) {
        allin[i] = {-1, -1};
    }
    ans = n;
    a[2 * n] = -1;
    for (int i = 0; i < 2 * n; ++i) {
        cin >> a[i];
        --a[i];
        //cout << allin[a[i]].first << " " << allin[a[i]].second << endl;
        if (allin[a[i]].first == -1) {
            allin[a[i]].first = i;
        } else {
            allin[a[i]].second = i;
            add(i);
        }
    }
    cout << ans + n << endl;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l; --r;
        del(allin[a[l]].second);
        del(allin[a[r]].second);
        if (allin[a[l]].second == l) {
            allin[a[l]].second = r;
        } else {
            allin[a[l]].first = r;
        }
        if (allin[a[r]].second == r) {
            allin[a[r]].second = l;
        } else {
            allin[a[r]].first = l;
        }
        if (allin[a[l]].second < allin[a[l]].first) {
            swap(allin[a[l]].second, allin[a[l]].first);
        }
        if (allin[a[r]].second < allin[a[r]].first) {
            swap(allin[a[r]].second, allin[a[r]].first);
        }
        swap(a[l], a[r]);
        add(allin[a[l]].second);
        add(allin[a[r]].second);
        cout << ans + n << endl;
    }
    return 0;
}
