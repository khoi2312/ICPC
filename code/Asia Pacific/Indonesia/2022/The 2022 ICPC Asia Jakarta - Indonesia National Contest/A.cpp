#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());

    int cntBal = 0, maxRate = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (a[k] - a[i] <= m) {
                    cntBal += 1;
                    maxRate = max(maxRate, a[i] + a[j] + a[k]);
                }
            }
        }
    }

    if (cntBal)
        cout << -1 << '\n';
    else
        cout << cntBal << ' ' << maxRate << '\n';

    return 0;
}