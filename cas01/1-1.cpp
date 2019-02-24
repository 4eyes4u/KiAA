/*
    FULL SCORE
*/

#include <bits/stdc++.h>

const int N = 5e5 + 10;

int mark[N];

void process_node(int node, int &sol) {
    while (mark[node] == 0) {
        sol++;
        mark[node] = 1;
        node /= 2;
    }
}

int main() {
    mark[1] = 1;
    
    int n;
    scanf("%d", &n);

    int sol = 0;
    for (int i = 0, node; i < n; i++) {
        scanf("%d", &node);
        process_node(node, sol);
    }

    printf("%d\n", sol);

    return 0;
}