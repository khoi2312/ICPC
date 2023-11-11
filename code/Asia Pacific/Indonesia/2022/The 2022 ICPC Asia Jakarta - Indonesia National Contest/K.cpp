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
const int LOG = 16;

int ans[N], a[N];
int f[N][LOG + 2];

int p = 0;
int query(int l, int r) {
	int x = 31 - btclz(r - l + 1);
	return max(f[l][x], f[r - (1 << x) + 1][x]);
};

void solve(int l, int r) {
	if(l > r) return;

	int x = query(l, r);
	if(x != r + 1) {
		cout << -1;
		exit(0);
	}	

	if(l == r) {
		ans[l] = ++p;
		return;
	}

	int lo = l, hi = r, pos = 0;
	while(lo <= hi) {
		int mid = (lo + hi) >> 1;
		if(query(l, mid) == r + 1) {
			pos = mid;
			hi = mid - 1;
		} else lo = mid + 1;
	}

	solve(l, pos - 1);
	solve(pos + 1, r);
	ans[pos] = ++p;
};

void BaoJiaoPisu() {
	int n; cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		if(a[i] == -1) a[i] = n + 1;
		f[i][0] = a[i];
	}		

	for(int j = 1; j <= LOG; j++) {
		for(int i = 1; i <= n - (1 << j) + 1; i++) {
			int u = i + (1 << j - 1);
			f[i][j] = max(f[i][j - 1], f[u][j - 1]);
		}
	}

	solve(1, n);
	for(int i = 1; i <= n; i++) {
		cout << ans[i];
		assert(ans[i] >= 1 && ans[i] <= n);
		if(i < n) cout << " ";
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
