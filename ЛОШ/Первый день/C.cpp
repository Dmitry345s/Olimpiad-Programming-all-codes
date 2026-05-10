#include<iostream>
using namespace std;

int main() {
    long long n, a, b, c;
    cin >> n >> a >> b >> c;
    long long l = 0, r = 1e9;
    while (l + 1 < r) {
        long long m = (l + r) / 2;
        if (m * (a + b + c) <= n) {
            l = m;
        } else {
            r = m;
        }
    }
    long long t = l, p;
    long long maxm = max(a, max(b, c));
    if (a == maxm) {
        cout << t * a << " ";
        l = t, r = 1e9;
        while (l + 1 < r) {
            long long m = (l + r) / 2;
            if (t * a + m * (b + c) <= n) {
                l = m;
            } else {
                r = m;
            }
        }
        p = l;
        if (b == min(b, c)) {
            l = p, r = 1e9;
            while (l + 1 < r) {
            long long m = (l + r) / 2;
                if (t * a + p * c + m * b <= n) {
                    l = m;
                } else {
                    r = m;
                }
            }
            cout << l * b << " " << p * c;
        } else {
            l = p, r = 1e9;
            while (l + 1 < r) {
            long long m = (l + r) / 2;
                if (t * a + p * b + m * c <= n) {
                    l = m;
                } else {
                    r = m;
                }
            }
            cout << p * b << " " << l * c;
        }
    } else if (b == maxm) {
        l = t, r = 1e9;
        while (l + 1 < r) {
            long long m = (l + r) / 2;
            if (t * b + m * (a + c) <= n) {
                l = m;
            } else {
                r = m;
            }
        }
        p = l;
        if (a == min(a, c)) {
            l = p, r = 1e9;
            while (l + 1 < r) {
            long long m = (l + r) / 2;
                if (t * b + p * c + m * a <= n) {
                    l = m;
                } else {
                    r = m;
                }
            }
            cout << a * l << " " << b * t << " " << c * p;
        } else {
            l = p, r = 1e9;
            while (l + 1 < r) {
            long long m = (l + r) / 2;
                if (t * b + p * a + m * c <= n) {
                    l = m;
                } else {
                    r = m;
                }
            }
            cout << a * p << " " << b * t << " " << c * l;
        }
    } else {
        l = t, r = 1e9;
        while (l + 1 < r) {
            long long m = (l + r) / 2;
            if (t * c + m * (a + b) <= n) {
                l = m;
            } else {
                r = m;
            }
        }
        p = l;
        if (a == min(a, b)) {
            l = p, r = 1e9;
            while (l + 1 < r) {
            long long m = (l + r) / 2;
                if (t * c + p * b + m * a <= n) {
                    l = m;
                } else {
                    r = m;
                }
            }
            cout << a * l << " " << b * p << " " << c * t;
        } else {
            l = p, r = 1e9;
            while (l + 1 < r) {
            long long m = (l + r) / 2;
                if (t * c + p * a + m * b <= n) {
                    l = m;
                } else {
                    r = m;
                }
            }
            cout << a * p << " " << b * l << " " << c * t;
        }
    }
    return 0;
}
