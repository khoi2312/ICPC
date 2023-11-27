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
const int N = 2e5 + 10;

int ans[505][505];
int a[N];

void BaoJiaoPisu() {
	int n; cin >> n;
	int X = 450;
	for(int i = 1; i <= n; i++) {
		char c; cin >> c;
		int x = c - '0';
		a[i] = x;
		if(!x) {
			for(int p = 1; p <= X; p++) {
				ans[p][i % p]++;
			}
		}
	}	

	int q; cin >> q;
	while(q--) {	
		int t; cin >> t;
		if(t == 1) {
			int x; cin >> x;
			a[x] = 1;
			for(int p = 1; p <= X; p++) {
				ans[p][x % p]--;
			}
		}

		if(t == 2) {
			int x; cin >> x;
			a[x] = 0;
			for(int p = 1; p <= X; p++) {
				ans[p][x % p]++;
			}
		}

		if(t == 3) {
			int x, k; cin >> x >> k;
			if(x == k) x = 0;
			if(k <= X) {
				cout << ans[k][x] << '\n';
			} else {
				int ans = 0;
				for(int i = (x ? x : k); i <= n; i += k) ans += a[i] ^ 1;
				cout << ans << '\n';
			}
		}
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
