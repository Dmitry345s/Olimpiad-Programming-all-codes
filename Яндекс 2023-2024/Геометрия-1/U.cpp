#include<bits/stdc++.h>

using namespace std;

struct Vector {
    int x, y;
    Vector(int x = 0, int y = 0): x(x), y(y) {}
};

istream& operator >> (istream& in, Vector & a) {
    cin >> a.x >> a.y;
    return in;
}

int operator ^ (Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

int operator * (Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

double get(Vector a, Vector b) {
    return atan2(a * b, a ^ b);
}

double reget(double a) {
    return 2 * M_PI * (a < 0) + a;
}

signed main() {
    Vector v1, tox = Vector(1, 0);
    cin >> v1;
    cout << setprecision(10) << reget(get(tox, v1)) << endl;
    return 0;
}
