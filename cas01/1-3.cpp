/*
    FULL SCORE
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 15;

int mat[N][N], dp[N][N];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &mat[i][j]);

    for (int j = 2; j <= n; j++) {
        int light = (dp[1][j - 1] + mat[1][j]) % 2;
        dp[1][j] = dp[1][j - 1] + (light == 1 ? 1 : 2);
    }
    for (int i = 2; i <= n; i++) {
        int light = (dp[i - 1][1] + mat[i][1]) % 2;
        dp[i][1] = dp[i - 1][1] + (light == 1 ? 1 : 2);
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= n; j++) {
            int light1 = (dp[i - 1][j] + mat[i][j]) % 2;
            int d1 = dp[i - 1][j] + (light1 == 1 ? 1 : 2);

            int light2 = (dp[i][j - 1] + mat[i][j]) % 2;
            int d2 = dp[i][j - 1] + (light2 == 1 ? 1 : 2);

            dp[i][j] = min(d1, d2);
        }
    }

    printf("%d\n", dp[n][n] + 1);

    return 0;
}