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
const int N = 2e5 + 10;

template <class T> struct FenwickTree {
	int n;
	vector<T> bit;

	FenwickTree(int _n = 0) {
		n = _n;
		bit.resize(n + 5);
		for(int i = 1; i <= n; i++) bit[i] = 0;
	}

	void update(int pos, T x) {
		for(int i = pos; i <= n; i += i & (-i)) bit[i] += x;
	}

	T get(int pos) {
		T ans = 0;
		for(int i = pos; i > 0; i -= i & (-i)) ans += bit[i];
		return ans;
	}
};
FenwickTree<ll> BIT[N];
vector<int> pos[N];
int c[N];

void solve() {
    int n, q; cin >> n >> q;
    for(int i = 1; i <= n; i++) {
        cin >> c[i];
        pos[c[i]].pb(i);
    }

    for(int i = 1; i <= n; i++) {
        BIT[i] = FenwickTree<ll>(pos[i].size());
        for(int j = 0; j < pos[i].size(); j++) {
            BIT[i].update(j + 1, 1ll * pos[i][j] * pos[i][j]);
        }
    }

    ll last = 0;
    while(q--) {
        int t; cin >> t;
        if(t == 1) {
            ll p; cin >> p;
            p = (p + last - 1) % (n - 1) + 1;
            int a = c[p];
            int b = c[p + 1];
            swap(c[p], c[p + 1]);
            if(a == b) continue;
            int pa = lower_bound(all(pos[a]), p) - pos[a].begin();
            int pb = lower_bound(all(pos[b]), p + 1) - pos[b].begin();
            assert(pos[a][pa] == p);
            assert(pos[b][pb] == p + 1);
            swap(pos[a][pa], pos[b][pb]);
            BIT[a].update(pa + 1, (1ll * (p + 1) * (p + 1)) - 1ll * p * p);
            BIT[b].update(pb + 1, 1ll * p * p - 1ll * (p + 1) * (p + 1));
        }

        if(t == 2) {
            ll l, r, x; cin >> l >> r >> x;
            l = (l + last - 1) % n + 1;
            r = (r + last - 1) % n + 1;
            x = (x + last - 1) % n + 1;
            if(l > r) swap(l, r);
            l = lower_bound(all(pos[x]), l) - pos[x].begin() + 1;
            r = upper_bound(all(pos[x]), r) - pos[x].begin();
            last = BIT[x].get(r) - BIT[x].get(l - 1);
            cout << last << '\n';
        }

        if(t == 3) {
            ll l, r, x; cin >> l >> r >> x;
            l = (l + last - 1) % n + 1;
            r = (r + last - 1) % n + 1;
            x = (x + last - 1) % n + 1;
            if(l > r) swap(l, r);
            last = BIT[x].get(r) - BIT[x].get(l - 1);
            cout << last << '\n';
        }
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
    while(tc--) {
        //ddd++;
        //cout << "Case #" << ddd << ": ";
        solve();
    }
}
