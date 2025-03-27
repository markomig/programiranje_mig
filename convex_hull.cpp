#include <bits/stdc++.h>
using namespace std;


struct Point {
    int x, y;


    Point(int x1, int y1) {
        x = x1;
        y = y1;
    }

    bool operator<(const Point& p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};

// funkcija za da odredime dali e levo ili desno
bool dali_desno(Point p, Point q, Point r) {
    int det = (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
    return det <= 0;  // ako r e pomalo od 0 vrakja true
}

int main() {
    int n;
    cin >> n;

    vector<Point> tocki;
    set<pair<Point, Point>> rebra;


    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        tocki.push_back(Point(x, y));
    }


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;

            Point p1 = tocki[i];
            Point p2 = tocki[j];
            bool valid = true;


            for (int k = 0; k < n; k++) {
                if (k == i || k == j) continue;

                Point p3 = tocki[k];
                if (!dali_desno(p1, p2, p3)) {
                    valid = false;// proveruvame dali tockata p3 e vo convex hull, ako ne e, rebroto od tocki p1 i p2 ne e validno
                    break;
                }
            }


            if (valid) {
                rebra.insert({p1, p2});
            }
        }
    }


    for (const auto& rebro : rebra) {
        Point a = rebro.first;
        Point b = rebro.second;
        cout << "(" << a.x << ", " << a.y << ") -> (" << b.x << ", " << b.y << ")" << endl;
    }

    return 0;
}
