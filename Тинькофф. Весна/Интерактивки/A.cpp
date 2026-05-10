#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main() {
    vector<int> d(19);
    d = {2, 3, 4, 5, 7, 9, 11, 13, 17, 19, 23, 25, 29, 31, 37, 41, 43, 47, 49};
    string ans;
    int cnt = 0;
    for (int i = 0; i < 19; ++i) {
        cout << d[i] << endl;
        cin >> ans;
        if (ans == "yes") {
            cnt += 1;
        }
    }
    if (cnt >= 2) {
        cout << "composite" << endl;
    } else {
        cout << "prime" << endl;
    }
    return 0;
}
