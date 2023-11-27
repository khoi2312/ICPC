#include <bits/stdc++.h>
using namespace std;
#define ll long long


long long dp[50][50];
ll n;
bool winb(long long sa, long long sb) {
    return sb >= n && sb >= sa + 2;
}
bool wina(long long sa, long long sb) {
    return sa >= n && sa >= sb + 2;
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
    
        ll sa ,sb ; cin >> n >> sa >> sb;
        if (sa < sb) swap(sa,sb);
        // sa >= sb
        for (int i = 0 ; i <= sa + sb + 5 ; i++) {
            for (int j = 0 ; j <= sa + sb + 5 ; j++) {
                dp[i][j] = 0;
            
        }
        }
        dp[0][0] = 1;

        for (int i = 0 ; i <= sa + sb ; i++) {
            for (int j = 0 ; j <= sa + sb ; j++) {
                //
                if (i+1 == sa && j == sb) {
                    dp[i+1][j] += dp[i][j];
                }
                else {
                    if (!wina(i+1,j)) dp[i+1][j] += dp[i][j];
                }
                
                if (!winb(i,j+1)) dp[i][j+1] += dp[i][j];
            
        }
        }

        if (sa < n) {cout << 0 << '\n';continue;}
        if (sa < sb+2) {cout << 0 << '\n';continue;}
        
        
        cout << dp[sa][sb] << '\n';



    }
    return 0;
}
