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
const int N = 1 + 10;
const int n = 9;

int ans[N][N];
int notFill[N][N][N];
vector<pii> jumps[N][N];

void fillBoard(int x, int y, int c) {
	for(auto [u, v] : jumps[x][y]) {
		notFill[u][v][c]++;
	}
}

void unfillBoard(int x, int y, int c) {
	for(auto [u, v] : jumps[x][y]) {
		notFill[u][v][c]--;
	}
}

void backtrack(int cnt) {
	if(cnt == 81) {
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				cout << ans[i][j];
			}
			cout << endl;
		}
		exit(0);
	}

	int x = 0, y = 0, p = -1;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if(!ans[i][j]) {
				int curr = 0;
				for(int c = 1; c <= 9; c++) curr += (notFill[i][j][c] > 0);
				if(maximize(p, curr)) x = i, y = j; 
			}
		}
	}

	for(int i = 1; i <= 9; i++) {
		if(notFill[x][y][i]) continue;
		ans[x][y] = i;

		fillBoard(x, y, i);
		backtrack(cnt + 1);
		unfillBoard(x, y, i);
		ans[x][y] = 0;
	}
}

void BaoJiaoPisu() {
	int cnt = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			char c; cin >> c;
			ans[i][j] = c - '0';
			cnt += (ans[i][j] > 0);
		}
	}

	for(int x = 1; x <= n; x++) {
		for(int y = 1; y <= n; y++) {
			for(int i = -2; i <= 2; i++) {
				for(int j = -2; j <= 2; j++) {
					if(max(abs(i), abs(j)) == 1 || i * i + j * j == 5) {
						int u = x + i;
						int v = y + j;
						if(u == x && v == y) continue;
						if(u > n || v > n || u < 1 || v < 1) continue;
						jumps[x][y].pb({u, v});
					}
				}
			}

			for(int i = 1; i <= n; i++) {
				if(i != x) jumps[x][y].pb({i, y});
				if(i != y) jumps[x][y].pb({x, i});
			}

			int cx = (x - 1) / 3;
			cx = cx * 3 + 1;
			int cy = (y - 1) / 3;
			cy = cy * 3 + 1;
			for(int u = cx; u <= cx + 2; u++) {
				for(int v = cy; v <= cy + 2; v++) {
					if(u != x || v != y) jumps[x][y].pb({u, v});
				}
			}

			sort(all(jumps[x][y]));
			jumps[x][y].resize(unique(all(jumps[x][y])) - jumps[x][y].begin());
		}
	}

	if(cnt == 0) {
		for(int i = 1; i <= 9; i++) ans[1][i] = i, fillBoard(1, i, i);
		backtrack(9);
		cout << "NO SOLUTION";
		return;
	}

	if(cnt == 1) {
		int x = 0, y = 0;
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				if(ans[i][j]) {
					x = i;
					y = j;
				}
			}
		}

		int iter = 1;
		for(int r = 1; r <= n; r++) {
			if(iter == ans[x][y]) ++iter;
			if(!ans[x][r]) {
				ans[x][r] = iter;
				++iter;
			}
			fillBoard(x, r, ans[x][r]);
		}

		backtrack(9);
		cout << "NO SOLUTION";
	}

	if(cnt == 2) {
		bool ok = false;
		int number = -1;
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				if(ans[i][j]) {
					if(notFill[i][j][ans[i][j]]) {
						cout << "NO SOLUTION";
						return;
					}
					if(number == -1) number = ans[i][j];
					else ok = (ans[i][j] == number);
					fillBoard(i, j, ans[i][j]);
				}
			}
		}

		int cnt = 2;
		if(ok) {
			int x = 0, y = 0;
			for(int i = 1; i <= n; i++) {
				for(int j = 1; j <= n; j++) {
					if(ans[i][j]) {
						x = i;
						y = j;
					}
				}
			}

			int iter = 1;
			for(int r = 1; r <= n; r++) {
				if(iter == ans[x][y]) ++iter;
				if(!ans[x][r]) {
					ans[x][r] = iter;
					++iter;
					fillBoard(x, r, ans[x][r]);
					cnt++;
				}
			}
		}
		backtrack(cnt);
		cout << "NO SOLUTION";
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
