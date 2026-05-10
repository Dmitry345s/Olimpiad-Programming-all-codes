#include<iostream>
#include<string>
#include<bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    string a;
    cin >> a;
    vector<string> ans;
    //cout << a[n - 1] - '0' << '\n';
    for (int _ = 0; _ < 10; ++_) {
        string x = to_string(_);
        //cout << x << '\n';
        for (int i = 0; i < n - 1; i++) {
            if (_ == 6) {
                //cout << i << ' ' << x[i] << ' ' << a[i] << ' ' << x[i] - '0' << ' ' << a[i] - '0' << '\n';
            }
            if ((x[i] - '0') <= (a[i] - '0')) {
                x += to_string((a[i] - '0') - (x[i] - '0'));
            }
            else{
                x += to_string((a[i] - '0') + 10 - (x[i] - '0'));
            }
        }

        //cout << x << '\n';
        if (((x[0] - '0') + (x[x.size() - 1] - '0')) % 10 == (a[n - 1] - '0')) {
            ans.push_back(x);
        }
    }
    cout << ans.size() << '\n';
    for (auto u : ans) {
        cout << u << '\n';
    }
}
