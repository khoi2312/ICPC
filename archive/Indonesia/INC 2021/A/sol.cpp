#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    int ans = 0;
    set<int> s;
    for (int x: a) {
        if (x > 0) s.insert(x);
        if (x < 0 && !s.count(-x)) ans++;
    }
    
    cout << ans << '\n';
    return 0;
}

