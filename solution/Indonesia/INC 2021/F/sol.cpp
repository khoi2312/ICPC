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

bool isPal(string s) {
  ll n = sz(s);
  ffor(i,n) if (s[i] != s[n-1-i]) return false;
  return true;
}
int main() {  
  ios_base::sync_with_stdio(false);  cin.tie(NULL);
  string s ; cin >> s;
  ll n = sz(s);

  string cur1 = "";
  string cur2 = s;

  reverse(all(cur2));
  for (int i = 0 ; i+1 < n ; i++) {
   
      cur1+= s[i];
      cur2.pop_back();
      if (isPal(cur1) && isPal(cur2)) {
        cout << cur1 << ' ' << cur2 << endl;
        return 0;
      }
  }
  cout << "NO" << endl;

  
}
