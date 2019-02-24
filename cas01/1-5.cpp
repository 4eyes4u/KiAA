/*
    FULL SCORE
*/

#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node *l, *r;
    int val;
};

vector<Node *> generate(int start, int end) {
    if (start > end) {
        vector<Node *> ret;
        ret.push_back(nullptr);
        return ret;
    }

    vector<Node *> ret;
    for (int i = start; i <= end; i++) {
        vector<Node *> sub_left = generate(start, i - 1);
        vector<Node *> sub_right = generate(i + 1, end);

        for (auto child_l : sub_left) {
            for (auto child_r : sub_right) {
                Node *tmp = new Node();
                tmp->val = i;
                tmp->l = child_l;
                tmp->r = child_r;
                ret.push_back(tmp);
            }
        }
    }

    return ret;
}

void pre_order(Node *v) {
    if (!v) return;
    printf("%d ", v->val);
    pre_order(v->l);
    pre_order(v->r);
}

int main() {
    int n;
    scanf("%d", &n);

    auto trees = generate(1, n);
    for (auto root : trees) {
        pre_order(root);
        puts("");
    }

    return 0;
}