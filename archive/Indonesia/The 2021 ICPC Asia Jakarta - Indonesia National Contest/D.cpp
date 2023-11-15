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

struct Node {
	Node *left, *right;
	int maxVal, minVal, maxValB;
	int maxValA, minValB, minValA;

	Node() {
		left = right = nullptr;
		maxVal = maxValA = maxValB = -INF;
		minVal = minValA = minValB = INF;
	};

	Node(Node* p) {
		left = p->left;
		right = p->right;
		maxVal = p->maxVal;
		minVal = p->minVal;
		maxValA = p -> maxValA;
		minValA = p -> minValA;
		minValB = p -> minValB;
		maxValB = p -> maxValB;
	}
};

void build(int l, int r, Node* curr) {
	if(l == r) return;
	int mid = (l + r) >> 1;
	curr->left = new Node();
	curr->right = new Node();
	build(l, mid, curr->left);
	build(mid + 1, r, curr->right);
}

void update(int l, int r, int pos, int x, int maxA, int minA, Node *root) {
	Node *curr = root;
	while(l <= r) {
		int mid = (l + r) >> 1;
		maximize(curr->maxVal, x);
		minimize(curr->minVal, x);
		maximize(curr->maxValA, maxA);
		minimize(curr->minValB, maxA);
		minimize(curr->minValA, minA);
		maximize(curr->maxValB, minA);
		if(l == r) return;

		if(pos <= mid) {
			r = mid;
			curr->left = new Node(curr->left);
			curr = curr->left;
		} else {
			l = mid + 1;
			curr->right = new Node(curr->right);
			curr = curr->right;
		}
	}
}

int getMax(int l, int r, int lo, int hi, Node *node) {
	if(l > hi || r < lo) return -INF;
	if(lo <= l && r <= hi) return node->maxVal;
	int mid = (l + r) >> 1;

	int left = getMax(l, mid, lo, hi, node->left);
	int right = getMax(mid + 1, r, lo, hi, node->right);
	return max(left, right);
}

int getMaxA(int l, int r, int lo, int hi, Node *node) {
	if(l > hi || r < lo) return -INF;
	if(lo <= l && r <= hi) return node->maxValA;
	int mid = (l + r) >> 1;

	int left = getMaxA(l, mid, lo, hi, node->left);
	int right = getMaxA(mid + 1, r, lo, hi, node->right);
	return max(left, right);
}

int getMaxB(int l, int r, int lo, int hi, Node *node) {
	if(l > hi || r < lo) return -INF;
	if(lo <= l && r <= hi) return node->maxValB;
	int mid = (l + r) >> 1;

	int left = getMaxB(l, mid, lo, hi, node->left);
	int right = getMaxB(mid + 1, r, lo, hi, node->right);
	return max(left, right);
}

int getMin(int l, int r, int lo, int hi, Node *node) {
	if(l > hi || r < lo) return INF;
	if(lo <= l && r <= hi) return node->minVal;
	int mid = (l + r) >> 1;

	int left = getMin(l, mid, lo, hi, node->left);
	int right = getMin(mid + 1, r, lo, hi, node->right);
	return min(left, right);
}

int getMinA(int l, int r, int lo, int hi, Node *node) {
	if(l > hi || r < lo) return INF;
	if(lo <= l && r <= hi) return node->minValA;
	int mid = (l + r) >> 1;

	int left = getMinA(l, mid, lo, hi, node->left);
	int right = getMinA(mid + 1, r, lo, hi, node->right);
	return min(left, right);
}

int getMinB(int l, int r, int lo, int hi, Node *node) {
	if(l > hi || r < lo) return INF;
	if(lo <= l && r <= hi) return node->minValB;
	int mid = (l + r) >> 1;

	int left = getMinB(l, mid, lo, hi, node->left);
	int right = getMinB(mid + 1, r, lo, hi, node->right);
	return min(left, right);
}

struct P {
	int a, b, id;
} person[N];
int pos[N];
vector<int> position[N];
Node *pref[N];
Node *suff[N];
pii query[N];
int res[N];

void BaoJiaoPisu() {
	int n, q; cin >> n >> q;
	for(int i = 1; i <= n; i++) cin >> person[i].a;
	for(int i = 1; i <= n; i++) {
		cin >> person[i].b;
		person[i].id = i;
	}

	sort(person + 1, person + 1 + n, [&](P a, P b) {
		return a.a < b.a;
	});

	for(int i = 1; i <= n; i++) {
		pos[person[i].id] = i;
	}

	vector<int> val;
	for(int i = 1; i <= n; i++) val.pb(person[i].b);
	sort(all(val)); val.resize(unique(all(val)) - val.begin());
	
	for(int i = 1; i <= n; i++) {
		person[i].b = lower_bound(all(val), person[i].b) - val.begin() + 1;
		position[person[i].b].pb(i);
	}

	pref[0] = new Node();
	build(1, n, pref[0]);

	for(int i = 1; i <= n; i++) {
		pref[i] = new Node(pref[i - 1]);
		for(auto x : position[i]) {
			update(1, n, x, val[i - 1], val[i - 1] + person[x].a, val[i - 1] - person[x].a, pref[i]);
		}
	}

	suff[n + 1] = new Node();
	build(1, n, suff[n + 1]);

	for(int i = n; i >= 1; i--) {
		suff[i] = new Node(suff[i + 1]);
		for(auto x : position[i]) {
			update(1, n, x, val[i - 1], val[i - 1] + person[x].a, val[i - 1] - person[x].a, suff[i]);
		}
	}

	for(int i = 1; i <= q; i++) {	
		int ans = INF;
		int u, v; cin >> u >> v;
		query[i] = {u, v};
		u = pos[u];
		v = pos[v];
		if(u > v) swap(u, v);

		if(u + 1 < v) {
			int b_min = min(person[u].b, person[v].b);
			int b_max = max(person[u].b, person[v].b);
			int x = getMax(1, n, u + 1, v - 1, pref[b_min]);
			if(x > -INF) minimize(ans, person[v].a - person[u].a + val[b_max - 1] - x);
			x = getMax(1, n, u + 1, v - 1, pref[b_max]);
			if(x >= val[b_min - 1]) minimize(ans, person[v].a - person[u].a + val[b_max - 1] - val[b_min - 1]);
			x = getMin(1, n, u + 1, v - 1, suff[b_max]);
			if(x >= val[b_max - 1] && x < INF) minimize(ans, person[v].a - person[u].a + x - val[b_min - 1]);
		}

		if(u > 1) {
			int b_min = min(person[u].b, person[v].b);
			int b_max = max(person[u].b, person[v].b);
			int x = getMaxA(1, n, 1, u - 1, pref[b_min]);
			if(x > -INF) minimize(ans, person[v].a + val[b_max - 1] - x);
			x = getMinA(1, n, 1, u - 1, suff[b_max]);
			if(x < INF) minimize(ans, x + person[v].a - val[b_min - 1]);
		}

		if(v < n) {
			int b_min = min(person[u].b, person[v].b);
			int b_max = max(person[u].b, person[v].b);
			int x = getMinB(1, n, v + 1, n, suff[b_max]);
			if(x < INF) minimize(ans, x - person[u].a - val[b_min - 1]);
			x = getMaxB(1, n, v + 1, n, pref[b_min]);
			if(x > -INF) minimize(ans, -x - person[u].a + val[b_max - 1]);
		}

		res[i] = ans;
	}

	{
		for(int i = 1; i <= n; i++) {
			swap(person[i].a, person[i].b);
			person[i].a = val[person[i].a - 1];	
		}

		sort(person + 1, person + 1 + n, [&](P a, P b) {
			return a.a < b.a;
		});

		for(int i = 1; i <= n; i++) {
			pos[person[i].id] = i;
		}

		for(int i = 1; i <= n; i++) position[i].clear();
		vector<int> val;
		for(int i = 1; i <= n; i++) val.pb(person[i].b);
		sort(all(val)); val.resize(unique(all(val)) - val.begin());
		
		for(int i = 1; i <= n; i++) {
			person[i].b = lower_bound(all(val), person[i].b) - val.begin() + 1;
			position[person[i].b].pb(i);
		}

		pref[0] = new Node();
		build(1, n, pref[0]);

		for(int i = 1; i <= n; i++) {
			pref[i] = new Node(pref[i - 1]);
			for(auto x : position[i]) {
				update(1, n, x, val[i - 1], val[i - 1] + person[x].a, val[i - 1] - person[x].a, pref[i]);
			}
		}

		suff[n + 1] = new Node();
		build(1, n, suff[n + 1]);

		for(int i = n; i >= 1; i--) {
			suff[i] = new Node(suff[i + 1]);
			for(auto x : position[i]) {
				update(1, n, x, val[i - 1], val[i - 1] + person[x].a, val[i - 1] - person[x].a, suff[i]);
			}
		}

		for(int i = 1; i <= q; i++) {	
			int ans = INF;
			int u = query[i].fi;
			int v = query[i].se;
			u = pos[u];
			v = pos[v];
			if(u > v) swap(u, v);

			if(u + 1 < v) {
				int b_min = min(person[u].b, person[v].b);
				int b_max = max(person[u].b, person[v].b);
				int x = getMax(1, n, u + 1, v - 1, pref[b_min]);
				if(x > -INF) minimize(ans, person[v].a - person[u].a + val[b_max - 1] - x);
				x = getMax(1, n, u + 1, v - 1, pref[b_max]);
				if(x >= val[b_min - 1]) minimize(ans, person[v].a - person[u].a + val[b_max - 1] - val[b_min - 1]);
				x = getMin(1, n, u + 1, v - 1, suff[b_max]);
				if(x >= val[b_max - 1] && x < INF) minimize(ans, person[v].a - person[u].a + x - val[b_min - 1]);
			}

			minimize(res[i], ans);
		}
	}

	for(int i = 1; i <= q; i++) {
		cout << res[i] << '\n';
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
