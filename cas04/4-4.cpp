#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 10;

struct Point {
    int x, y;
};

pair<Point, Point> segs[N];
int dsu[N];

inline long long ccw(Point O, Point A, Point B) {
    return 1ll * (A.x - O.x) * (B.y - O.y) - (B.x - O.x) * (A.y - O.y);
}

inline bool is_collinear(Point A, Point B, Point C) {
    return ccw(A, B, C) == 0;
}

inline bool is_left(Point A, Point B, Point C) {
    return ccw(A, B, C) > 0;
}

inline bool opposite(Point A, Point B, Point C, Point D) {
    return is_left(A, B, C) != is_left(A, B, D);
}

inline bool is_between(Point A, Point B, Point C) {
    return min(A.x, B.x) <= C.x && C.x <= max(A.x, B.x) && min(A.y, B.y) <= C.y && C.y <= max(A.y, B.y);
}

inline bool intersect(Point A, Point B, Point C, Point D) {
    if (is_collinear(A, B, C) && is_between(A, B, C))
        return true;
    if (is_collinear(A, B, D) && is_between(A, B, D))
        return true;
    if (is_collinear(C, D, A) && is_between(C, D, A))
        return true;
    if (is_collinear(C, D, B) && is_between(C, D, B))
        return true;
    
    return opposite(A, B, C, D) && opposite(C, D, A, B);
}

void init(int n) {
    for (int i = 1; i <= n; i++)
        dsu[i] = i;
}

inline int find(int a) {
    if (dsu[a] == a) return a;
    return dsu[a] = find(dsu[a]);
}

inline void unite(int a, int b) {
    dsu[find(a)] = find(b);
}

inline void read_segment(int i) {
    cin >> segs[i].first.x >> segs[i].first.y;
    cin >> segs[i].second.x >> segs[i].second.y;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        read_segment(i);
    init(n);

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (intersect(segs[i].first, segs[i].second, segs[j].first, segs[j].second)) {
                unite(i, j);
            }
        }
    }
    
    int sol = 0;
    for (int i = 1; i < n; i++) {
        if (find(i) != find(n)) {
            sol++;
        }
    }
    cout << sol << endl;

    return 0;
}