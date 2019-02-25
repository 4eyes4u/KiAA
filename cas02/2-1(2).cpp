/*
    FULL SCORE
*/

#include <bits/stdc++.h>
using namespace std;

const int COMMAND_LEN = 20;
const int WORD_LEN = 1e6 + 10;

struct Node {
    unordered_map<int, Node *> adj;
    int size = 0;
    bool end = 0;
};

char command[COMMAND_LEN], word[WORD_LEN];

bool find(Node *v, char *s, int len, int pos = 0) {
    if (pos == len) return v->end;

    char c = s[pos];
    auto child = v->adj.find(c);
    if (child != v->adj.end())
        return find(v->adj[c], s, len, pos + 1);
    return false;
}

void add(Node *v, char *s, int len, int pos = 0) {
    v->size++;
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

int smaller(Node *v, char *s, int len, int pos = 0) {
    if (pos == len)
        return 0;

    int ret = v->end;
    char c = s[pos];
    for (char i = 'a'; i < c; i++) {
        auto child = v->adj.find(i);
        if (child != v->adj.end())
            ret += v->adj[i]->size;
    }

    return ret + smaller(v->adj[c], s, len, pos + 1);
}

int main() {
    Node *root = new Node();

    int q;
    scanf("%d", &q);
    while (q--) {
        scanf("%s%s", command, word);
        int len = strlen(word);
        transform(word, word + len, word, ::tolower);
        bool exist = find(root, word, len);
        if (!strcmp(command, "LESS")) {
            if (exist) printf("%d\n", smaller(root, word, len));
            else puts("NA");
        }
        else if (!exist) add(root, word, len);
    }

    return 0;
}