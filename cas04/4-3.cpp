#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 10;

vector<pair<int, int>> g[N];
int bottleneck;
bool mark[N];

void dfs(int v) {
    mark[v] = 1;
    for (const auto &pxt : g[v]) {
        if (pxt.second >= bottleneck && !mark[pxt.first]) {
            dfs(pxt.first);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int i = 0, a, b, w; i < m; i++) {
        cin >> a >> b >> w;
        g[a].push_back({b, w});
        g[b].push_back({a, w});
    }
    cin >> bottleneck;

    int sol = -1;
    for (int i = 1; i <= n; i++) {
        if (!mark[i]) {
            dfs(i);
            sol++;
        }
    }
    cout << sol << endl;

    return 0;
}