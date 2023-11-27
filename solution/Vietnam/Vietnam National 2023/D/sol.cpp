#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> cnt(n + 1);
    long long ans = 0;
    for (int l = 0, r = 0; l < n; l++) {
        while (r < n && cnt[a[r]] == 0) {
            cnt[a[r]]++;
            r++;
        }
        ans += r - l;
        cnt[a[l]]--;
    }

    cout << ans << '\n';    
}

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
        solve();
    }
    return 0;
}
