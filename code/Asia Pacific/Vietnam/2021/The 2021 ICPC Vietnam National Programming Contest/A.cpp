#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<vector<int>> idx(n + 1);
    for (int i = 0; i < n * n; i++) {
        int x; cin >> x;
        --x; idx[x].push_back(i);
    }
    vector<int> ans(n * n);

    vector<int> color(n + 1);
    for (int i = 0; i <= n; i++) color[i] = i;

    int cntBox = 0;
    while (true) {
        sort(color.begin(), color.end(), [&] (int x, int y) {
            return idx[x].size() > idx[y].size();
        });
        while (!color.empty() && idx[color.back()].empty())
            color.pop_back();
        if (color.empty()) break;
        int x = color[0], y = color.back();
        ++cntBox;
        if (idx[y].size() >= n) {
            for (int i = 0; i < n; i++) {
                ans[idx[y].back()] = cntBox;
                idx[y].pop_back();
            }
        }
        else {
            for (int i: idx[y]) ans[i] = cntBox;
            for (int i = 0; i < n - idx[y].size(); i++) {
                ans[idx[x].back()] = cntBox;
                idx[x].pop_back();
            }
            idx[y].clear();
        }
    }

    cout << "YES\n";
    for (int i: ans) cout << i << ' ';
    cout << '\n';
    return 0;
}

