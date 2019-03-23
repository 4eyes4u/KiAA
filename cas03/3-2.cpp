#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1e6 + 10;

int bit[N];
pair<int, int> p[N];

void update(int x) {
    for (; x < N; x += x & -x)
        bit[x]++;
}

int get(int x) {
    int ret = 0;
    for (; x; x -= x & -x)
        ret += bit[x];
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        p[i] = {x, i};
    }

    sort(p + 1, p + n + 1);

    long long sol = 0;
    for (int i = 1; i <= n; i++) {
        int x = p[i].second;
        int query = get(x);
        sol += 1ll * (x - query - 1) * (i - query - 1);
        update(x);
    }
    cout << sol;

    return 0;
}