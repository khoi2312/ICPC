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

vector<int> ord;
vector<int> g[N], rev[N], adj[N];
bool visited[N];
int f[N][LOG + 2];
int depth[N];
int ans[N];

void dfs(int u) {
	visited[u] = true;
	for(auto v : g[u]) {
		if(!visited[v]) dfs(v);
	}
	ord.pb(u);
}

void dfs2(int u) {
	for(auto v : adj[u]) {
		ans[v] += ans[u];
		dfs2(v);
	}
}

int find_lca(int u, int v) {
	if(depth[u] < depth[v]) swap(u, v);
	for(int i = LOG; i >= 0; i--) {
		if(depth[u] - (1 << i) >= depth[v]) u = f[u][i];
	}

	if(u == v) return u;

	for(int i = LOG; i >= 0; i--) {
		if(f[u][i] != f[v][i]) {
			u = f[u][i];
			v = f[v][i];
		}
	}

	return f[u][0];
}

void BaoJiaoPisu() {
	int n, m; cin >> n >> m;
	for(int i = 1; i <= m; i++) {
		int u, v; cin >> u >> v;
		g[u].pb(v);
		rev[v].pb(u);
	}

	dfs(1);
	reverse(all(ord));

	depth[1] = 1;
	for(auto u : ord) {
		if(u == 1) continue;
		ans[u] = (rev[u].size() > 1 ? 0 : 1);
		int p = rev[u][0];
		for(auto x : rev[u]) p = find_lca(p, x);
		adj[p].pb(u);
		depth[u] = depth[p] + 1;
		f[u][0] = p;
		for(int j = 1; j <= LOG; j++) {
			if(depth[u] <= (1 << j)) break;
			int x = f[u][j - 1];
			f[u][j] = f[x][j - 1];
		}
	}

	dfs2(1);
	for(int i = 1; i <= n; i++) cout << ans[i] << " ";
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
        BaoJiaoPisu();
    }
}
