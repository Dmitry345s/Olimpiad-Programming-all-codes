#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main(){
    long long w, k;
    string m;
    cin >> w >> m >> k;
    w /= k;
    int size_ = m.size();
    string check = "1";
    for (int i = 0; i < size_; ++i){
        check.push_back('0');
    }
    long long check2 = stoll(check);
    long long m2 = stoll(m);
    long long dif = check2 - m2;
    long long ans = 0;
    if (dif * size_ >= w){
        ans += w / size_;
        cout << ans;
        return 0;
    } else{
        ans += dif;
        w -= dif * size_;
    }
    while (true){
        check.push_back('0');
        size_ += 1;
        m2 = check2;
        check2 = stoll(check);
        dif = check2 - m2;
        if (dif * size_ >= w){
            ans += w / size_;
            cout << ans;
            return 0;
        } else{
            ans += dif;
            w -= dif * size_;
        }
    }
}
