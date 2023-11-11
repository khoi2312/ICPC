#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 1;
int A[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int q; cin >> q;
    int bal = 0;
    while (q--) {
        char c; cin >> c; 
        int x; cin >> x;

        if (c == '+') {
            while (A[x] == 1) {
                A[x] = 0;
                bal--;
                x++;
            }
            A[x]++;
            if (A[x] == 0) bal -= 1; else bal += 1;
        }
        else {
            while (A[x] == -1) {
                A[x] = 0;
                bal--;
                x++;
            }
            A[x]--;
            if (A[x] == 0) bal -= 1; else bal += 1;
        }
        if (bal == 0) cout << "YES\n"; else cout << "NO\n";
    }

    return 0;
}