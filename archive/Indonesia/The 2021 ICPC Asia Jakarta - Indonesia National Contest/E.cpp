
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

const int MAXN = 131075;
int mark[18];
vector<pair<int,ll>> adj[100005];
ll dist[18][100005];
ll mingroup[MAXN];
ll pre[MAXN][18];
ll ans[MAXN];
ll fromroot[MAXN][18];
ll minfromroot[MAXN];
vector<int> sub[MAXN];
ll full ;
ll n,m,k,s;
void dijkstra(int id) {
    for (int i = 1 ; i <= n ; i++) dist[id][i] = 1e18;
    dist[id][mark[id]] = 0;
    priority_queue<pair<ll,int>> pq;
    pq.push({0LL,mark[id]});
    while (!pq.empty()) {
      auto cur = pq.top(); pq.pop();
      ll d = -cur.fi;
      int u = cur.se;
      if (dist[id][u] != d) continue;
      for (auto v : adj[u]) {
         ll nd = d + v.se;
         if (dist[id][v.fi] > nd) {
            dist[id][v.fi] = nd;
            pq.push({-nd,v.fi});
         }
      }
    }
}
int main() {  
  ios_base::sync_with_stdio(false);  cin.tie(NULL);
  cin >> n >> m >> k >> s;
  for (int i = 0 ; i < 18 ; i++) {
    for (int j = 1 ; j <= n ; j++) {
         dist[i][j] = 1e18;
    }
  }
  for (int i = 1 ; i <= m ; i++) {
    int x, y ; ll w;  
    cin >> x >> y >> w;
    adj[x].pb({y,w});
    adj[y].pb({x,w});
  }
  for (int i = 0 ; i < k ; i++) {
    cin >> mark[i];
  }
  mark[k] = 1;
  for (int i = 0 ; i <= k ; i++) {
    dijkstra(i);
  }
  //rep(i,5) cout << dist[k][i] << ' ' ; cout << '\n';
  full = (1LL << k);
  for (int i = 0 ; i <= full; i++) {
    mingroup[i] = 1e18;
    for (int j = 0 ; j < 18 ; j++ )
      pre[i][j] = 1e18;
  }
  for (int i = 0 ; i <= k ; i++) {
      pre[1LL << i][i] = 0;
  }
  for (ll mask = 0 ; mask < full ; mask++) {
    for (ll last = 0 ; last <= k ; last++) {
       if (pre[mask][last] >= 1e18) continue;
       for (ll i = 0 ; i <= k ; i++) {
        if ((mask>>i)&1) continue;
        pre[mask + (1LL<<i)][i] = min(pre[mask + (1LL<<i)][i],pre[mask][last] + dist[last][mark[i]]);
      }
    }
  }
  for (int i = 0 ; i <= full; i++) {
    for (int j = 0 ; j < 18 ; j++ )
      mingroup[i] = min(mingroup[i],pre[i][j]);
  }
  for (ll mask = 0 ; mask < full ; mask++) {
     for(ll submask = mask; submask; submask = (submask - 1) & mask) {
         sub[mask].pb(submask);
     }
  }
  ll full2 = (1LL << (k+1));
  for (int i = 0 ; i <= full2; i++) {
    minfromroot[i] = 1e18;
    for (int j = 0 ; j < 18 ; j++ )
      fromroot[i][j] = 1e18;
  }
  fromroot[1LL<< k][k] = 0;
  for (ll mask = 0 ; mask < full2 ; mask++) {
    for (ll last = 0 ; last <= k ; last++) {
       if (fromroot[mask][last] >= 1e18) continue;
       for (ll i = 0 ; i <= k ; i++) {
        if ((mask>>i)&1) continue;
        fromroot[mask + (1LL<<i)][i] = min(fromroot[mask + (1LL<<i)][i],fromroot[mask][last] + dist[last][mark[i]]);
      }
    }
  }
  for (int i = 0 ; i <= full2; i++) {
    for (int j = 0 ; j < 18 ; j++ )
      minfromroot[i] = min(minfromroot[i],fromroot[i][j]);
  }

  for(int i = 0 ; i <= full ; i++) ans[i] = -1;
  for (int mask = 0 ; mask < full ; mask++) {
    ll cur = 1e18;
    if (mask == full-1) {
      // iterate first group
      for (auto x : sub[mask]) {
        if (mask - x < 0) while(true) {};
        if (x == mask) continue;
        // first vertex = 1;
        //same group 1
        cur = min(cur,minfromroot[x+(1LL<<k)] + max(0LL,s-minfromroot[x+(1LL<<k)]) + ans[mask-x]);
        //1 tele 
        cur = min(cur,s + mingroup[x] + max(0LL,s-mingroup[x]) + ans[mask-x]);
      }
      //only group
      cur = min(cur,minfromroot[mask + (1LL<<k)] + max(0LL,s-minfromroot[mask + (1LL<<k)])); // 1 same gr, tele 1

      cur = min(cur,s+mingroup[mask] + max(0LL,s-mingroup[mask]));                           // 1 tele   , tele 1

      cur = min(cur,s+minfromroot[mask+(1LL<<k)]);                                           // 1 tele   , same gr 1
      // 1 same gr, same gr 1
      // no tele case
    }
    else {
      //de quy
      for (auto x : sub[mask]) {
        if (mask - x < 0) while(true) {};
        if (x == mask) continue;
        cur = min(cur,mingroup[x] + max(0LL,s-mingroup[x]) + ans[mask-x]);
      }
      //is last 
      //tele to 1
      cur = min(cur,mingroup[mask] + max(0LL,s-mingroup[mask]));
      // last vertex = 1;
      cur = min(cur,minfromroot[mask+(1LL<<k)]); 
    }
    ans[mask] = cur;
  }
  ll res =  ans[full-1];
  //no tele
  for (int j = 0 ; j < 18 ; j++ )
  res = min(res,fromroot[full2-1][j] + dist[j][1]);
  //
  cout << res << endl;
}
