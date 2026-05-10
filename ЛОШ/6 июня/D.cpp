#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

double EPS = 1e-3;

bool equals (double a, double b) {
    return ((a <= b && a + EPS >= b) || (a >= b && a - EPS <= b));
}

struct vct{
    long long x, y;
};

long long operator *(vct a, vct b) {
    return a.x * b.y - a.y * b.x;
}

bool check(vector<pair<long long, long long>> t, vector<pair<long long, long long>> t2, double s) {
    bool flag = false;
    for (int i = 0; i < int(t2.size()); ++i) {
        long long x = t2[i].first, y = t2[i].second;
        double s2 = 0;
        int n = t.size();
        for (int j = 0; j < n - 1; ++j) {
            vct a = {t[j].first - x, t[j].second - y}, b = {t[j + 1].first - x, t[j + 1].second - y};
            s2 += abs(double(a * b) / 2);
        }
        vct a = {t[n - 1].first - x, t[n - 1].second - y}, b = {t[0].first - x, t[0].second - y};
        s2 += abs(double(a * b) / 2);
        if (equals(s, s2)) {
            flag = true;
        }
    }
    return flag;
}

int main() {
    int k ;
    cin >> k;
    while (k--) {
        int n1;
        cin >> n1;
        vector<pair<long long, long long>> t(n1);
        cin >> t[0].first >> t[0].second;
        double s1 = 0;
        for (int i = 1; i < n1; ++i) {
            cin >> t[i].first >> t[i].second;
            s1 += (double(t[i].second + t[i - 1].second) / 2) * (t[i].first - t[i - 1].first);
        }
        s1 += (double(t[0].second + t[n1 - 1].second) / 2) * (t[0].first - t[n1 - 1].first);
        int n2;
        cin >> n2;
        vector<pair<long long, long long>> t2(n2);
        cin >> t2[0].first >> t2[0].second;
        double s2 = 0;
        for (int i = 1; i < n2; ++i) {
            cin >> t2[i].first >> t2[i].second;
            s2 += (double(t2[i].second + t2[i - 1].second) / 2) * (t2[i].first - t2[i - 1].first);
        }
        s2 += (double(t2[0].second + t2[n2 - 1].second) / 2) * (t2[0].first - t2[n2 - 1].first);
        s1 = abs(s1);
        s2 = abs(s2);
        if (check(t, t2, s1) || check(t2, t, s2)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
