#include<bits/stdc++.h>
#include "grader.h"

using namespace std;

vector<int> a;
int n;

int init(int n1, vector<int> a1) {
    a = a1;
    n = n1;
    return 30;
}

void go(int k, bool b) {
    vector<int> was(n + 1);
    if (k % 2 == 1) {
        was[0] = b;
        for (int i = 0; i < n; ++i) {
            if (a[i] == i || a[i] > i || was[a[i]] == 0) {
                b = setb(b);
                was[i + 1] = b;
                continue;
            }
            b = setb(b ^ 1);
            was[i + 1] = b;
        }
    }
    if (k % 2 == 0) {
        was[n] = b;
        for (int i = n - 1; i >= 0; --i) {
            if (a[i] == i || a[i] < i || was[a[i] + 1] == 0) {
                b = setb(b);
                was[i] = b;
                continue;
            }
            b = setb(b ^ 1);
            was[i] = b;
        }
    }
}
