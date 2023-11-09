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
const int N = 20 + 10;

vector<int> edge[N];
string sa[N], sb[N];
int a[N], b[N];
ll dp[(1 << 20) + 10], f[(1 << 20) + 10], ans[N][N];

void solve(int n) {
    vector<string> teams;
    for(int i = 1; i <= n; i++) {
        edge[i].clear();
        cin >> sa[i] >> sb[i];
        teams.pb(sa[i]);
        teams.pb(sb[i]);
    }

    sort(all(teams));
    teams.resize(unique(all(teams)) - teams.begin());
    for(int i = 1; i <= n; i++) {
        a[i] = lower_bound(all(teams), sa[i]) - teams.begin() + 1;
        b[i] = lower_bound(all(teams), sb[i]) - teams.begin() + 1;
    }

    for(int i = 1; i <= n; i++) {
        int x = a[i];
        for(int j = 1; j <= n; j++) {
            if(i == j || a[i] == b[j]) continue;
            edge[i].pb(j);
        }
    }

    for(int i = 0; i < (1 << n); i++) dp[i] = f[i] = 0;
    f[0] = 1;
    for(int mask = 1; mask < (1 << n); mask++) {
        int current = btpc(mask);
        current = n - current + 1;
        for(auto nxt : edge[current]) {
            if(mask >> (nxt - 1) & 1 ^ 1) continue;
            f[mask] += f[mask ^ (1 << nxt - 1)];
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) ans[i][j] = 0;
    }

    dp[0] = 1;
    for(int mask = 1; mask < (1 << n); mask++) {
        int current = btpc(mask);
        for(auto nxt : edge[current]) {
            if(mask >> (nxt - 1) & 1 ^ 1) continue;
            ans[current][nxt] += dp[mask ^ (1 << nxt - 1)] * f[((1 << n) - 1) ^ mask];
            dp[mask] += dp[mask ^ (1 << nxt - 1)];
        }
    }

    cout << fixed;
    cout << setprecision(25);
    ll tot = f[(1 << n) - 1];
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) cout << 1.0 * ans[i][j] / tot << " ";
        cout << '\n';
    }
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
    while(cin >> tc) {
        //ddd++;
        //cout << "Case #" << ddd << ": ";
        if(tc == 0) break;
        solve(tc);
    }
}
