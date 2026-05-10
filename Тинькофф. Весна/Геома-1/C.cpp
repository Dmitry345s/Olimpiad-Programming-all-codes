#include<iostream>
#include<cmath>
#include<iomanip>

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

int main() {
    long long x1, y1, x2, y2, x3, y3, x4, y4;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    vct vec1 = {x1 - x2, y1 - y2}, vec2 = {x3 - x2, y3 - y2}, vec3 = {x4 - x2, y4 - y2};
    double l = abs(atan2(vec1 * vec3, vec1 ^ vec3)), r = abs(atan2(vec2 * vec3, vec3 ^ vec2)), all = abs(atan2(vec1 * vec2, vec1 ^ vec2));
    if (l + r <= all && l + r + 1e-5 >= all || l + r >= all && l + r - 1e-5 <= all || x4 == x2 && y4 == y2) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
