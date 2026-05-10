#include<iostream>
#include<cmath>
#include<iomanip>

using namespace std;

struct point{
    int x, y;
};

struct line{
    int a, b, c;
};

bool equals(double a, double b) {
    return (a <= b && a + 1e-7 >= b || a >= b && a - 1e-7 <= b);
}

line get_line(point a, point b) {
    line ans;
    ans.a = b.y - a.y;
    ans.b = a.x - b.x;
    ans.c = b.x * a.y - b.y * a.x;
    return ans;
}

int main() {
    point a, b, a1, b1;
    cin >> a.x >> a.y >> b.x >> b.y >> a1.x >> a1.y >> b1.x >> b1.y;
    line f = get_line(a, b), s = get_line(a1, b1);
    double const1 = f.a * s.c - f.c * s.a, const2 = s.a * f.b - s.b * f.a;
    if (const2 == 0) {
        if (const1 == 0) {
            cout << 2 << endl;
            return 0;
        }
        cout << 0 << endl;
        return 0;
    }
    double y = const1 / const2, x;
    if (f.a == 0) {
        x = -1 * (s.c + s.b) / s.a;
    } else {
        x = -1 * (f.c + f.b * y) / f.a;
    }
    cout << 1 << " " << x << " " << y << endl;
    return 0;
}
