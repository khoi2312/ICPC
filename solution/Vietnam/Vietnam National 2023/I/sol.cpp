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
#define pb push_back
#define pf push_front
#define mp make_pair
#define ins insert
#define btpc __builtin_popcount
#define btclz __builtin_clz

#define sz(x) (int)(x.size());
#define all(x) x.begin(), x.end()
#define debug(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int d4x[4] = {1, 0, -1, 0}; int d4y[4] = {0, 1, 0, -1};
int d8x[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int d8y[8] = {1, 1, 0, -1, -1, -1, 0, 1};

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

template<class X, class Y>
	void add(X &x, const Y &y) {
		x = (x + y);
		if(x >= MOD) x -= MOD;
	}

template<class X, class Y> 
	void sub(X &x, const Y &y) {
		x = (x - y);
		if(x < 0) x += MOD;
	}

/* Author : Le Ngoc Bao Anh, DUT, Da Nang */

const ll INF = 1e9;
const int N = 1e5 + 10;

__int128 f(__int128 n, __int128 a, __int128 m, __int128 b = 0) {
	if(!a) return n * (b / m);
	__int128 ans = 0;
	if(a >= m) return (__int128)(a / m) * (n * (n - 1) / 2) + f(n, a % m, m, b);
	if(b >= m) return (__int128)(b / m) * n + f(n, a, m, b % m);
	__int128 tmp = (__int128)(a * (n - 1) + b) / m;
	return (__int128)(n - 1) * tmp - f(tmp, m, a, m - b - 1);
	return ans;
}

void BaoJiaoPisu() {
	int n; ll k; cin >> n >> k;

	auto count = [&](__int128 p, __int128 q) -> __int128 {
		if(!q) return k + 1;
		return f(n + 1, p, q, 0);
	};

	ll a = 0, b = 1;
	ll c = 1, d = 0;
	ll u = 0, v = 0;
	while(b + d <= n) {
		ll x = (a + c);
		ll y = (b + d);
		if(f(n + 1, x, y, 0) >= k) {
			ll l = 1, r = (n - d) / b;
			ll nxt_a;
			ll nxt_b;
			while(l <= r) {
				ll mid = (l + r) / 2;
				ll x = (mid * a + c);
				ll y = (mid * b + d);
				if(count(x, y) >= k) {
					nxt_a = u = x;
					nxt_b = v = y;
					l = mid + 1;
				} else {
					r = mid - 1;
				}
			}
			c = nxt_a;
			d = nxt_b;
		} else {		
			ll l = 1, r = (!d ? 1e18 + 5 : (n - b) / d);
			ll nxt_a;
			ll nxt_b;
			while(l <= r) {
				ll mid = (l + r) / 2;
				ll x = (a + mid * c);
				ll y = (b + mid * d);
				if(y > n) {
					r = mid - 1;
					continue;
				}
				if(count(x, y) < k) {
					nxt_a = x;
					nxt_b = y;
					l = mid + 1;
				} else {
					r = mid - 1;
				}
			}
			a = nxt_a;
			b = nxt_b;
		}
	}

	long long uu = u;
	long long vv = v;
	long long curr = count(uu, vv) - k;
	long long f = n / vv;
	f -= curr;
	cout << uu * f << " " << vv * f << '\n';
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
        BaoJiaoPisu();
    }
}
