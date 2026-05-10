#include<iostream>
#include<vector>
#include<set>
#include<map>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(2 * n);
    set<pair<int, int>> s;
    map<int, int> h;
    for (int i = 0; i < 2 * n; ++i) {
        cin >> a[i];
        s.insert({a[i], i});
    }
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        h[l - 1] = r - 1;
        h[r - 1] = l - 1;
    }
    int t;
    cin >> t;
    set<pair<int, int>> :: iterator it = s.end();
    int j;
    if (t == 1) {
        int last = -1;
        for (int i = 0; i < n; ++i) {
            if (h.find(last) == h.end() || s.find({a[h[last]], h[last]}) == s.end()) {
                it = s.end();
                --it;
                j = it->second;
                cout << j + 1 << endl;
                s.erase(it);
            } else {
                cout << h[last] + 1 << endl;
                s.erase({a[h[last]], h[last]});
            }
            cin >> last;
            --last;
            if (last == -2) {
                cout << -1 << endl;
                return 0;
            }
            s.erase({a[last], last});
        }
    } else {
        int last = -1;
        for (int i = 0; i < n; ++i) {
            cin >> last;
            --last;
            if (last == -2) {
                cout << -1 << endl;
                return 0;
            }
            s.erase({a[last], last});
            if (h.find(last) == h.end() || s.find({a[h[last]], h[last]}) == s.end()) {
                it = s.end();
                --it;
                j = it->second;
                cout << j + 1 << endl;
                s.erase(it);
            } else {
                cout << h[last] + 1 << endl;
                s.erase({a[h[last]], h[last]});
            }
        }
    }
    return 0;
}
