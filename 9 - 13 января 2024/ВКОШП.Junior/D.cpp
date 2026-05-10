#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    map <string, bool> allerg;
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        string a;
        cin >> a;
        allerg[a] = true;
    }
    int c;
    cin >> c;
    for (int i = 0; i < c; ++i) {
        int l;
        cin >> l;
        int cnt = 0;
        for (int j = 0; j < l; ++j) {
            string a;
            cin >> a;
            if (allerg[a]) {
                cnt++;
            }
        }
        if (cnt == l) {
            cout << "NO" << endl;
        } else if(k + l - cnt + m > n) {
            cout << "YES" << endl;
        } else {
            cout << "MAYBE" << endl;
        }
    }
    return 0;
}
