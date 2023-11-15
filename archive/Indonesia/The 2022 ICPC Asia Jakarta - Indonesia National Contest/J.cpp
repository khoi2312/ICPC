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

int a[N];
ll dp[N];

void BaoJiaoPisu() {
	int n, q; cin >> n >> q;;
	a[0] = a[n + 1] = 1;
	set<int> s; s.ins(0); s.ins(n + 1);

	dp[1] = 1;
	for(int i = 2; i <= n; i++) {
		dp[i] = dp[i - 1] + 1ll * i * (i - 1) / 2 + i;
	}

	auto calc = [&](int x) -> ll {
		auto iter = s.upper_bound(x);
		return dp[(*iter) - x - 1];		
	};

	ll ans = calc(0);
	while(q--) {
		int x; cin >> x;
		if(!a[x]) {
			a[x] = 1;
			auto iter = s.lower_bound(x);
			--iter;
			ans -= calc((*iter));
			s.ins(x);
			ans += calc(x);
			iter = s.lower_bound(x);
			iter--;
			ans += calc((*iter));
		} else {
			a[x] = 0;
			auto iter = s.lower_bound(x);
			ans -= calc(x);
			iter--;
			ans -= calc((*iter));
			s.erase(x);
			iter = s.upper_bound(x);
			iter--; 
			ans += calc((*iter));
		}

		cout << ans << '\n';
	}
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int tc = 1, ddd = 0;
    // cin >> tc;
    while(tc--) {
        //ddd++;
        //cout << "Case #" << ddd << ": ";
        BaoJiaoPisu();
    }
}
