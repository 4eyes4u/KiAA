#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

vector<pair<int, int>> vx, edges;
int dsu[2 * N], k;

void init(int n) {
    for (int i = 1; i <= n; i++)
        dsu[i] = i;
}

int find(int x) {
    if (dsu[x] == x) return x;
    return dsu[x] = find(dsu[x]);
}

int unite(int x, int y ){
    dsu[find(x)] = find(y);
}

void compress() {
    sort(vx.begin(), vx.end());
    int last = -1;
    for (const auto &pxt : vx) {
        if (pxt.first != last) k++;
        if (pxt.second > 0) edges[pxt.second].first = k;
        else edges[-pxt.second].second = k;
        last = pxt.first;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; i++) {
        cin >> x >> y;
        edges.push_back({x, y});
        vx.push_back({x, i});
        vx.push_back({y, -i});
    }
    compress();

    init(k);
    int sol = n;
    for (int i = 1, x, y; i <= m; i++) {
        x = edges[i].first, y = edges[i].second;
        if (find(x) != find(y)) {
            unite(x, y);
            sol--;
        }
    }
    cout << sol << endl;

    return 0;
}