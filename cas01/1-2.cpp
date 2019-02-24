/*
    FULL SCORE
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 5e6 + 10;
const int INF = 1e9;

vector<int> g[N];
int n, cnt, dp[N], save[N][3];

int precalc(int d, int carry) {
    if (d == 0) return carry;
    return (1 << (d + 1)) - 1 - carry;
}

void dfs(int v, int d, int carry = 0) {
    /*
        v: root of tree
        d: depth of final tree
        carry: how many operations are propagated for this subtree ( <= 2)
    */

    if (save[v][carry] != -1)
        return;

    if (d == 0) {
        // children have to deleted
        dp[v] = g[v].size() + carry;
    }
    else {
        if (g[v].size() == 0) {
            // empty subtree
            dp[v] = precalc(d, carry);
        }
        else if (g[v].size() == 1) {
            if (carry == 0) {
                dfs(g[v][0], d - 1, 1);
                dp[v] = 1 + save[g[v][0]][1] + precalc(d - 1, 0);
                dp[v] = min(dp[v], 3 + precalc(d - 1, 1) + precalc(d - 1, 0));
            }
            else if (carry == 1) {
                dfs(g[v][0], d - 1, 1);
                dp[v] = save[g[v][0]][1] + precalc(d - 1, 0);
                dp[v] = min(dp[v], 2 + precalc(d - 1, 1) + precalc(d - 1, 0));
            }
            else {
                g[v].emplace_back(++cnt);
                g[v].emplace_back(++cnt);
                dfs(g[v][0], d - 1, 2);
                dfs(g[v][1], d - 1, 1);
                dfs(g[v][2], d - 1, 0);

                int mn_1 = INF, mn_2 = INF;
                for (int i = 0; i < 3; i++) {
                    int xt = g[v][i], j = 2 - i;
                    if (save[xt][j] <= mn_1) {
                        mn_2 = mn_1;
                        mn_1 = save[xt][j];
                    }
                    else if (save[xt][j] < mn_2)
                        mn_2 = save[xt][j];
                }

                dp[v] = mn_1 + mn_2 + 1;
            }
        }
        else {
            int init_size = g[v].size();
            g[v].emplace_back(++cnt);
            g[v].emplace_back(++cnt);
            dp[v] = INF;
            
            for (int c = carry; c <= 2; c++) {
                int mn_1 = INF, mn_2 = INF;
                for (int i = 0; i < init_size; i++) {
                    int xt = g[v][i];
                    dfs(xt, d - 1, c);

                    if (save[xt][c] <= mn_1) {
                        mn_2 = mn_1;
                        mn_1 = save[xt][c];
                    }
                    else if (save[xt][c] < mn_2)
                        mn_2 = save[xt][c];
                }
                for (int i = init_size; i < init_size + c; i++) {
                    int xt = g[v][i], j = c - 1 - (i - init_size);
                    dfs(xt, d - 1, j);

                    if (save[xt][j] <= mn_1) {
                        mn_2 = mn_1;
                        mn_1 = save[xt][j];
                    }
                    else if (save[xt][j] < mn_2)
                        mn_2 = save[xt][j];
                }
                
                dp[v] = min(dp[v], mn_1 + mn_2 + (c - carry) + (init_size + c - 2));
            }

            g[v].pop_back();
            g[v].pop_back();
        }
    }

    // memoization
    save[v][carry] = dp[v];
}

int main() {
    memset(save, -1, sizeof(save));

    int n, d;
    scanf("%d%d", &n, &d);
    cnt = n;
    for (int i = 2, node; i <= n; i++) {
        scanf("%d", &node);
        g[node].emplace_back(i);
    }

    dfs(1, d);

    printf("%d\n", dp[1]);

    return 0;
}