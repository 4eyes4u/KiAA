/*
    8/10 (iostream is too slow)
*/

#include <bits/stdc++.h>
using namespace std;

struct Node {
    unordered_map<int, Node *> adj;
    int size = 0;
    bool end = 0;
};

bool find(Node *v, string s, int pos = 0) {
    if (pos == s.length()) return v->end;

    char c = s[pos];
    auto child = v->adj.find(c);
    if (child != v->adj.end())
        return find(v->adj[c], s, pos + 1);
    return false;
}

void add(Node *v, string s, int pos = 0) {
    v->size++;
    if (pos == s.length()) {
        v->end = true;
        return;
    }

    char c = s[pos];
    auto child = v->adj.find(c);
    if (child == v->adj.end())
        v->adj[c] = new Node();
    add(v->adj[c], s, pos + 1);
}

int smaller(Node *v, string s, int pos = 0) {
    if (pos == s.length())
        return 0;

    int ret = v->end;
    char c = s[pos];
    for (char i = 'a'; i < c; i++) {
        auto child = v->adj.find(i);
        if (child != v->adj.end())
            ret += v->adj[i]->size;
    }

    return ret + smaller(v->adj[c], s, pos + 1);
}

int main() {
    // syncing iostream and stdio
    ios::sync_with_stdio(false);
    cin.tie(0);

    Node *root = new Node();

    int q;
    cin >> q;
    string command, word;
    while (q--) {
        cin >> command >> word;
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        bool exist = find(root, word);
        if (command.compare("LESS") == 0) {
            if (exist) cout << smaller(root, word) << endl;
            else cout << "NA" << endl;
        }
        else if (!exist) add(root, word);
    }

    return 0;
}