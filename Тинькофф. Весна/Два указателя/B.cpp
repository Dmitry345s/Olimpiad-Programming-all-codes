#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
    int n, n1, n2, n3;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    cin >> n1;
    vector<int> a1(n1);
    for (int i = 0; i < n1; ++i) {
        cin >> a1[i];
    }
    sort(a1.begin(), a1.end());
    cin >> n2;
    vector<int> a2(n2);
    for (int i = 0; i < n2; ++i) {
        cin >> a2[i];
    }
    sort(a2.begin(), a2.end());
    cin >> n3;
    vector<int> a3(n3);
    for (int i = 0; i < n3; ++i) {
        cin >> a3[i];
    }
    sort(a3.begin(), a3.end());
    int i = 0, i1 = 0, i2 = 0, i3 = 0;
    vector<int> ans(4), r_ans(4);
    r_ans[0] = a[0];
    r_ans[1] = a1[0];
    r_ans[2] = a2[0];
    r_ans[3] = a3[0];
    ans[0] = a[0];
    ans[1] = a1[0];
    ans[2] = a2[0];
    ans[3] = a3[0];
    sort(ans.begin(), ans.end());
    int minm = ans[3] - ans[0];
    while (i < n && i1 < n1 && i2 < n2 && i3 < n3) {
        ans[0] = a[i];
        ans[1] = a1[i1];
        ans[2] = a2[i2];
        ans[3] = a3[i3];
        sort(ans.begin(), ans.end());
        if (ans[3] - ans[0] < minm) {
            minm = ans[3] - ans[0];
            r_ans[0] = a[i];
            r_ans[1] = a1[i1];
            r_ans[2] = a2[i2];
            r_ans[3] = a3[i3];
        }
        if (a[i] == ans[0]) {
            i += 1;
        }
        if (a1[i1] == ans[0]) {
            i1 += 1;
        }
        if (a2[i2] == ans[0]) {
            i2 += 1;
        }
        if (a3[i3] == ans[0]) {
            i3 += 1;
        }
    }
    cout << r_ans[0] << " " << r_ans[1] << " " << r_ans[2] << " " << r_ans[3] << endl;
    return 0;
}
