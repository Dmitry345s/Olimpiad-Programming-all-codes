#include<bits/stdc++.h>

using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0): x(x), y(y) {}
};

istream& operator >> (istream & in, Point & a) {
    in >> a.x >> a.y;
    return in;
}

struct Vector {
    int x, y;
    Vector(Point a, Point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
};

int get(Vector a) {
    return a.x * a.x + a.y * a.y;
}

signed main() {
    Point a, b;
    cin >> a >> b;
    int ndlen;
    cin >> ndlen;
    cout.precision(10);
    Vector v1 = Vector(a, b);
    cout << v1.x << " " << v1.y << endl;
    double len = sqrt(get(v1));
    cout << v1.x / len << " " << v1.y / len << endl;
    cout << v1.x / len * ndlen << " " << v1.y / len * ndlen << endl;
    cout << v1.y << " " << -v1.x << endl;
    cout << -v1.y << " " << v1.x << endl;
    return 0;
}
