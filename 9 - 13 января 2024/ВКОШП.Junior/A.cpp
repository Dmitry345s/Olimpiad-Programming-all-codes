#include<iostream>
#include<string>
#include<bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    string a;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < 10; ++i) {
        string x = to_string(i);
        for (int j = 1; j < n; ++j) {
            x += to_string((10 + a[j - 1] - (x.back() - '0')) % 10 + 2);
        }
        cout << stoi(x) << endl;
        if ((i + (x.back() - '0')) % 10 == (a[i] - '0') + 2) {
            cout << stoi(x);
        }
    }
    return 0;
}
