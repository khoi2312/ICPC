#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n, k, p;
    while (cin >> n >> k >> p) {
        if (n == 0 && k == 0 && p == 0) break;

        vector<string> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        int cntRook = 0;
        for (auto s: a) 
            for (char c: s) 
                if (c == 'R') cntRook += 1;
        
        vector<bool> usedR(n), usedC(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (a[i][j] == 'R')
                    usedR[i] = usedC[j] = true;

        int cntR = 0, cntC = 0;
        for (int i = 0; i < n; i++) {
            if (usedR[i]) ++cntR;
            if (usedC[i]) ++cntC;
        }
        
        int curPair = 2 * cntRook - (cntR + cntC);

        int deltaPair = curPair + 2 * k - p;
        // cout << curPair << "nowPair\n";
        
        if (deltaPair < 0) {
            cout << "NO\n";
            continue;
        }

        bool found = false;

        for (int both = 0; 2 * both <= deltaPair && !found; both++) {
            // cout << both << "bug" << endl;
            if (both > min(n - cntR, n - cntC)) break;
            if (both == 0 && !cntRook && deltaPair > 0) continue;

            int curDelta = deltaPair - 2 * both;
            for (int rowDelta = 0; rowDelta <= curDelta; rowDelta++) {
                int colDelta = curDelta - rowDelta;
                // cout << rowDelta << " " << colDelta << "bug2" << endl;
                if (rowDelta + both > n - cntR) break;
                if (colDelta + both > n - cntC) continue;
                if (both + rowDelta + colDelta > k) continue;
                if (n * n - cntRook < k) continue;
                if ((cntR + both + rowDelta) * (cntC + both + colDelta) - cntRook < k) continue;

                int rr = -1, cc = -1;

                vector<int> empR, empC;
                for (int i = 0; i < n; i++)
                    if (!usedR[i]) empR.push_back(i); else rr = i;
                
                for (int i = 0; i < n; i++)
                    if (!usedC[i]) empC.push_back(i); else cc = i;

                for (int i = 0; i < both; i++) {
                    a[empR[i]][empC[i]] = 'R';
                    usedR[empR[i]] = true;
                    usedC[empC[i]] = true;
                    rr = empR[i];
                    cc = empC[i];
                }         

                for (int i = 0; i < rowDelta; i++) {
                    int j = both + i;
                    a[empR[j]][cc] = 'R';
                    usedR[empR[j]] = true;
                }

                for (int i = 0; i < colDelta; i++) {
                    int j = both + i;
                    a[rr][empC[j]] = 'R';
                    usedC[empC[j]] = true;
                }

                int finalRook = k - both - rowDelta - colDelta;
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (finalRook && a[i][j] == '.' && usedR[i] && usedC[j]) {
                            finalRook--;
                            a[i][j] = 'R';
                        } 
                    }
                }
                assert(finalRook == 0);

                found = true;
                break;
            }
        }

        if (found) {
            cout << "YES\n";
            for (auto s: a) cout << s << "\n";
        }
        else {
            cout << "NO\n";
        }
    }

    return 0;
}
