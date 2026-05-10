#include<iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int x = 128;
    for (int i = 0; i < 8; ++i) {
        if (n >= x) {
            cout << 1;
            n -= x;
        } else {
            cout << 0;
        }
        x /= 2;
    }
    return 0;
}
