#include<iostream>
#include<vector>

using namespace std;

int main() {
    vector<long long> c;
    long long i = 1, j = 1;
    while (c.size() < 1e7) {
        if (i * i < j * j * j) {
            c.push_back(i * i);
            i += 1;
        } else if (i * i == j * j * j) {
            c.push_back(i * i);
            i += 1;
            j += 1;
        } else {
            c.push_back(j * j * j);
            j += 1;
        }
    }
    int x;
    cin >> x;
    cout << c[x - 1] << endl;
    return 0;
}
