#include <bits/stdc++.h>
using namespace std;

const int N = 20;
const int LEN = 1e6 + 10;
const int SIGMA = 26;
const int INF = 1e9;

vector<int> submasks[N];
string s[N];
int cnt[N][SIGMA], total[N];

void generate_submasks(int n) {
    for (int i = 0; i < (1 << n); i++)
        submasks[__builtin_popcount(i)].emplace_back(i);
}

inline vector<int> extract_from_mask(int mask, int n) {
    vector<int> ret;
    for (int i = 0; i < n; i++)
        if (mask & (1 << i))
            ret.emplace_back(i);
    return ret;
}

int solve(int mask, const int &n) {
    int ret = 0;
    int mask_size = __builtin_popcount(mask);

    if (mask_size == 1) {
        int idx = (round)(log2(mask));
        return total[idx];
    }

    vector<int> in_mask = extract_from_mask(mask, n);
    vector<pair<int, int>> taken_chars;
    for (int c = 0; c < SIGMA; c++) {
        int tmp = n;
        for (const int &xt : in_mask)
            tmp = min(tmp, cnt[xt][c]);
        
        for (const int &xt : in_mask) {
            cnt[xt][c] -= tmp;
            total[xt] -= tmp;
        }
        
        if (tmp) {
            ret += tmp;
            taken_chars.emplace_back(c, tmp);
        }
    }

    int children = INF;
    for (int size = __builtin_popcount(mask) - 1, picked_size = 0; size >= 1 && picked_size == 0; size--) {
        for (const int sub : submasks[size]) {
            // sub has to be submask of mask
            if ((sub & mask) != sub) continue;

            vector<int> in_sub = extract_from_mask(sub, n);
            bool flag = false;
            for (int c = 0; c < SIGMA; c++) {
                int tmp = n;
                for (const int &xt : in_sub)
                    tmp = min(tmp, cnt[xt][c]);

                flag |= (tmp > 0);
            }

            if (flag) {
                int first_branch = solve(sub, n);
                int second_branch = solve(sub ^ mask, n);
                children = min(children, first_branch + second_branch);
            }

            picked_size = size;
        }
    }

    // not found any viable size so all strings are empty
    if (children == INF)
        children = 0;

    // reverting changes
    for (const auto &p : taken_chars)
        for (const int &xt : in_mask) {
            cnt[xt][p.first] += p.second;
            total[xt] += p.second;
        }

    return ret + children;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {\
        cin >> s[i];
        total[i] = s[i].length();
        for (int j = 0; j < s[i].length(); j++)
            cnt[i][s[i][j] - 'a']++;
    }

    generate_submasks(n);

    cout << 1 + solve((1 << n) - 1, n) << endl;

    return 0;
}