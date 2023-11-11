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


int main() {  
    ios_base::sync_with_stdio(false);  cin.tie(NULL);
    ll n ; cin >> n;
    ll p ; cin >> p;
    ll curmin = p ; ll curmax = p;  

    // 50 -1000
    // for (int i = 1 ; i <= 50 ; i++) {
    //   cout << "x 2 x 2 \n" ;
    // }

  
    for (int i = 1 ; i <=  n ; i++) {
      char c ; cin >> c;
      ll val ;cin >> val;


      char c2; cin >> c2;
      ll val2 ;cin >> val2;

     // cout << val << ' ' << val2 << '\n';


      ll ncurmax = -8e18;
      ll ncurmin = 8e18;
      if (c == '+') {
        ncurmax = max(ncurmax,curmin + val);
        ncurmax = max(ncurmax,curmax + val);

        ncurmin = min(ncurmin,curmin + val);
        ncurmin = min(ncurmin,curmax + val);
      }
      else {
        ncurmax = max(ncurmax,curmin * val);
        ncurmax = max(ncurmax,curmax * val);

        ncurmin = min(ncurmin,curmin * val);
        ncurmin = min(ncurmin,curmax * val);

      }
      if (c2 == '+') {
        ncurmax = max(ncurmax,curmin + val2);
        ncurmax = max(ncurmax,curmax + val2);

        ncurmin = min(ncurmin,curmin + val2);
        ncurmin = min(ncurmin,curmax + val2);
      }
      else {
        ncurmax = max(ncurmax,curmin * val2);
        ncurmax = max(ncurmax,curmax * val2);

        ncurmin = min(ncurmin,curmin * val2);
        ncurmin = min(ncurmin,curmax * val2);

      }


      if (ncurmax < ncurmin) swap(ncurmax,ncurmin);

      curmax = ncurmax;
      curmin = ncurmin;
     // cout << curmin << ' ' << curmax << '\n';
    }

    cout << max(curmax,curmin);
    
}
