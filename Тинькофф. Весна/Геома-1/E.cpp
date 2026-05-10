#include<iostream>
#include<cmath>
#include<iomanip>

using namespace std;

int main() {
    double x, y, a, b, c;
    cin >> x >> y >> a >> b >> c;
    if (b == 0) {
        cout << abs((-c / a) - x);
        return 0;
    }
    if (a == 0) {
        cout << abs((-c / b) - y);
        return 0;
    }
    a /= -b;
    c /= -b;
    double a2 = -1 * (1 / a), c2, y2 = (a2 * x + c);
    if (y >= y2) {
        c2 = c + abs(y - y2);
    } else {
        c2 = c - abs(y - y2);
    }
    double x1 = (c2 - c) / (a - a2), y1 = a * x1 + c;
    cout << setprecision(8) << sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1)) << endl;
    return 0;
}
