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

const int MOD = 1e9 + 7; //998244353

const ll INF = 1e9;
const int N = 1e5 + 10;

int ans[N], a[N], cnt[N], pref[N];

void solve() {
	int n, m, k; cin >> n >> m >> k;
    for(int i = 1; i <= m; i++) cin >> a[i];
    for(int l = 1; l <= m; l++) {
        int lim = min(l + k - 1, m);
        for(int i = 1; i <= n; i++) {
            cnt[i] = 0;
        }

        for(int i = 0; i <= m; i++) pref[i] = 0;

        for(int r = l; r <= lim; r++) {
            ++cnt[a[r]];
        }

        for(int i = 1; i <= n; i++) {
            ++pref[cnt[i]];
        }

        for(int i = 1; i <= m; i++) {
            pref[i] += pref[i - 1];
        }

        for(int i = 1; i <= n; i++) {
            maximize(ans[i], n - pref[cnt[i]]);
        }
        
        for(int r = lim; r >= l; r--) {
            int x = a[r];
            cnt[x]--;
            ++pref[cnt[x]];
            maximize(ans[x], n - pref[cnt[x]]);
        }
    }

    for(int i = 1; i <= n; i++) cout << ans[i] + 1 << " ";
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
