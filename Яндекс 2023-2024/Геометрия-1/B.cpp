#include<bits/stdc++.h>

using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0): x(x), y(y) {}
};

istream& operator >> (istream& in, Point & a) {
    in >> a.x >> a.y;
    return in;
}

struct Vector {
    int x, y;
    Vector(int x = 0, int y = 0): x(x), y(y) {}
    Vector(Point a) {
        x = a.x;
        y = a.y;
    }
    Vector(Point a, Point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
};

Vector operator + (Vector a, Vector b) {
    Vector c = Vector(a.x + b.x, a.y + b.y);
    return c;
}

int operator ^ (Vector a, Vector b) { //скалярное произведение
    return a.x * b.x + a.y * b.y;
}

int operator * (Vector a, Vector b) { //векторное произведение
    return a.x * b.y - a.y * b.x;
}

ostream& operator << (ostream& out, Vector a) {
    out << a.x << " " << a.y;
    return out;
}

double get_angle(Vector a, Vector b) {
    return atan2((a * b), (a ^ b));
}

double reget_angle(double a) {
    return 2 * M_PI * (a < 0) + a;
}

int get(Vector v) {
    return v.x * v.x + v.y * v.y;
}

signed main() {
    Point a1, a2, b1, b2;
    cin >> a1 >> a2 >> b1 >> b2;
    Vector v1 = Vector(a1, a2), v2 = Vector(b1, b2);
    cout.precision(15);
    cout << sqrt(get(v1)) << " " << sqrt(get(v2)) << endl;
    cout << (v1 + v2) << endl;
    cout << (v1 ^ v2) << " " << (v1 * v2) << endl;
    cout << (double)abs(v1 * v2) / 2 << endl;
    Vector tox = Vector(1, 0);
    cout << reget_angle(get_angle(tox, v1)) << " " << reget_angle(get_angle(tox, v2)) << endl;
    double ch = reget_angle(get_angle(v1, v2));
    cout << ch << endl;
    cout << ch / (2 * M_PI) << endl;
    return 0;
}
