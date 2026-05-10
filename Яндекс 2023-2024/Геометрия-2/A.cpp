#include<bits/stdc++.h>
#pragma GCC optimize("O3")

# define int long long

using namespace std;

struct Point {
    int x, y;
    Point(int x = 1e5, int y = 1e5) : x(x), y(y) {}
};

bool operator == (Point a, Point b) {
    return (a.x == b.x && a.y == b.y);
}

istream& operator >> (istream & in, Point & a) {
    in >> a.x >> a.y;
    return in;
}

struct Vector {
    int x, y;
    Vector(int x = 0, int y = 0) : x(x), y(y) {}
    Vector(Point a, Point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
};

int operator ^ (Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

int operator * (Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

int get2(Vector a) {
    return a.x * a.x + a.y * a.y;
}

Point mn;

bool cmp(pair<Point, int> a, pair<Point, int> b) {
    Vector v1 = Vector(mn, a.first), v2 = Vector(mn, b.first);
    if (v1 * v2 == 0) {
        return get2(v1) < get2(v2);
    }
    return v1 * v2 < 0;
}

vector<int> hull(vector<pair<Point, int>> a) {
    if (a.size() <= 2) {
        vector<int> ans;
        for (int i = 0; i < (int)a.size(); ++i) {
            ans.push_back(a[i].second);
        }
        return ans;
    }
    mn = Point();
    int in = -1;
    for (int i = 0; i < (int)a.size(); ++i) {
        if (a[i].first.y < mn.y || (a[i].first.y == mn.y && a[i].first.x < mn.x)) {
            mn = a[i].first;
            in = i;
        }
    }
    vector<int> ans;
    vector<Point> to_ans;
    ans.push_back(a[in].second);
    to_ans.push_back(mn);
    Point last = mn;
    while (true) {
        Point minm = last;
        in = -1;
        for (int i = 0; i < (int)a.size(); ++i) {
            if (a[i].first == last) continue;
            if (minm == last) {
                minm = a[i].first;
                in = a[i].second;
            } else {
                Vector v1 = Vector(last, a[i].first), v2 = Vector(last, minm);
                if (v1 * v2 < 0 || (v1 * v2 == 0 && get2(v1) > get2(v2))) {
                    minm = a[i].first;
                    in = a[i].second;
                }
            }
        }
        if (minm == mn) break;
        ans.push_back(in);
        to_ans.push_back(minm);
        last = minm;
    }
    for (int i = 0; i < (int)to_ans.size(); ++i) {
        Point v = to_ans[i], v2 = to_ans[(i + 1) % (int)ans.size()];
        for (int i = 0; i < (int)a.size(); ++i) {
            if (a[i].first == v || a[i].first == v2) continue;
            Vector v3 = Vector(v, a[i].first), v4 = Vector(v2, a[i].first);
            if (v3 * v4 == 0 && (v3 ^ v4) < 0) {
                ans.push_back(a[i].second);
            }
        }
    }
    return ans;
    a.erase(a.begin() + in);
    sort(a.begin(), a.end(), cmp);
    vector<Point> st;
    st.push_back(mn);
    st.push_back(a[0].first);
    ans.push_back(a[0].second);
    for (int i = 1; i < (int)a.size(); ++i) {
        //cout << i << " " << a[i].first.x << " " << a[i].first.y << endl;
        while ((int)st.size() > 2 && Vector(st.back(), a[i].first) * Vector(st[(int)st.size() - 2], st.back()) < 0) {
            st.pop_back();
            ans.pop_back();
        }
        st.push_back(a[i].first);
        ans.push_back(a[i].second);
    }
    return ans;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<pair<Point, int>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first;
        a[i].second = i;
    }
    vector<int> ch(n, -1);
    for (int i = 0; i < (int)a.size(); ++i) {
        for (int j = i + 1; j < (int)a.size(); ++j) {
            if (a[i].first == a[j].first) {
                ch[a[j].second] = a[i].second;
                a.erase(a.begin() + j);
                j--;
            }
        }
    }
    vector<int> ans(n, 0);
    int cnt = 0;
    while (a.size() > 0) {
        cnt++;
        vector<int> now = hull(a);
        for (int i = 0; i < (int)now.size(); ++i) {
            ans[now[i]] = cnt;
        }
        vector<pair<Point, int>> a2;
        for (int i = 0; i < (int)a.size(); ++i) {
            int j = a[i].second;
            if (!ans[j]) {
                a2.push_back(a[i]);
            }
        }
        a = a2;
    }
    for (int i = 0; i < n; ++i) {
        if (ans[i] == 0) {
            ans[i] = ans[ch[i]];
        }
        cout << ans[i] << " ";
    }
    return 0;
}
