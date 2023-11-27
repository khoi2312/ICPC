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
const int N = 3e6 + 10;

int p;
ll power(int a, int b) {
    if(b == 0) return 1;
    ll ans = power(a, b >> 1);
    ans = ans * ans % p;
    if(b & 1) ans = ans * a % p;
    return ans;
}

ll suffix[N];
int d[N], exist[2 * N];

void solve() {
	int q, n; cin >> q >> n >> p;
    for(int i = 1; i <= n; i++) {
        cin >> d[i];
        if(d[i] < 2 * N) {
            exist[d[i]]++;
            exist[d[i]] %= p;
        }
    }
    sort(d + 1, d + 1 + n);

    string a = "icpcvn";
    string b = "icpcvn";

    suffix[n] = 1;
    for(int i = n - 1; i >= 1; i--) {
        suffix[i] = suffix[i + 1] * power(26, d[i + 1] - d[i]) + 1;
        suffix[i] %= p;
    }

    ll tot_a = 0;
    int iter_a = 0;
    for(int i = 0; i < a.size(); i++) {
        int x = a[i] - 'a';
        while(iter_a <= n && d[iter_a] < i + 1) ++iter_a;
        if(iter_a <= n) tot_a += 1ll * x * suffix[iter_a] % p * power(26, d[iter_a] - i + 1) % p;
        tot_a %= p; 
    }

    ll tot_b = 0;
    int iter_b = 0;
    for(int i = 0; i < b.size(); i++) {
        int x = b[i] - 'a';
        while(iter_b <= n && d[iter_b] < i + 1) ++iter_b;
        if(iter_b <= n) tot_b += 1ll * x * suffix[iter_b] % p * power(26, d[iter_b] - i + 1) % p;
        tot_b %= p; 
    }

    for(int i = 1; i < a.size(); i++) {
        if(exist[i]) {
            tot_a = (tot_a + 1) % p;
            tot_b = (tot_b + 1) % p;
        }
    }

    bool larger = false;
    string add_char, add_where;
    cin >> add_char >> add_where;
    ll ans = 0;
    for(int i = 0; i < q; i++) {
        if(add_where[i] == 'A') {
            if(exist[a.size()]) tot_a = (tot_a + exist[a.size()]) % p;
            a += add_char[i];
            if(a.size() <= b.size()) {
                if(a[a.size() - 1] > b[a.size() - 1] && !larger) {
                    break;
                } 

                if(a[a.size() - 1] < b[a.size() - 1]) larger = true;
            }
            while(iter_a <= n && d[iter_a] < a.size()) ++iter_a;
            int x = a.back() - 'a';
            if(iter_a <= n) tot_a += 1ll * x * suffix[iter_a] % p * power(26, d[iter_a] - a.size()) % p; 
            tot_a %= p;
        } else {
            if(exist[b.size()]) tot_b = (tot_b + exist[b.size()]) % p;
            b += add_char[i];
            if(a.size() >= b.size()) {
                if(a[b.size() - 1] > b[b.size() - 1] && !larger) {
                    break;
                } 

                if(a[b.size() - 1] < b[b.size() - 1]) larger = true;
            }
            while(iter_b <= n && d[iter_b] < b.size()) ++iter_b;
            int x = b.back() - 'a';
            // cout << iter_b << " " << suffix[iter_b] << endl;
            if(iter_b <= n) tot_b += 1ll * x * suffix[iter_b] % p * power(26, d[iter_b] - b.size()) % p; 
            tot_b %= p;
        }

        if(larger || a.size() < b.size()) {
            ll res = (tot_b + p - tot_a) % p;
            if(exist[a.size()]) res = (res + p - exist[a.size()]) % p;
            // cout << tot_a << " " << tot_b << '\n';
            // cout << res << '\n';
            ans = ans ^ (1ll * res * (i + 1));
        }
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
