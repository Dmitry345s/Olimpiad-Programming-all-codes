#include<iostream>

using namespace std;

int main(){
    int n, a, b, c;
    cin >> n >> a >> b >> c;
    if (a + b + c > n){
        cout << 1 << " " << 1 << " " << n - 2;
        return 0;
    }
    int a1 = a, b1= b, c1 = c;
    n -= a + b + c;
    int temp = n / (a + b + c);
    a1 += temp * a;
    b1 += temp * b;
    c1 += temp * c;
    n %= a + b + c;
    if (a == max(max(a, b), c)){
        temp = n / (b + c);
        b1 += temp * b;
        c1 += temp * c;
        n %= b + c;
        if (b == max(b, c)){
            c1 += n;
        } else{
            b1 += n;
        }
    } else if (b == max(max(a, b), c)){
        temp = n / (a + c);
        a1 += temp * a;
        c1 += temp * c;
        n %= a + c;
        if (a == max(a, c)){
            c1 += n;
        } else{
            a1 += n;
        }
    } else{
        temp = n / (a + b);
        a1 += temp * a;
        b1 += temp * b;
        n %= a + b;
        if (b == max(b, a)){
            a1 += n;
        } else{
            b1 += n;
        }
    }
    cout << a1 << " " << b1 << " " << c1;
}
