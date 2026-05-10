#include<bits/stdc++.h>

using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0): x(x), y(y) {};
};

istream& operator >> (istream& in, Point & a) {
    in >> a.x >> a.y;
    return in;
}

int get(Point a, Point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

signed main() {
    Point a, b, c, d;
    cin >> a >> b >> c >> d;
    cout.precision(15);
    cout << sqrt(get(a, c)) << endl;
    return 0;
}
