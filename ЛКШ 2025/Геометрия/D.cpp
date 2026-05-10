#include<bits/stdc++.h>

//#define int long long

using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

bool operator == (Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

struct Vector {
    int x, y;
    Vector(int x = 0, int y = 0) : x(x), y(y) {}
    Vector(Point a, Point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
};

int operator * (Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

int operator % (Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

int ch(pair<Point, Point> a, pair<Point, Point> b) {
    int u1 = min(max(a.first.y, a.second.y), max(b.first.y, b.second.y));
    int u2 = max(min(a.first.y, a.second.y), min(b.first.y, b.second.y));
    if (u1 < u2) return 0;
    int u3 = min(max(a.first.x, a.second.x), max(b.first.x, b.second.x));
    int u4 = max(min(a.first.x, a.second.x), min(b.first.x, b.second.x));
    if (u3 < u4) return 0;
    Vector v1 = Vector(a.first, a.second), v2 = Vector(a.first, b.first), v3 = Vector(a.first, b.second);
    Vector v4 = Vector(b.first, b.second), v5 = Vector(b.first, a.first), v6 = Vector(b.first, a.second);
    if (1ll * (v1 * v2) * (v3 * v2) >= 0 && 1ll * (v4 * v5) * (v6 * v5) >= 0 && 1ll * (v1 * v3) * (v2 * v3) >= 0 && 1ll * (v4 * v6) * (v5 * v6) >= 0) return 1;
    return 0;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<pair<Point, Point>> all(n);
    vector<array<int, 3>> to_sort;
    vector<pair<int, int>> b;
    vector<int> do_an(n);
    vector<int> rev_an(n);
    for (int i = 0; i < n; ++i) {
        cin >> all[i].first.x >> all[i].first.y >> all[i].second.x >> all[i].second.y;
        to_sort.push_back({all[i].first.x, -1, i});
        to_sort.push_back({all[i].second.x, 1, i});
        b.push_back({all[i].first.y, i});
    }
    sort(b.begin(), b.end());
    for (int i = 0; i < n; ++i) {
        do_an[b[i].second] = i;
        rev_an[i] = b[i].second;
    }
    sort(to_sort.begin(), to_sort.end());
    set<int> st;
    for (auto [x, t, in] : to_sort) {
        if (t == -1) {
            st.insert(do_an[in]);
            auto it = st.lower_bound(do_an[in]);
            auto it2 = it;
            if (it2 != st.begin()) {
                --it2;
            } else {
                it2 = st.end();
            }
            ++it;
            if (it != st.end() && ch(all[in], all[rev_an[(*it)]])) {
                cout << "YES" << endl;
                cout << in + 1 << " " << rev_an[(*it)] + 1 << endl;
                return 0;
            }
            if (it2 != st.end() && ch(all[in], all[rev_an[(*it2)]])) {
                cout << "YES" << endl;
                cout << in + 1 << " " << rev_an[(*it2)] + 1 << endl;
                return 0;
            }
        } else {
            auto it = st.lower_bound(do_an[in]);
            auto it2 = it, it3 = it;
            it2++;
            if (it3 != st.begin()) {
                --it3;
            } else {
                it3 = st.end();
            }
            if (it2 != st.end() && it3 != st.end() && ch(all[rev_an[(*it3)]], all[rev_an[(*it2)]])) {
                cout << "YES" << endl;
                cout << rev_an[(*it3)] + 1 << " " << rev_an[(*it2)] + 1 << endl;
                return 0;
            }
            st.erase(it);
        }
    }
    cout << "NO" << endl;
    return 0;
}
