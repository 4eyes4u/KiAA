/*
    FULL SCORE
*/

#include <bits/stdc++.h>
using namespace std;

void solve(string in, string post) {
    if (in == "") return;

    int idx_1 = in.find_first_of(post.back());
    string in_1 = in.substr(0, idx_1);
    string in_2 = in.substr(idx_1 + 1);
    string post_1 = post.substr(0, idx_1);
    string post_2 = post.substr(idx_1, in_2.length());

    cout << post.back();
    solve(in_1, post_1);
    solve(in_2, post_2);
}

int main() {
    int len;
    string in, post;
    cin >> len >> in >> post;
    
    solve(in, post);
    cout << endl;

    return 0;
}