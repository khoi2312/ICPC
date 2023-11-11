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

struct TrieNode {
	TrieNode *child[26];
	int cnt = 0;

	TrieNode() {
		for(int i = 0; i < 26; i++) child[i] = nullptr;
		cnt = 0;
	}
};
TrieNode *root[500];
string s[N];

void addTrie(int p, int l) {
	TrieNode *current = root[l];
	for(int i = l - 1; i < s[p].size(); i++) {
		int x = s[p][i] - 'a';
		if(current->child[x] == nullptr) current->child[x] = new TrieNode();
		current = current->child[x];
		current->cnt++;
	}
};

int getTrie(int type, int pos, int l, int r) {
	TrieNode *current = root[l];
	int ans = 0;
	for(int i = l - 1; i < r; i++) {
		int x = s[pos][i] - 'a';
		if(!type) for(int j = 0; j < x; j++) {
			if(current->child[j] != nullptr) {
				ans += current->child[j]->cnt;
			}
		}
		if(current->child[x] == nullptr) return ans;
		current = current->child[x];
	}
	if(type) return current->cnt;
	return ans;
};

struct DataQuery {
	int a, b, l, r, x;
} query[N];

struct DataQTrie {
	int type, pos, l, r, coef, id;
};
vector<DataQTrie> queryTrie[N];
int ans[N];

vector<ll> H[2510];

void BaoJiaoPisu() {
	int n, m; cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> s[i];
	}

	int q; cin >> q;
	for(int i = 1; i <= q; i++) {
		cin >> query[i].a >> query[i].b >> query[i].l >> query[i].r >> query[i].x;
	}

	if(m <= 40) {
		for(int i = 1; i <= m; i++) root[i] = new TrieNode();
		for(int i = 1; i <= q; i++) {
			int a = query[i].a;
			int b = query[i].b;
			int l = query[i].l;
			int r = query[i].r;
			int x = query[i].x;
			queryTrie[a - 1].pb({0, a + x - 1, l, r, -1, i});
			queryTrie[a - 1].pb({1, a + x - 1, l, r, -1, i});
			queryTrie[a + x - 1].pb({1, a + x - 1, l, r, 1, i});
			queryTrie[b].pb({0, a + x - 1, l, r, 1, i});
		}

		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				addTrie(i, j);
			}

			for(int j = 0; j < queryTrie[i].size(); j++) {
				int x = queryTrie[i][j].type;
				int pos = queryTrie[i][j].pos;
				int l = queryTrie[i][j].l;
				int r = queryTrie[i][j].r;
				int coef = queryTrie[i][j].coef;
				int id = queryTrie[i][j].id;

				// cout << x << " " << pos << " " << l << " " << r << " " << coef << " " << id << " " << getTrie(x, pos, l, r) << endl;
				ans[id] += coef * getTrie(x, pos, l, r);
			}
		}

		for(int i = 1; i <= q; i++) {
			cout << ans[i] << '\n';
		}
		return;
	}

	for(int i = 1; i <= n; i++) H[i].resize(m + 5);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			H[i][j] = H[i][j - 1] * 31 + (s[i][j - 1] - 'a' + 1);
		}
	}

	vector<ll> pw(m + 5);
	pw[0] = 1;
	for(int i = 1; i <= m; i++) pw[i] = pw[i - 1] * 31;
	for(int i = 1; i <= q; i++) {
		int a = query[i].a;
		int b = query[i].b;
		int l = query[i].l;
		int r = query[i].r;
		int pos = query[i].x + a - 1;
		int ans = 0;
		for(int i = a; i <= b; i++) {
			int lo = l, hi = r, p = l - 1;
			while(lo <= hi) {
				int mid = (lo + hi) >> 1;
				ll x = H[i][mid] - H[i][l - 1] * pw[mid - l + 1];
				ll y = H[pos][mid] - H[pos][l - 1] * pw[mid - l + 1];
				if(x == y) {
					p = mid;
					lo = mid + 1;
				} else hi = mid - 1;
			}

			if(p == r) {
				ans += (i <= pos);
			} else {
				ans += (s[i][p] < s[pos][p]);
			}
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
