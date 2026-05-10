#include<iostream>
#include<cmath>
#include<iomanip>

using namespace std;

struct vct{
    int x, y;
};

int operator *(vct a, vct b) {
    return a.x * b. y - a.y * b.x;
}

int operator ^(vct a, vct b) {
    return a.x * b.x + a.y * b.y;
}

int main() {
    int x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    vct vec1 = {x3 - x1, y3 - y1}, vec2 = {x2 - x1, y2 - y1}, Vct1 = {x1 - x2, y1 - y2};
    vct Vct2 = {x3 - x2, y3 - y2}, Vec1 = {x1 - x3, y1 - y3}, Vec2 = {x2 - x3, y2 - y3};
    double ans = max(max(abs(atan2(vec1 * vec2, vec1 ^ vec2)), abs(atan2(Vct1 * Vct2, Vct1 ^ Vct2))), abs(atan2(Vec1 * Vec2, Vec1 ^ Vec2)));
    cout << setprecision(8) << ans * 180 / 3.14159265 << endl;
    return 0;
}
