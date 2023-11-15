#include <bits/stdc++.h>
using namespace std;

#define FOR(i, l, r) for (int i = l; i <= r; i++)
#define sz(x) (int)x.size()

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<int> c(n * n);
    FOR(i, 0, n * n - 1) {
        cin >> c[i]; 
        --c[i];
    }

    vector<vector<int>> idx(n + 1);
    FOR(i, 0, n * n - 1)
        idx[c[i]].push_back(i);

    vector<int> b(n * n);
    auto makeBox = [&] (int curBox) {
        int x = -1, y = -1;
        FOR(i, 0, n) {
            if (!sz(idx[i])) continue;
            if (x == -1 || sz(idx[i]) < sz(idx[x]))
                x = i;
            if (y == -1 || sz(idx[i]) >= sz(idx[y]))
                y = i;
        }
        
        auto minM = &idx[x], maxM = &idx[y];
        int m = minM->size();
        m = min(m, n);
        FOR(i, 1, m) {
            b[minM->back()] = curBox;
            minM->pop_back();
        }
        FOR(i, m + 1, n) {
            b[maxM->back()] = curBox;
            maxM->pop_back();
        }
    };

    FOR(i, 1, n) makeBox(i);
    cout << "YES\n";
    for (int i: b) cout << i << ' ';
    cout << '\n';
    return 0;
}
