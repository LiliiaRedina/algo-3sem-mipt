#include <iostream>
#include <iomanip>
#include <vector>

struct Point {
    int x, y;

    Point(): x(0ll), y(0ll) {}

    Point(int a, int b): x(a), y(b) {}

    Point(const Point& other) {
        x = other.x;
        y = other.y;
    }

    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }
};

int cross(const Point& first, const Point& second) {
    return first.x * second.y - first.y * second.x;
}

bool check_inside(int n, const Point& point, const std::vector<Point>& vertex) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        Point min_p, max_p;
        if (vertex[i].y < vertex[(i + 1) % n].y) {
            min_p = vertex[i];
            max_p = vertex[(i + 1) % n];
        } else {
            max_p = vertex[i];
            min_p = vertex[(i + 1) % n];
        }

        if (point.y <= max_p.y && point.y >= min_p.y && cross(min_p - max_p, point - max_p) == 0) {
            return true;
        }
        if (vertex[i].y == vertex[(i + 1) % n].y) {
            continue;
        }
        if (point.y >= std::max(vertex[i].y, vertex[(i + 1) % n].y) ||
            point.y < std::min(vertex[i].y, vertex[(i + 1) % n].y)) {
            continue;
        }

        if (cross(min_p - max_p, point - max_p) < 0) {
            ++count;
        }
    }

    if (count % 2) {
        return true;
    } else {
        return false;
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<Point> vertex(n);
    int x, y;
    std::cin >> x >> y;
    Point point(x, y);
    for (int i = 0; i < n; ++i) {
        std::cin >> x >> y;
        vertex[i] = Point(x, y);
    }

    if (check_inside(n, point, vertex)) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }

    return 0;
}