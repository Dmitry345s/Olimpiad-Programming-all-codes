#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
	int t;
	cin >> t;
	for (int _ = 0; _ < t; _++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		if (a == 0) {
			cout << 1 << '\n';
			continue;
		}
		int ans = 0;
		int alice = 0;
		int bob = 0;
		ans += a;
		alice += a;
		bob += a;
		ans += min(b, c) * 2;
		cout << ans + min({ d + max(b, c) - min(b, c), alice + 1, bob + 1}) << '\n';
	}
}
