/*
    FULL SCORE
*/

#include <bits/stdc++.h>
using namespace std;

const int TEST_SIZE = 4;

bool extract(long long x, const int p) {    
    int cnt[p] = {false};
    while (x) {
        cnt[x % p]++;
        x -= x % p;
        x /= p;
    }

    for (int i = 3; i < p; i++)
        if (cnt[i])
            return 0;

    if (cnt[1] == 0) // equal or not possible
        return 0;
    if (cnt[1] == 1 && cnt[2] == 0) // second number has to be 0 - not possible
        return 0;
    if (cnt[1] == 1) // they are different
        return 1;
    if (cnt[1] == 2 && cnt[2] == 0) // exactly one way
        return 1;
    
    return 0;
}

int main() {
    int p;
    scanf("%d", &p);

    for (int i = 0; i < TEST_SIZE; i++) {
        long long x;
        scanf("%lld", &x);
        bool possible = extract(x, p);
        printf(possible ? "1" : "0");
        printf(i == TEST_SIZE - 1 ? "\n" : " ");
    }

    return 0;
}