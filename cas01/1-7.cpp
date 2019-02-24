/*
    9/10 (flaw in final testcase)
*/

#include <bits/stdc++.h>
using namespace std;

const int dr[] = {-2, -2, -1, 1, -1, 1, 2, 2};
const int dc[] = {-1, 1, -2, -2, 2, 2, -1, 1};
const int INF = 1e9;
const int N = 8;
const int NODES = N * N;

int dist[N][N];
bool mark[N][N];

void bfs(int start_row, int start_col, const int &n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = INF;
    mark[start_row][start_col] = 1;
    dist[start_row ][start_col] = 0;
    queue<pair<int, int>> q;
    q.push({start_row, start_col});

    while (!q.empty()) {
        int cur_row = q.front().first;
        int cur_col = q.front().second;
        q.pop();

        for (int i = 0; i < 8; i++) {
            int row = cur_row + dr[i];
            int col = cur_col + dc[i];

            if (row >= 0 && col >= 0 && row < n && col < n && !mark[row][col]) {
                dist[row][col] = dist[cur_row][cur_col] + 1;
                mark[row][col] = 1;
                q.push({row, col});
            }
        }
    }
}

int main() {
    int sr, sc, er, ec;
    scanf("%d%d%d%d", &sr, &sc, &er, &ec);
    sr--, sc--, er--, ec--;
    assert(sr >= 0 && sr < N);
    assert(sc >= 0 && sc < N);
    assert(er >= 0 && er < N);
    assert(ec >= 0 && ec < N);
    bfs(sr, sc, N);
    printf("%d\n", dist[er][ec]);

    return 0;
}
