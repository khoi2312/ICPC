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

vector<int> left[N], right[N];
int cnt_left[N], cnt_right[N];
int a[N], b[N];
map<pii, int> have;

void BaoJiaoPisu() {
	int n, m; cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i];
		if(a[i] == -1 && b[i] == -1) continue;
		if(a[i] == -1) {
			right[b[i]].pb(i);
			++cnt_right[b[i]];
		} else {
			left[a[i]].pb(i);
			++cnt_left[a[i]];
		}
	}	

	set<pii> l, r;
	for(int i = 1; i <= m; i++) {
		l.ins({cnt_left[i], i});
		r.ins({cnt_right[i], i});
	}

	while(l.size() || r.size()) {
		if(r.empty() || (l.size() && (*l.rbegin()).fi) > (*r.rbegin()).fi) {
			auto iter = l.end(); iter--;
			pii curr = (*iter);
			l.erase(iter);
			vector<pii> new_r;
			if(r.size() < curr.fi) {
				cout << "NO";
				return;
			}
			
			while(curr.fi) {
				auto iter = r.begin();
				pii edge = (*iter);
				r.erase(iter);
				new_r.pb(edge);
				--curr.fi;
				int pos = left[curr.se].back(); left[curr.se].pop_back();
				b[pos] = edge.se;
			}

			while(r.size()) {
				auto iter = r.end(); iter--;
				pii edge = (*iter);
				if(edge.fi == 0) break;
				r.erase(iter);
				edge.fi--;
				new_r.pb(edge);
				int pos = right[edge.se].back(); right[edge.se].pop_back();
				a[pos] = curr.se;
			}

			for(auto x : new_r) r.ins(x);
		}  else {
			auto iter = r.end(); iter--;
			pii curr = (*iter);
			r.erase(iter);
			vector<pii> new_l;
			if(l.size() < curr.fi) {
				cout << "NO";
				return;
			}
			
			while(curr.fi) {
				auto iter = l.begin();
				pii edge = (*iter);
				l.erase(iter);
				new_l.pb(edge);
				--curr.fi;
				int pos = right[curr.se].back(); right[curr.se].pop_back();
				a[pos] = edge.se;
			}

			while(l.size()) {
				auto iter = l.end(); iter--;
				pii edge = (*iter);
				if(edge.fi == 0) break;
				l.erase(iter);
				edge.fi--;
				new_l.pb(edge);
				int pos = left[edge.se].back(); left[edge.se].pop_back();
				b[pos] = curr.se;
			}

			for(auto x : new_l) l.ins(x);
		}
	}	

	for(int i = 1; i <= n; i++) {
		if(a[i] >= 1) have[{a[i], b[i]}] = 1;
	}

	pii curr = {1, 1};
	for(int i = 1; i <= n; i++) {
		if(a[i] == -1) {
			while(have[curr]) {
				curr.fi++;
				if(curr.fi > m) {
					curr.fi = 1;
					curr.se++;
				}
			}
			a[i] = curr.fi;
			b[i] = curr.se;
			have[curr] = 1;
		}
	}

	cout << "YES" << '\n';
	for(int i = 1; i <= n; i++) {
		cout << a[i] << " " << b[i] << '\n';
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
        BaoJiaoPisu();
    }
}
