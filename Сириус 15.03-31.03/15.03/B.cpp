#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n;
    cin >> n;
    /*int st = 1;
    int cnt = 0;
    while (st < n) {
        cnt++;
        //cout << st << " ";
        if (st % 100000 == 2) {
            cout << cnt << endl;
        }
        int x = st;
        int maxm = 0;
        while (x != 0) {
            maxm = max(x % 10, maxm);
            x /= 10;
        }
        st += maxm;
    }*/
    vector<vector<int>> prec1(10, vector<int> (10));
    vector<vector<int>> cnt1(10, vector<int> (10));
    //cout << time(0) << endl;
    int k2 = 1e5;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (i == 0 && j == 0) continue;
            int st = j;
            int cnt = 0;
            while (st < k2) {
                cnt++;
                int x = st;
                int maxm = i;
                while (x != 0) {
                    maxm = max(x % 10, maxm);
                    x /= 10;
                }
                st += maxm;
            }
            //cout << i << " " << j << " " << cnt << endl;
            prec1[i][j] = st % k2;
            cnt1[i][j] = cnt;
        }
    }
    int k = 1e10;
    vector<vector<int>> prec2(10, vector<int> (10));
    vector<vector<int>> cnt2(10, vector<int> (10));
    //cout << time(0) << endl;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (i == 0 && j == 0) continue;
            int st = j;
            int cnt = 0;
            while (st < k) {
                int x = st / k2;
                int y = x;
                int maxm = i;
                while (x != 0) {
                    maxm = max(x % 10, maxm);
                    x /= 10;
                }
                int ch = prec1[maxm][st % k2];
                cnt += cnt1[maxm][st % k2];
                st = (y + 1) * k2 + ch;
            }
            //cout << i << " " << j << " " << cnt << endl;
            prec2[i][j] = st % k;
            cnt2[i][j] = cnt;
        }
    }
    int k3 = 1e15;
    vector<vector<int>> prec3(10, vector<int> (10));
    vector<vector<int>> cnt3(10, vector<int> (10));
    //cout << time(0) << endl;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (i == 0 && j == 0) continue;
            int st = j;
            int cnt = 0;
            while (st < k3) {
                int x = st / k;
                int y = x;
                int maxm = i;
                while (x != 0) {
                    maxm = max(x % 10, maxm);
                    x /= 10;
                }
                int ch = prec2[maxm][st % k];
                cnt += cnt2[maxm][st % k];
                st = (y + 1) * k + ch;
            }
            //cout << i << " " << j << " " << cnt << endl;
            prec3[i][j] = st % k3;
            cnt3[i][j] = cnt;
        }
    }
    //cout << time(0) << endl;
    int st = 1;
    int cnt = 0;
    while (st < n) {
        //cout << st << endl;
        if (n - st > k3) {
            int x = st / k3;
            int y = x;
            int maxm = 0;
            while (x != 0) {
                maxm = max(x % 10, maxm);
                x /= 10;
            }
            int ch = prec3[maxm][st % k3];
            cnt += cnt3[maxm][st % k3];
            st = (y + 1) * k3 + ch;
        }else if (n - st > k) {
            int x = st / k;
            int y = x;
            int maxm = 0;
            while (x != 0) {
                maxm = max(x % 10, maxm);
                x /= 10;
            }
            int ch = prec2[maxm][st % k];
            cnt += cnt2[maxm][st % k];
            st = (y + 1) * k + ch;
        } else if (n - st > k2) {
            //cout << st << " " << cnt << endl;
            int x = st / k2;
            int y = x;
            int maxm = 0;
            while (x != 0) {
                maxm = max(x % 10, maxm);
                x /= 10;
            }
            int ch = prec1[maxm][st % k2];
            cnt += cnt1[maxm][st % k2];
            st = (y + 1) * k2 + ch;
        } else {
            int x = st;
            int maxm = 0;
            while (x != 0) {
                maxm = max(x % 10, maxm);
                x /= 10;
            }
            st += maxm;
            cnt++;
        }
    }
    //cout << time(0) << endl;*/
    if (st == n) {
        cout << cnt + 1 << endl;
    } else {
        cout << -1 << endl;
    }
    return 0;
}
