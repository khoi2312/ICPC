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
const int N = 3e5 + 10;

int cnt[N][3];

void solve() {
    string s; cin >> s;
    int n = s.size();
    s = "#" + s;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 3; j++) cnt[i][j] = cnt[i - 1][j];
        if(s[i] == 'R') cnt[i][0]++;
        if(s[i] == 'P') cnt[i][1]++;
        if(s[i] == 'S') cnt[i][2]++;
    }

    int ans = 0, res = 0;
    for(int i = n; i >= 2; i--) {
        int cc = 0;
        for(int l = 1; l <= n; l += i) {
            int r = min(n, l + i - 1);
            cc += max({cnt[r][2] - cnt[l - 1][2], cnt[r][1] - cnt[l - 1][1], cnt[r][0] - cnt[l - 1][0]});
        }
        if(maximize(res, cc)) ans = i;
    }

    cout << ans << '\n';
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
    cin >> tc;
    while(tc--) {
        //ddd++;
        //cout << "Case #" << ddd << ": ";
        solve();
    }
}
