#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int t;
    cin >> t;
    while (t--) {
        int a, b, c;
        cin >> a >> b >> c;
        if (c == 0) {
            cout << "NO CURVE\n";
        }
        else if (c > 0) {
            cout << "CURVE UP\n";
        }
        else {
            cout << "CURVE DOWN\n";
        }
    }
    return 0;
}
