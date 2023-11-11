#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef long double ld;
typedef pair<ld,ld> pld;

#define fi first
#define se second
#define pb push_back
#define rep(i,n) for (int i=1;i <=int(n);i++)
#define ffor(i,n) for (int i=0;i <int(n);i++)  
#define sz(x) ((int) (x).size()) 
#define all(x) x.begin(),x.end()

ll a[200005];
ll d[200005];
int main() {  
    ios_base::sync_with_stdio(false);  cin.tie(NULL);
    ll n , p , x; cin >> n >> p >> x;
    rep(i,n) cin >> d[i];
    ll res = 1e18;


    a[0] = p;
    for (int i = 1 ; i < n ; i++) {
      a[i] = a[i-1] + d[i];
    } 

    ll s = 0;
    rep(i,n) s += d[i];
    s = -s;
    

    //ffor(i,n) cout << a[i] << ' ' ; cout << '\n';



    for (int i = 0 ; i < n ; i++){
        if (a[i] < x) continue;
        ll diff = a[i] - x;
        ll div = diff/s;
        res = min(res,a[i]-div*s);
    }





    if (res == 1e18) cout << -1 << endl; else cout << res << endl;
    
}
