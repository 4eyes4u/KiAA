/*
    FULL SCORE
*/

#include <bits/stdc++.h>
using namespace std;

void solve(string in, string pre) {
    if (in == "") return;

    int idx_1 = in.find_first_of(pre[0]);
    string in_1 = in.substr(0, idx_1);
    string in_2 = in.substr(idx_1 + 1);
    string pre_1 = pre.substr(1, idx_1);
    string pre_2 = pre.substr(idx_1 + 1);

    solve(in_1, pre_1);
    solve(in_2, pre_2);

    cout << pre[0];
}

int main() {
    int len;
    string in, pre;
    cin >> len >> in >> pre;
    
    solve(in, pre);
    cout << endl;

    return 0;
}