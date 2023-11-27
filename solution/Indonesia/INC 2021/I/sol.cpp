#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pii pair<int, int>
#define info pair<int, pii>

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<info>> adj(n);
    for (int i = 0; i < m; i++) {
        int x, y, p, t;
        cin >> x >> y >> p >> t;
        --x, --y;
        adj[x].push_back({t, {y, p}});
        adj[y].push_back({t, {x, p}});
    }
    vector<bool> vis(n);

    priority_queue<info, vector<info>, greater<info>> Q;
    Q.push({0, {0, 1}});
    while (!Q.empty()) {
        auto [T, _] = Q.top();
        auto [x, P] = _;
        Q.pop();

        vis[x] = true;
        if (x == n - 1) {
            cout << T << '\n';
            break;
        }

        for (auto [t, _]: adj[x]) {
            auto [y, p] = _;
            if (vis[y]) continue;
            if (y != n - 1)
                Q.push({T + t + abs(P - p), {y, p}});
            else
                Q.push({T + t + abs(P - p) + abs(p - 1), {y, p}});
        }
    }

    return 0;
}

