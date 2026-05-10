#include<iostream>

using namespace std;

bool check(long long k, long long n){
    long long checker = (n + 1) / 2;
    long long cnt = 0;
    while (n > k){
        n -= k;
        cnt += k;
        n -= n / 10;
    }
    cnt += n;
    if (cnt >= checker){
        return true;
    } else{
        return false;
    }
}
long long i_search(long long l, long long r, long long n){
    long long m = (l + r) / 2;
    if (l + 1 >= r){
        if (check(l, n)){
            return l;
        } else{
            return r;
        }
    }
    if (check(m, n)){
        return i_search(l, m, n);
    } else{
        return i_search(m, r, n);
    }
}
int main(){
    long long n;
    cin >> n;
    long long ans = i_search(1, n, n);
    cout << ans;
    return 0;
}
