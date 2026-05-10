#include<iostream>
#include<vector>

using namespace std;

int main() {
    int a, i;
    cin >> a >> i;
    cout << (a ^ (1 << i)) << endl;
    return 0;
}
