#include<iostream>
#include<vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    int sum1, sum2, sum3;
    cout << "? 1 2" << endl;
    cin >> sum1;
    cout << "? 2 3" << endl;
    cin >> sum2;
    cout << "? 1 3" << endl;
    cin >> sum3;
    a[0] = (sum1 + sum3 - sum2) / 2;
    a[1] = (sum1 + sum2 - sum3) / 2;
    a[2] = (sum2 + sum3 - sum1) / 2;
    int sum;
    for (int i = 3; i < n; ++i) {
        cout << "? 1 " << i + 1 << endl;
        cin >> sum;
        a[i] = sum - a[0];
    }
    cout << "! ";
    for (int i = 0; i < n; ++i) {
        cout << a[i] << " ";
    }
    return 0;
}
