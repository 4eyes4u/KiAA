#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::endl;

const int N = 1e6 + 10;

std::vector<int> g[N];

inline void terminate(std::string s) {
    cout << s << endl;
    exit(0);
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int n_children, node;
        cin >> n_children;
        while (n_children--) {
            cin >> node;
            g[i].emplace_back(node);
            g[node].emplace_back(i);
        }
    }

    for (int i = 0; i < n; i++) {
        int mx_1 = 0, mx_2 = -1, mx_3 = -1;
        for (const int &xt : g[i]) {
            int size = g[xt].size();
            if (size >= mx_1) {
                mx_3 = mx_2;
                mx_2 = mx_1;
                mx_1 = size;
            }
            else if (size >= mx_2) {
                mx_3 = mx_2;
                mx_2 = size;
            }
            else if (size > mx_3) {
                mx_3 = size;
            }
        }

        if (mx_1 >= 2 && mx_2 >= 2 && mx_3 >= 2) {
            terminate("no");
        }
    }

    terminate("yes");

    return 0;
}