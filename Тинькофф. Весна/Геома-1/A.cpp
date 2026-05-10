#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

struct vct{
    int x, y;
};

int operator *(vct a, vct b) {
    return a.x * b.y - b.x * a.y;
}

int main() {
    int x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    vct a = {x2 - x1, y2 - y1}, b = {x3 - x1, y3 - y1};
    double s2 = abs(a * b);
    cout << s2 / 2;
    return 0;
}
