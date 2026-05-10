#include<iostream>
#include<cmath>
#include<iomanip>

using namespace std;

bool equals(double a, double b) {
    return (a <= b && a + 1e-10 >= b || a >= b && a - 1e-10 <= b);
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

double operator *(vct a, vct b) {
    return a.x * b.y - a.y * b.x;
}

double operator ^(vct a, vct b) {
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
    point a, b, c;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
    line bis1 = get_bis(a, b, c), bis2 = get_bis(b, a, c);
    double const1 = bis1.a * bis2.c - bis1.c * bis2.a, const2 = bis2.a * bis1.b - bis2.b * bis1.a;
    double y = const1 / const2, x;
    if (bis1.a == 0) {
        x = -1 * (bis2.c + bis2.b * y) / bis2.a;
    } else {
        x = -1 * (bis1.c + bis1.b * y) / bis1.a;
    }
    cout << setprecision(10) << x << " " << y << endl;
    return 0;
}
