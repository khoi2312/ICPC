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

const int MOD = 998244353; //998244353

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

template <typename T> T mod_inv_in_range(T a, T m) {
    // assert(0 <= a && a < m);
    T x = a, y = m;
    T vx = 1, vy = 0;
    while (x) {
        T k = y / x;
        y %= x;
        vy -= k * vx;
        std::swap(x, y);
        std::swap(vx, vy);
    }
    assert(y == 1);
    return vy < 0 ? m + vy : vy;
}
 
template <typename T> T mod_inv(T a, T m) {
    a %= m;
    a = a < 0 ? a + m : a;
    return mod_inv_in_range(a, m);
}
 
template <int MOD_> struct modnum {
    static constexpr int MOD = MOD_;
    static_assert(MOD_ > 0, "MOD must be positive");
 
    using ll = long long;
 
    int v;
 
public:
 
    modnum() : v(0) {}
    modnum(ll v_) : v(int(v_ % MOD)) { if (v < 0) v += MOD; }
    explicit operator int() const { return v; }
    friend std::ostream& operator << (std::ostream& out, const modnum& n) { return out << int(n); }
    friend std::istream& operator >> (std::istream& in, modnum& n) { ll v_; in >> v_; n = modnum(v_); return in; }
 
    friend bool operator == (const modnum& a, const modnum& b) { return a.v == b.v; }
    friend bool operator != (const modnum& a, const modnum& b) { return a.v != b.v; }
 
    modnum inv() const {
        modnum res;
        res.v = mod_inv_in_range(v, MOD);
        return res;
    }
    friend modnum inv(const modnum& m) { return m.inv(); }
    modnum neg() const {
        modnum res;
        res.v = v ? MOD-v : 0;
        return res;
    }
    friend modnum neg(const modnum& m) { return m.neg(); }
 
    modnum operator- () const {
        return neg();
    }
    modnum operator+ () const {
        return modnum(*this);
    }
 
    modnum& operator ++ () {
        v ++;
        if (v == MOD) v = 0;
        return *this;
    }
    modnum& operator -- () {
        if (v == 0) v = MOD;
        v --;
        return *this;
    }
    modnum& operator += (const modnum& o) {
        v -= MOD-o.v;
        v = (v < 0) ? v + MOD : v;
        return *this;
    }
    modnum& operator -= (const modnum& o) {
        v -= o.v;
        v = (v < 0) ? v + MOD : v;
        return *this;
    }
    modnum& operator *= (const modnum& o) {
        v = int(ll(v) * ll(o.v) % MOD);
        return *this;
    }
    modnum& operator /= (const modnum& o) {
        return *this *= o.inv();
    }
 
    friend modnum operator ++ (modnum& a, int) { modnum r = a; ++a; return r; }
    friend modnum operator -- (modnum& a, int) { modnum r = a; --a; return r; }
    friend modnum operator + (const modnum& a, const modnum& b) { return modnum(a) += b; }
    friend modnum operator - (const modnum& a, const modnum& b) { return modnum(a) -= b; }
    friend modnum operator * (const modnum& a, const modnum& b) { return modnum(a) *= b; }
    friend modnum operator / (const modnum& a, const modnum& b) { return modnum(a) /= b; }
};
using num = modnum<MOD>;

int l[N], r[N];
num dp[N];

void BaoJiaoPisu() {
	int n; cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> l[i] >> r[i];
	}

	auto intersect = [&](pii a, pii b) -> pii {
		pii ans;
		ans.fi = max(a.fi, b.fi);
		ans.se = min(a.se, b.se);
		return ans;
	};

	auto sum = [&](num a, num b) -> num {
		return (a + b) * (b - a + 1) / 2;
	};

	num inv6 = num(1) / num(6);
	auto sum_square = [&](num a) -> num {
		return a * (a + 1) * (2 * a + 1) * inv6;
	};

	auto sum2 = [&](num a, num b) -> num {
		return sum_square(b) - sum_square(a - 1);
	};

	num ans = 0;
	num ways = 1;
	for(int i = 1; i <= n; i++) ways *= (r[i] - l[i] + 1);
	for(int i = 1; i < n; i++) {
		pii curr = intersect({l[i], r[i]}, {l[i + 1], r[i + 1]});
		if(curr.fi > curr.se) continue;
		num coef = ways / (r[i] - l[i] + 1) / (r[i + 1] - l[i + 1] + 1) * sum(curr.fi, curr.se);
		dp[i] = coef;
		coef = coef / sum(curr.fi, curr.se) * sum2(curr.fi, curr.se);
		ans += coef;
	}

	for(int i = 1; i < n; i++) dp[i] += dp[i - 1];

	for(int i = 3; i < n; i++) {
		pii curr = intersect({l[i], r[i]}, {l[i + 1], r[i + 1]});
		if(curr.fi > curr.se) continue;
		ans += 2 * sum(curr.fi, curr.se) * dp[i - 2] / (r[i] - l[i] + 1) / (r[i + 1] - l[i + 1] + 1);
	}

	for(int i = 1; i + 1 < n; i++) {
		pii curr = intersect({l[i], r[i]}, {l[i + 1], r[i + 1]});
		curr = intersect(curr, {l[i + 2], r[i + 2]});
		if(curr.fi > curr.se) continue;
		ans += ways / (r[i] - l[i] + 1) / (r[i + 1] - l[i + 1] + 1) / (r[i + 2] - l[i + 2] + 1) * 2 * sum2(curr.fi, curr.se);
	}
	cout << ans / ways;
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
