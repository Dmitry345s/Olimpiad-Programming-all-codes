#include<iostream>
#include<cmath>
#include<iomanip>

using namespace std;

bool equals(double a, double b) {
    return (a <= b && a + 1e-7 >= b || a >= b && a - 1e-7 <= b);
}

struct point{
    double x, y;
};

struct line{
    double a, b, c;
};

struct vct{
    double x, y;
};

int operator *(vct a, vct b) {
    return a.x * b.y - a.y * b.x;
}

int operator ^(vct a, vct b) {
    return a.x * b.x + a.y * b.y;
}

line get_line(point a, point b) {
    return {b.y - a.y, a.x - b.x, b.x * a.y - a.x * b.y};
}

line get_bis(point a, point o, point b) {
    vct vec1 = {a.x - o.x, a.y - o.y}, vec2 = {b.x - o.x, b.y - o.y};
    point l = a, r = b;
    bool flag = true;
    while (flag) {
        point m = {(l.x + r.x) / 2, (l.y + r.y) / 2};
        vct vec_mid = {m.x - o.x, m.y - o.y};
        double an1 = abs(atan2(vec1 * vec_mid, vec1 ^ vec_mid)), an2 = abs(atan2(vec2 * vec_mid, vec2 ^ vec_mid));
        if (equals(an1, an2)) {
            l = m;
            flag = false;
            continue;
        }
        if (an1 > an2) {
            r = m;
        } else {
            l = m;
        }
    }
    return get_line(o, l);
}

int main() {
    point a, o, b;
    cin >> o.x >> o.y >> a.x >> a.y >> b.x >> b.y;
    line bis = get_bis(a, o, b);
    cout.precision(8);
    cout << fixed;
    cout << bis.a << " " << bis.b << " " << bis.c << endl;
    return 0;
}
