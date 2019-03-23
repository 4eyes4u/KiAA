#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

const int N = 1e6 + 10;

int bit[N];

void update(int x, int val) {
    while (x < N) {
        bit[x] += val;
        x += x & -x;
    }
}

int get(int x) {
    int ret = 0;
    while (x) {
        ret += bit[x];
        x -= x & -x;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;

    long long sol = 0;
    for (int i = 1, val; i <= n; i++) {
        cin >> val;
        update(val, 1);
        sol += 1ll * (i - get(val));
    }

    cout << sol;

    return 0;
}