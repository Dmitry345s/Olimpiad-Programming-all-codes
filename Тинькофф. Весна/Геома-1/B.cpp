#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>

using namespace std;

struct vct{
    double x, y;
};

int operator *(vct a, vct b) {
    return a.x * b.y - a.y * b.x;
}

int operator ^(vct a, vct b) {
    return a.x * b.x + a.y * b.y;
}

int main() {
    vct vec1, vec2;
    cin >> vec1.x >> vec1.y >> vec2.x >> vec2.y;
    cout << setprecision(7) << abs(atan2(vec1 * vec2, vec1 ^ vec2));
    return 0;
}
