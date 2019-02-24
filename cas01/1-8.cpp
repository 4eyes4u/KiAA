/*
    FULL SCORE
*/

#include <bits/stdc++.h>
using namespace std;

const int SIZE = sizeof(long long);

long long xors[SIZE][2];

int main() {
    int n;
    scanf("%d", &n);
    
    long long main_xor = 0;
    for (int i = 0; i < n; i++) {
        long long x;
        scanf("%lld", &x);
        main_xor ^= x;

        for (int i = 0; i < SIZE; i++) {
            if ((x >> i) & 1)
                xors[i][1] ^= x;
            else
                xors[i][0] ^= x;
        }
    }

    for (int i = 0; i < SIZE; i++) {
        if ((main_xor >> i) & 1) {
            printf("%lld %lld\n", min(xors[i][0], xors[i][1]), max(xors[i][0], xors[i][1]));
            break;
        }
    }

    return 0;
}
