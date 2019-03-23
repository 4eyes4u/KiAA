#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

const int N = 300;
const int dr[] = {1, -1, 0, 0};
const int dc[] = {0, 0, 1, -1};
const int N_MOVES = sizeof(dr) / sizeof(int);

bool mark[N][N];
char table[N][N];
int n, m, start_r, start_c;

inline bool valid_move(int r, int c) {
    return (r >= 0 && c >=0 && r <= n + 1 && c <= m + 1 && table[r][c] == ' ');
}

void dfs(int row, int col) {
    mark[row][col] = 1;
    for (int move = 0; move < N_MOVES; move++) {
        int xt_row = row + dr[move];
        int xt_col = col + dc[move];
        if (valid_move(xt_row, xt_col) && !mark[xt_row][xt_col]) {
            dfs(xt_row, xt_col);
        }
    }
}

void input() {
    scanf("%d%d%d%d%*c", &m, &n, &start_r, &start_c);
    start_r++, start_c++;
    string tmp;
    for (int i = 1; i <= n; i++) {
        getline(cin, tmp);
        for (int j = 0; j < m; j++) {
            table[i][j + 1] = tmp[j];
        }
    }
    for (int i = 0; i <= n + 1; i++) {
        table[i][0] = ' ';
        table[i][m + 1] = ' ';
    }
    for (int j = 0; j <= m + 1; j++) {
        table[0][j] = ' ';
        table[n + 1][j] = ' ';
    }
}

void solve() {
    dfs(start_r, start_c);

    bool flag = false;
    for (int i = 1; i <= n; i++) {
        flag |= mark[i][0];
        flag |= mark[i][m + 1];
    }
    for (int j = 1; j <= m; j++) {
        flag |= mark[0][j];
        flag |= mark[n + 1][j];
    }

    puts(flag ? "DA" : "NE");
}

int main() {
    input();
    solve();

    return 0;
}