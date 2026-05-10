#include<iostream>
#include<vector>
#include<string>

using namespace std;

bool check(char x, int b){
    int y = 50;
    if ((int)x >= 65 && (int)x <= 90){
        y = (int)x - 54;
    } else if((int)x >= 48 && (int)x <= 57){
        y = (int)x - 48;
    }
    if (y < b){
        return true;
    }
    return false;
}

int to_10_int(string s, int b){
    int kof = 1;
    int x;
    int ans = 0;
    for (int i = s.size() - 1; i >= 0; --i){
        if (s[i] >= 65 && s[i] <= 90){
            x = (int)s[i] - 54;
        } else{
            x = (int)s[i] - 48;
        }
        if (x != 0 && kof > 1000000000){
            return 1000000001;
        }
        ans += x * kof;
        if (kof < 1000000000){
            kof *= b;
        }
        if (ans > 1000000000){
            return 1000000001;
        }
    }
    return ans;
}

int main(){
    int k, b;
    cin >> k >> b;
    vector<int> ms(k);
    for (int i = 0; i < k; ++i){
        cin >> ms[i];
    }
    string _;
    getline(cin, _);
    string s;
    getline(cin, s);
    vector<int> dp(s.size() + 1, 1e9);
    dp[0] = 0;
    for (int i = 1; i < dp.size(); ++i){
        dp[i] = dp[i - 1] + 1;
        for (int j = i; j >= 0; --j){
            if (check(s[j], b)){
                int v = to_10_int(s.substr(j, i - j + 1), b);
                if (v > 1000000000){
                    break;
                }
                for (int l = 0; l < ms.size(); ++l){
                    if (ms[l] >= v){
                        dp[i] = min(dp[i], dp[j - 1] + 2 + l);
                        break;
                    }
                }
            } else{
                break;
            }
        }
    }

    return 0;
}
