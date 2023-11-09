#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;

using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pld = pair<ld, ld>;

#define fi first
#define se second
#define left BAO
#define right ANH
#define btpc __builtin_popcount
#define btclz __builtin_clz
#define pb push_back
#define pf push_front
#define mp make_pair
#define ins insert

#define debug(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x.size());

int d4x[4] = {1, 0, -1, 0}; int d4y[4] = {0, 1, 0, -1};
int d8x[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int d8y[8] = {1, 1, 0, -1, -1, -1, 0, 1};

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class X, class Y>
    bool minimize(X &x, const Y &y) {
        if (x > y)
        {
            x = y;
            return true;
        }
        return false;
    }
template<class X, class Y>
    bool maximize(X &x, const Y &y) {
        if (x < y)
        {
            x = y;
            return true;
        }
        return false;
    }

const int MOD = 998244353; //998244353

const ll INF = 1e9;
const int N = 1e5 + 10;

int a[N];
ll dp[105][105];
ll pw[105];

void solve() {
	int n; cin >> n;
    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
    }

    pw[0] = 1;
    for(int i = 1; i <= n; i++) pw[i] = pw[i - 1] * 2;

    dp[1][1] = 1;
    for(int i = 1; i < n; i++) {
        for(int j = n; j >= 1; j--) {
            if(!dp[i][j]) continue;
            dp[i + 1][j + 1] += dp[i][j] * pw[j - 1] % MOD;
            dp[i + 1][j + 1] %= MOD;
            if(j > 1) {
                dp[i][j - 1] += dp[i][j];
                dp[i][j - 1] %= MOD;
            }
        }
    }

    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += dp[n][i];
        ans %= MOD;
    }
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #else 
    //online
    #endif

    int tc = 1, ddd = 0;
    // cin >> tc;
    while(tc--) {
        //ddd++;
        //cout << "Case #" << ddd << ": ";
        solve();
    }
}
