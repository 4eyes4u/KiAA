#include <bits/stdc++.h>
using namespace std;

const int LEN = 1e6 + 10;

struct Node {
    unordered_map<char, Node *> adj;
    bool end = 0;
};

char word[LEN];

int solve(Node *v, int len) {
    if (len == 0) return (int)(v->end);

    int ret = 0;
    for (auto entry : v->adj)
        ret += solve(entry.second, len - 1);

    return max(ret, (int)(v->end));
}

void add(Node *v, char *s, int len, int pos = 0) {
    if (pos == len) {
        v->end = true;
        return;
    }

    char c = s[pos];
    auto child = v->adj.find(c);
    if (child == v->adj.end())
        v->adj[c] = new Node();

    add(v->adj[c], s, len, pos + 1);
}

int main() {
    Node *root = new Node();

    int n, d, max_len = 0;
    scanf("%d%d", &n, &d);
    for (int i = 0; i < n; i++) {
        scanf("%s", word);
        int len = strlen(word);
        add(root, word, len);
        max_len = max(max_len, len);
    }

    int l = 1, r = max_len, sol = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        int tmp = solve(root, mid);

        if (tmp >= d) {
            sol = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }

    printf("%d\n", sol);

    return 0;
}