#include<iostream>
#include<vector>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    long long cnt = 0, r = 1;
    long long x;
    if (min(n, m) < max(n, m)){
        x = min(n, m) * 2 + 1;
    } else{
        x = min(n, m) * 2;
    }
    while (r * r <= x){
        cnt += x / r - r + 1;
        r += 1;
    }
    cout << cnt << endl;
    return 0;
}
