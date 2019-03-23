#include <bits/stdc++.h>
using namespace std;

const int N = 5e3 + 10;

vector<int> g[N], h[N], inv[N], scc[N], topo;
stack<int> box;
bitset<N> bs[N];
set<pair<int, int>> added_edges;
int in[N], in_deg[N];
bool mark[N];

void dfs1(int v) {
    mark[v] = 1;
    
    for (auto xt: g[v])
    	if (!mark[xt])
    		dfs1(xt);
    
    box.push(v);
}

void dfs2(int v, int k){
    scc[k].emplace_back(v);
    in[v] = k;
    
    for (auto xt: inv[v])
    	if (!in[xt])
    		dfs2(xt, k);
}

int Kosaraju(int n) {
	int ret = 0;

    for (int i = 1; i <= n; i++)
    	if (!mark[i])
    		dfs1(i);

    while (!box.empty()) {
        int v = box.top();
        box.pop();
        
        if (!in[v]) {
            ret++;
            dfs2(v, ret);
        }
    }
    
    // number of SCC
    return ret;
}

bool Kahn(int n) {
    int topo_idx = 0;
    queue<int> q;
    for (int i = 1; i <= n; i++) 
        if (!in_deg[i])
            q.push(i);

    while (q.size()) {
        int v = q.front();
        q.pop();
        topo.emplace_back(v);
        topo_idx++;

        for (auto xt: h[v])
            if (!--in_deg[xt])
                q.emplace(xt);
    }

    return topo_idx == n;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        g[u].emplace_back(v);
        inv[v].emplace_back(u);
    }

    int n_scc = Kosaraju(n);

    for (int i = 1; i <= n; i++) {
        for (const int &xt : g[i]) {
            pair<int, int> edge = {min(in[i], in[xt]), max(in[i], in[xt])};
            if (edge.first != edge.second && added_edges.find(edge) == added_edges.end()) {
                h[in[i]].emplace_back(in[xt]);
                added_edges.insert(edge);
                in_deg[in[xt]]++;
            }
        }
    }

    bool flag = Kahn(n_scc);
    reverse(topo.begin(), topo.end());

    for (const int &comp : topo) {
        for (const int &v : scc[comp]) {
            bs[comp].set(v);
        }
    }

    int sol = 0;
    for (const int &comp : topo) {
        for (const int &xt : h[comp]) {
            bs[comp] |= bs[xt];
        }
        sol += scc[comp].size() * bs[comp].count();
    }

    cout << sol << endl;

    return 0;
}