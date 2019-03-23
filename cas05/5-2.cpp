#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <utility>
#include <set>
#include <array>

using std::array;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::stack;
using std::queue;
using std::pair;
using std::set;
using std::cerr;

const int N = 2e3 + 10;

vector<int> g[N], inv[N], dag[N], scc[N], topo;
array<int, N> indeg, outdeg, in;
array<bool, N> mark; 
stack<int> box;
int n_scc;

namespace StronglyConnectedComponents {

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

    void Kosaraju(int n) {
        for (int i = 0; i < n; i++)
            if (!mark[i])
                dfs1(i);

        while (!box.empty()) {
            int v = box.top();
            box.pop();
            if (!in[v]) {
                n_scc++;
                dfs2(v, n_scc);
            }
        }
    }

    void condensation(int n) {
        set<pair<int, int>> added;
        for (int i = 0; i < n; i++) {
            for (const int &xt : g[i]) {
                // the same SCC
                if (in[i] == in[xt])
                    continue;

                pair<int, int> entry = {std::min(in[xt], in[i]), std::max({in[xt], in[i]})};
                if (added.find(entry) == added.end()) {
                    added.insert(entry);
                    dag[in[i]].emplace_back(in[xt]);
                    indeg[in[xt]]++;
                    outdeg[in[i]]++;
                }   
            }
        }
    }
}

namespace TopologicalSort {

    void Kahn(int n) {
        array<int, N> tmp;
        std::copy_n(indeg.begin(), N, tmp.begin());

        queue<int> q;
        for (int i = 1; i <= n; i++)
            if (!tmp[i])
                q.push(i);

        while (q.size()) {
            int v = q.front();
            q.pop();
            topo.emplace_back(v);
            for (const int &xt: dag[v])
                if (!--tmp[xt])
                    q.emplace(xt);
        }
    }
}

namespace MainSolver {
    void dfs(int v) {
        mark[v] = true;
        for (const int &xt : dag[v]) {
            if (!mark[xt]) {
                dfs(xt);
            }
        }
    }

    int first_subtask() {
        std::fill(mark.begin(), mark.end(), 0);
        int ret = 0;
        for (const int &v : topo) {
            if (!mark[v]) {
                ret++;
                dfs(v);
            }
        }
        return ret;
    }

    int second_subtask() {
        int X = 0, Y = 0;
        for (int i = 1; i <= n_scc; i++) {
            if (indeg[i] == 0) X++;
            if (outdeg[i] == 0) Y++;
        }
        return std::max(X, Y) * (n_scc != 1);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        g[u].emplace_back(v);
        inv[v].emplace_back(u);
    }

    StronglyConnectedComponents::Kosaraju(n);
    StronglyConnectedComponents::condensation(n);
    TopologicalSort::Kahn(n_scc);
    cout << MainSolver::first_subtask() << " " << MainSolver::second_subtask() << endl;


    return 0;
}