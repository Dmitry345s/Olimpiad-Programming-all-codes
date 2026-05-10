#include<bits/stdc++.h>

using namespace std;

long long encode(double k) {
    long long *all = (long long *)&k;
    return all[0];
}

double decode(long long k) {
    double *p = (double*)&k;
    return p[0];
}
