#include<iostream>
#include<vector>

using namespace std;

vector<int> b(5e6 + 5, 1);

void sieve() {
    b[0] = 0;
    b[1] = 1;
    for (int i = 2; i < 5e6 + 5; ++i) {
        if (b[i]) {
            for (int j = 2 * i; j < 5e6 + 5; j += i) {
                b[j] = 0;
            }
        }
    }
}

vector<int> ans(5e6 + 5);

void get_ans() {
    vector<int> st(4);
    st[1] = 1;
    st[2] = 2;
    st[3] = 3;
    ans[1] = 1;
    ans[2] = 1;
    ans[3] = 1;
    for (int i = 4; i < 5e6 + 5; ++i) {
        if (b[i]) {
            st[i % 4] = i;
        }
        if (i % 4 == 0) {
            ans[i] = max(max(ans[i - 1], ans[i - 2]), ans[i - 3]) + 1;
        } else {
            ans[i] = ans[i - st[i % 4]] + 1;
        }
    }
}

int main() {
    sieve();
    get_ans();
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n == 1) {
            int x;
            cin >> x;
            if (x % 4 == 0) {
                cout << "Farmer Nhoj" << endl;
            } else {
                cout << "Farmer John" << endl;
            }
        } else {
            vector<int> a(n);
            int f = 1e9, f2 = 1e9, s = 1e9, s2 = 1e9;
            for (int i = 0; i < n; ++i) {
                cin >> a[i];
                if (a[i] % 4 == 0) {
                    int mays = (ans[a[i]] + 1) / 2;
                    if (mays < s) {
                        s = mays;
                        s2 = i;
                    }
                } else {
                    int mayf = ans[a[i]] / 2;
                    if (mayf < f) {
                        f = mayf;
                        f2 = i;
                    }
                }
            }
            if (f > s) {
                cout << "Farmer Nhoj" << endl;
            } else if (f < s) {
                cout << "Farmer John" << endl;
            } else {
                if (f2 < s2) {
                    cout << "Farmer John" << endl;
                } else {
                    cout << "Farmer Nhoj" << endl;
                }
            }
        }
    }
    return 0;
}
