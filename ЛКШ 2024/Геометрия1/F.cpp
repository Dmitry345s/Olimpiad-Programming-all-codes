#include<bits/stdc++.h>

using namespace std;

signed main() {
    string s, st1, st2;
    cin >> s >> st1;
    cin >> s >> st2;
    cout << "TOUCH " << st1 << endl;
    string now;
    cin >> now;
    cout << "LINE " << st2 << " " << now.substr(1, 4) << endl;
    cin >> now;
    array<string, 2> a1, a2;
    cout << "INTERSECT " << st1 << " " << now.substr(1, 4) << endl;
    string now2;
    cin >> now2;
    //cout << now2 << endl;
    if (now2.back() == '}') {
        cout << "TANGENT " << now.substr(1, 4) << endl;
        return 0;
    }
    string now3;
    cin >> now3;
    a1[0] = now2.substr(1, 4);
    a1[1] = now3.substr(0, 4);
    cout << "TOUCH " << st1 << endl;
    cin >> now;
    cout << "LINE " << st2 << " " << now.substr(1, 4) << endl;
    cin >> now;
    cout << "INTERSECT " << st1 << " " << now.substr(1, 4) << endl;
    cin >> now2;
    if (now2.back() == '}') {
        cout << "TANGENT " << now.substr(1, 4) << endl;
        return 0;
    }
    cin >> now3;
    a2[0] = now2.substr(1, 4);
    a2[1] = now3.substr(0, 4);
    string p1, p2;
    string l1, l2, l3, l4;
    cout << "LINE " << a1[0] << " " << a2[0] << endl;
    cin >> l1;
    l1 = l1.substr(1, 4);
    cout << "LINE " << a1[1] << " " << a2[1] << endl;
    cin >> l2;
    l2 = l2.substr(1, 4);
    cout << "INTERSECT " << l1 << " " << l2 << endl;
    cin >> p1;
    if (p1 == "{}") {
        cout << "TOUCH " << st1 << endl;
        cin >> now;
        cout << "LINE " << st2 << " " << now.substr(1, 4) << endl;
        cin >> now;
        cout << "INTERSECT " << st1 << " " << now.substr(1, 4) << endl;
        cin >> now2;
        //cout << now2 << endl;
        if (now2.back() == '}') {
            cout << "TANGENT " << now.substr(1, 4) << endl;
            return 0;
        }
        cin >> now3;
        a1[0] = now2.substr(1, 4);
        a1[1] = now3.substr(0, 4);
        cout << "LINE " << a1[0] << " " << a2[0] << endl;
        cin >> l1;
        l1 = l1.substr(1, 4);
        cout << "LINE " << a1[1] << " " << a2[1] << endl;
        cin >> l2;
        l2 = l2.substr(1, 4);
        cout << "INTERSECT " << l1 << " " << l2 << endl;
        cin >> p1;
    }
    p1 = p1.substr(1, 4);
    cout << "LINE " << a1[0] << " " << a2[1] << endl;
    cin >> l3;
    l3 = l3.substr(1, 4);
    cout << "LINE " << a1[1] << " " << a2[0] << endl;
    cin >> l4;
    l4 = l4.substr(1, 4);
    cout << "INTERSECT " << l3 << " " << l4 << endl;
    cin >> p2;
    if (p2 == "{}") {
        cout << "TOUCH " << st1 << endl;
        cin >> now;
        cout << "LINE " << st2 << " " << now.substr(1, 4) << endl;
        cin >> now;
        cout << "INTERSECT " << st1 << " " << now.substr(1, 4) << endl;
        cin >> now2;
        //cout << now2 << endl;
        if (now2.back() == '}') {
            cout << "TANGENT " << now.substr(1, 4) << endl;
            return 0;
        }
        cin >> now3;
        a1[0] = now2.substr(1, 4);
        a1[1] = now3.substr(0, 4);
        cout << "LINE " << a1[0] << " " << a2[1] << endl;
        cin >> l3;
        l3 = l3.substr(1, 4);
        cout << "LINE " << a1[1] << " " << a2[0] << endl;
        cin >> l4;
        l4 = l4.substr(1, 4);
        cout << "INTERSECT " << l3 << " " << l4 << endl;
        cin >> p2;
    }
    p2 = p2.substr(1, 4);
    string l5;
    cout << "LINE " << p1 << " " << p2 << endl;
    cin >> l5;
    l5 = l5.substr(1, 4);
    cout << "INTERSECT " << l5 << " " << st1 << endl;
    string ans1, ans2;
    cin >> ans1 >> ans2;
    cout << "LINE " << ans1.substr(1, 4) << " " << st2 << endl;
    string rans;
    cin >> rans;
    cout << "TANGENT " << rans.substr(1, 4) << endl;
    return 0;
}
