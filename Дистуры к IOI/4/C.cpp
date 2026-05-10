#include<bits/stdc++.h>
#include "grader.h"
using namespace std;

vector<int> findPerm(int n) {
    vector<int> a(n);
    for (int i = 0; i < n; ++i) a[i] = i;
    vector<vector<int>> ch(n, vector<int> (n));
    vector<int> r(n);
    int now = numMatches(a);
    for (int i = 0; i < n; ++i) {
        vector<int> all;
        for (int j = i + 1; j < n; ++j) {
            if (r[i] || r[j]) continue;
            swap(a[i], a[j]);
            int tu = numMatches(a);
            if (abs(now - tu) == 2) {
                r[i] = 1;
                r[j] = 1;
            }
            if (tu < now) {
                swap(a[i], a[j]);
            } else {
                now = tu;
                if (tu > now) all.push_back(j);
            }
        }
        if (!all.empty()) all.pop_back();
        for (int v : all) {
            r[v] = 1;
        }
    }
    return a;
}
