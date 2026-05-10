#include<bits/stdc++.h>

using namespace std;

signed main() {
    int g;
    cin >> g;
    if (g <= 4) {
        if (g == 4) {
            cout << "Ivan Urgant" << endl << "Mix" << endl;
            return 0;
        }
        if (g == 1) {
            cout << "Ivan Urgant" << endl << "Draw" << endl;
            return 0;
        }
        if (g == 3) {
            cout << "Ivan Urgant" << endl << "Draw" << endl;
            return 0;
        }
        if (g == 2) {
            cout << "Ivan Safonov" << endl;
            return 0;
        }
    }
    if (g % 2 == 0) {
        cout << "Ivan Urgant" << endl << "Draw" << endl;
        return 0;
    }
    cout << "Ivan Safonov" << endl;
    return 0;
}
