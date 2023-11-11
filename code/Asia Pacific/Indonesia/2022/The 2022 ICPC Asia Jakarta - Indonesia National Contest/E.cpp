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
ll minans = 1e18;
ll maxans = -1e18;
struct Node {
        ll size;
        ll child[2];
        Node() {
            size = 0;
            child[0] = child[1] = 0;
        }
    };
struct Trie {
     vector<Node> node;
    Trie() {
     node.push_back(Node());
     node.push_back(Node());
    }
    void insert(ll val) {
    
        ll root = 1;
        for (ll i = 30; i >= 0; i--) {
            ll bit = (val >> i)&1;
            if (node[root].child[bit] == 0) {
               ll k = sz(node);
               node.push_back(Node());
               node[root].child[bit] = k;
            }
            root = node[root].child[bit];
         
        }
    }
    long long queryMax(ll val) {
        ll root = 1;
        long long res = 0;
        for (ll i = 30; i >= 0; i--) {
            ll bit = (val >> i)&1;
           
            if (node[root].child[bit^1] == 0) {
                root = node[root].child[bit];
            }
            else {
                res += (1ll << i);
                root = node[root].child[bit^1];
            }
        }
        //cout << "GET1 : " << res << '\n';
        return res;
    }
    long long queryMin(ll val) {
        ll root = 1;
        long long res = 0;
        for (ll i = 30; i >= 0; i--) {
            ll bit = (val >> i)&1;
            bit = 1 - bit;
           
            if (node[root].child[bit^1] == 0) {
                res += (1ll << i);
                root = node[root].child[bit];
            }
            else {
                
                root = node[root].child[bit^1];
            }
        }
       // cout << "GET2 : " << res << '\n';
      
        return res;
    }
};


vector<pll> adj[200005];
ll a[200005];


void dfs0(ll u, ll par) {

  for (auto v : adj[u]) {
    if (v.fi == par) continue;
    a[v.fi] = a[u] ^ v.se;
    dfs0(v.fi,u);
  
  }
}


int main() {  
  ios_base::sync_with_stdio(false);  cin.tie(NULL);
  ll n; cin >> n;
  for (int i = 1 ; i <= n-1 ; i++) {
    ll x , y ; cin >> x >> y;
    ll w; cin >> w;
    adj[x].pb({y,w});
    adj[y].pb({x,w});




  }
 
  Trie tr;
  
  a[1] = 0;
  dfs0(1,-1);
  
  for (int i = 1 ; i <= n ; i++) {
    minans =min(minans,tr.queryMin(a[i]));
    maxans =max(maxans,tr.queryMax(a[i]));
    tr.insert(a[i]);
  }

  cout << minans << ' ' << maxans << endl;

  
  
}

