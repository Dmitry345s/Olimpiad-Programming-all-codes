#include<iostream>
#include<cmath>

using namespace std;

struct vct{
    long long x, y;
};

long long operator *(vct a, vct b) {
    return a.x * b.y - a.y * b.x;
}

long long operator ^(vct a, vct b) {
    return a.x * b.x + a.y * b.y;
}

struct point{
    int x, y;
};

bool bounding_box(int x1, int x2, int x3, int x4) {
    return max(min(x1, x2), min(x3, x4)) <= min(max(x1, x2), max(x3, x4));
}

double area(point a, point b, point c) {
    vct vec1 = {a.x - c.x, a.y - c.y}, vec2 = {b.x - c.x, b.y - c.y};
    double s2 = vec1 * vec2;
    return s2 / 2;
}

int main() {
    point a, b, c, d;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
    if (!bounding_box(a.x, b.x, c.x, d.x) || !bounding_box(a.y, b.y, c.y, d.y)) {
        cout << "NO" << endl;
        return 0;
    }
    if (area(a, b, c) * area(a, b, d) <= 0 && area(c, d, a) * area(c, d, b) <= 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
