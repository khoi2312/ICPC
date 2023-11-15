#include <bits/stdc++.h>
using namespace std;

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];    
    
    sort(a.begin(), a.end());
    int minTest = 0;
    for (int i = 0; i < k; i++)
        if (a[i] > 1) minTest += a[i];
    
    reverse(a.begin(), a.end());
    int maxTest = 0;
    for (int i = 0; i < k; i++)
        if (a[i] > 1) maxTest += a[i];
    
    cout << minTest << ' ' << maxTest << '\n';
    return 0;
}