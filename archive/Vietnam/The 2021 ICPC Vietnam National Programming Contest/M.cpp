#include <bits/stdc++.h>
using namespace std;

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    cout << n + 1 << '\n';
    vector<vector<int>> a(n + 1);
    int cur = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            a[j].push_back(++cur);
            a[i].push_back(cur);
        }
    }
    for (auto i: a) {
        for (auto j: i) 
            cout << j << ' ';
        cout << '\n';
    }


    return 0;
}