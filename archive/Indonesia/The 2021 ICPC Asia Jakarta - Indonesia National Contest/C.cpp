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

int dp[N], f[N], d[N];

int par[N];
int find_par(int u) {
	if(par[u] < 0) return u;
	par[u] = find_par(par[u]);
	return par[u];
}
bool merge(int u, int v) {
	u = find_par(u), v = find_par(v);
	if(u == v) return false;
	if(par[u] > par[v]) swap(u, v);
	par[u] += par[v];
	par[v] = u;
	return true;
}
int pos[N];

void BaoJiaoPisu() {
	int n; cin >> n;
	dp[0] = 0;
	dp[1] = 1;
	for(int i = 2; i <= 500; i++) {
		vector<int> v;
		v.pb(dp[i - 2]);
		v.pb(dp[i - 1]);
		for(int j = 1; j < i - 2; j++) {
			v.pb(dp[j] ^ dp[i - j - 2]);
		}

		sort(all(v));
		v.resize(unique(all(v)) - v.begin());
		for(int j = 0; j < v.size(); j++) {
			if(dp[i] == v[j]) dp[i]++;
			else break;
		}
	}

	for(int i = 501; i <= n; i++) dp[i] = 1;

	for(int i = 1; i <= n; i++) {
		par[i] = -1;
		int x; cin >> x;
		pos[x] = i;
	}

	for(int i = 1; i <= n; i++) {
		int x; cin >> x;
		merge(i, pos[x]);
	}

	int ans = 0;
	for(int i = 1; i <= n; i++) {
		if(find_par(i) == i) {
			int d = -par[i];
			ans ^= (dp[max(0, d - 2)] >= 1) ^ 1;
		}
	}

	cout << (ans ? "First" : "Second");
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
