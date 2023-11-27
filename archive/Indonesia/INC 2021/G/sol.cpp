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

int cntComp = 0, Time = 0;
int Num[N], Low[N], id[N];
vector<int> g[N], adj[N];
bool visited[N], f[N], treasure[N];
int cnt[N];
bool inEdge[N], outEdge[N];
stack<int> s;

void dfs2(int u) {
	visited[u] = true;
	for(auto v : g[u]) {
		if(!visited[v]) {
			dfs2(v);
		}
		cnt[u] += cnt[v];
	}
}

void dfs(int u) {
	s.push(u);
	Num[u] = Low[u] = ++Time;
	for(auto v : g[u]) {
		if(Num[v]) {
			minimize(Low[u], Num[v]);
		} else {
			dfs(v);
			minimize(Low[u], Low[v]);
		}
	}

	if(Num[u] == Low[u]) {
		int v;
		++cntComp;
		do {
			v = s.top();
			s.pop();
			id[v] = cntComp;
			Num[v] = Low[v] = INF;
		} while(v != u);
	}
}

struct Dinitz {
	struct Edges {
		int u, v;
		ll cap;

		Edges() : u(), v(), cap() {}
		Edges(int _u, int _v, ll _cap) : u(_u), v(_v), cap(_cap) {}
	};

	vector<vector<int>> g;
	vector<Edges> ed;
	vector<int> dist;
	vector<int> id;
	int S, T;
	int n;

	Dinitz() : ed(), n(), S(), T() {}
	Dinitz(int _n, int _S, int _T) {
		n = _n; S = _S; T = _T;
		g.resize(n);
		dist.resize(n);
		id.resize(n);
		for(int i = 0; i < n; i++) g[i].clear();
		ed = vector<Edges>();
	}

	void addEdge(int u, int v, ll cap) {
		g[u].pb((int)ed.size());
		ed.pb(Edges(u, v, cap));
		g[v].pb((int)ed.size());
		ed.pb(Edges(v, u, 0));
	}

	bool bfs() {
		for(int i = 0; i < n; i++) dist[i] = n + 5;
		queue<int> q;
		q.push(S); dist[S] = 0;
		while(!q.empty()) {
			int u = q.front(); q.pop();
			for(int i : g[u]) {
				Edges e = ed[i];
				if(!e.cap) continue;
				if(dist[e.v] <= dist[u] + 1) continue;
				dist[e.v] = dist[u] + 1;
				q.push(e.v);
			}
		}

		return dist[T] < n + 5;
	}

	ll dfs(int u, ll flow) {
		if(u == T || flow == 0) return flow;

		ll ans = 0;
		for(int &i = id[u]; i < (int)g[u].size(); i++) {
			Edges e = ed[g[u][i]];
			if(!e.cap) continue;
			if(dist[e.v] != dist[u] + 1) continue;
			ll f = dfs(e.v, min(flow, e.cap));
			flow -= f;
			ans += f;
			ed[g[u][i]].cap -= f;
			ed[g[u][i] ^ 1].cap += f;
			if(flow == 0) return ans;
		}

		return ans;
	}

	ll Flow() {
		ll ans = 0;
		while(bfs()) {
			for(int i = 0; i < n; i++) id[i] = 0;
			ans += dfs(S, INF * INF);
		}

		return ans;
	}
};

void BaoJiaoPisu() {
	int n, m, t; cin >> n >> m >> t;
	for(int i = 1; i <= t; i++) {
		int x; cin >> x; treasure[x] = true;
	}		

	for(int i = 1; i <= m; i++) {
		int u, v; cin >> u >> v;
		g[u].pb(v);
	}

	for(int i = 1; i <= n; i++) {
		if(!Num[i]) {
			dfs(i);
		}
	}

	for(int u = 1; u <= n; u++) {
		if(treasure[u]) {
			f[id[u]] = true;
		}
		for(auto v : g[u]) {
			if(id[v] != id[u]) {
				adj[id[u]].pb(id[v]);
				outEdge[id[u]] = true;
				inEdge[id[v]] = true;
			}
		}
	}

	n = cntComp;
	int S = 2 * n + 2, T = 2 * n + 5;
	int l = 0, r = n, ans = 0;
	while(l <= r) {
		int mid = (l + r) >> 1;
		int _S = 2 * n + 7;
		int _T = 2 * n + 9;
		Dinitz G = Dinitz(2 * n + 10, _S, _T);
		for(int i = 1; i <= n; i++) {
			if(!inEdge[i]) G.addEdge(S + 1, i, INF);
			if(!outEdge[i]) G.addEdge(i + n, T, INF);
			for(auto v : adj[i]) G.addEdge(i + n, v, INF);
		}
		int cnt = 0;
		G.addEdge(S, S + 1, mid);
		G.addEdge(T, S, INF);
		for(int i = 1; i <= n; i++) {
			G.addEdge(i, i + n, INF);
			if(f[i]) {
				G.addEdge(_S, i + n, 1);
				G.addEdge(i, _T, 1);
				++cnt;
			}
		}

		if(G.Flow() == cnt) {
			ans = mid - 1;
			r = mid - 1;
		} else l = mid + 1;
	}

	cout << ans;
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
