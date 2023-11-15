#include <bits/stdc++.h>
using namespace std;

const int N = 500 * 500 + 1;
bool dp[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> l(n);
    for (int i = 0; i < n; i++)
        cin >> l[i];
    
    dp[0] = true;
    int L = 0;
    for (int x: l) if (x != 2) L += x;
    
    int cnt = 0;
    for (int x: l) {
        if (x != 2) 
            for (int i = L; i >= x; i--)
                dp[i] |= dp[i - x];
        else
            cnt += 1;
    }
    
    for (int x = 0; x <= L; x++) {
        int y = L - x;
        int z = abs(x - y);
        if (dp[x] && z <= 2 * cnt && z % 2 == 0) {
            cout << "YES\n";
            return 0;
        }
    }
    
    cout << "NO\n";
    return 0;
}

