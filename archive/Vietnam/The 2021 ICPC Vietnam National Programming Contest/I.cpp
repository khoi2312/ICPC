#include <bits/stdc++.h>
using namespace std;

#define int long long
#define FOR(i, l, r) for (int i = l; i <= r; i++)
#define FORD(i, l, r) for (int i = l; i >= r; i--)
const int M = 16;
int f[M][M][M][M][M];

int32_t main () {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    f[0][0][0][0][0] = 1;

    while (n--) {
        int t;
        cin >> t;
        bool dp, graph, mathgeo, ds, adhoc;
        dp = graph = mathgeo = ds = adhoc = false;
        while (t--) {
            string s; cin >> s;
            dp |= s == "dp"; 
            graph |= s == "graph"; 
            mathgeo |= s == "mathgeo"; 
            ds |= s == "ds"; 
            adhoc |= s == "adhoc";
        }

        FORD(i1, 15, dp) FORD(i2, 15, graph) FORD(i3, 15, mathgeo) FORD (i4, 15, ds) FORD (i5, 15, adhoc) 
            f[i1][i2][i3][i4][i5] += f[i1 - dp][i2 - graph][i3 - mathgeo][i4 - ds][i5 - adhoc]; 
             
    }

    int l1, r1, l2, r2, l3, r3, l4, r4, l5, r5;
    cin >> l1 >> r1 >> l2 >> r2 >> l3 >> r3 >> l4 >> r4 >> l5 >> r5;
    int ans = 0;
    FOR(i1, l1, r1) FOR(i2, l2, r2) FOR(i3, l3, r3) FOR(i4, l4, r4) FOR(i5, l5, r5)
        if (i1 || i2 || i3 || i4 || i5)
            ans += f[i1][i2][i3][i4][i5];

    cout << ans << '\n';
    return 0;
}