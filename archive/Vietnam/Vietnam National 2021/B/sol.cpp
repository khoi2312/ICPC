#include <bits/stdc++.h>
using namespace std;

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int r, c;
    cin >> r >> c;

    vector<string> a(r);
    for (auto &x: a) cin >> x;

    int ans = 0;
    vector<char> group;
    auto add_char = [&] (int x, int y) {
        if (a[x][y] == '#') return;
        group.push_back(a[x][y]);
        a[x][y] = '#';
    };

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (a[i][j] == '#') continue;
            add_char(i, j);
            add_char(r - 1 - i, j);
            add_char(i, c - 1 - j);
            add_char(r - 1 - i, c - 1 - j);
            int min_step = 26 * 4;
            for (char c = 'A'; c <= 'Z'; c++) {
                int w = 0;
                for (char item: group) w += min(abs(item - c), 26 - abs(item - c));
                min_step = min(min_step, w);
            }
            ans += min_step;
            group.clear();
        }
    }

    cout << ans << '\n';


    return 0;
}