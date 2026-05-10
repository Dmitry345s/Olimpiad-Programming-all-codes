#include<iostream>
#include<vector>
#include<string>
#include<iomanip>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<double> a(n);
    cin >> a[0];
    double minm = 30, maxm = 4000;
    vector<string> b(n);
    for (int i = 1; i < n; ++i) {
        cin >> a[i];
        cin >> b[i];
        if (b[i] == "closer") {
            if (a[i] > a[i - 1]) {
                maxm = max((a[i - 1] + a[i]) / 2, maxm);
                minm = max((a[i - 1] + a[i]) / 2, minm);
            } else {
                minm = min((a[i - 1] + a[i]) / 2, minm);
                maxm = min((a[i - 1] + a[i]) / 2, maxm);
            }
        } else {
            if (a[i] > a[i - 1]) {
                minm = min((a[i - 1] + a[i]) / 2, minm);
                maxm = min((a[i - 1] + a[i]) / 2, maxm);
            } else {
                minm = max((a[i - 1] + a[i]) / 2, minm);
                maxm = max((a[i - 1] + a[i]) / 2, maxm);
            }
        }
    }
    cout << setprecision(18) << minm << " " << setprecision(18) << maxm << endl;
    return 0;
}
