#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

struct Point;

long long cross(const Point& first, const Point& second);

struct Point {
    long long x, y;

    Point(): x(0ll), y(0ll) {}

    Point(long long a, long long b): x(a), y(b) {}

    Point(const Point& other) {
        x = other.x;
        y = other.y;
    }

    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }

    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }

    bool operator==(const Point& other) const {
        return (x == other.x && y == other.y);
    }

    bool operator<(const Point& other) const {
        if (cross(*this, other) > 0) {
            return true;
        }
        if (cross(*this, other) == 0) {
            if (len_sq() < other.len_sq()) {
                return true;
            } else {
                return false;
            }
        }
        return false;
    }

    long long len_sq() const {
        return x * x + y * y;
    }
};

long long cross(const Point& first, const Point& second) {
    return first.x * second.y - first.y * second.x;
}

Point sort_angle(std::vector<Point>& vertex) {
    int n = vertex.size();

    Point min_x_min_y = vertex[0];
    for (int i = 0; i < n; ++i) {
        if (vertex[i].x < min_x_min_y.x) {
            min_x_min_y = vertex[i];
        }
        if (vertex[i].x == min_x_min_y.x && vertex[i].y < min_x_min_y.y) {
            min_x_min_y = vertex[i];
        }
    }

    std::vector<Point> for_sort(n);
    for (int i = 0; i < n; ++i) {
        for_sort[i] = vertex[i] - min_x_min_y;
    }
    std::sort(for_sort.begin(), for_sort.end());
    for (int i = 0; i < n; ++i) {
        vertex[i] = for_sort[i] + min_x_min_y;
    }

    return min_x_min_y;
}

void find_conv(std::vector<Point>& vertex, std::vector<Point>& conv) {
    int n = vertex.size();
    Point min_x_min_y = sort_angle(vertex);

    conv.push_back(min_x_min_y);
    if (!(vertex[0] == min_x_min_y)) {
        conv.push_back(vertex[0]);
    } else {
        conv.push_back(vertex[1]);
    }

    for (int i = 1; i < n; ++i) {
        if (vertex[i] == min_x_min_y) {
            continue;
        }
        if (vertex[i] == conv[conv.size() - 1]) {
            continue;
        }
        if (conv.size() < 2) {
            conv.push_back(vertex[i]);
            continue;
        }
        while (conv.size() >= 2) {
            Point a = conv[conv.size() - 1];
            Point b = conv[conv.size() - 2];

            if (cross(a - b, vertex[i] - b) > 0) {
                break;
            }
            if (cross(a - b, vertex[i] - b) == 0 &&
                    (a - b).len_sq() >= (vertex[i] - b).len_sq()) {
                break;
            }
            conv.pop_back();
        }
        conv.push_back(vertex[i]);
    }
}

int main() {
    long long n;
    std::cin >> n;
    std::vector<Point> vertex(n);
    long long x, y;

    for (int i = 0; i < n; ++i) {
        std::cin >> x >> y;
        vertex[i] = Point(x, y);
    }

    std::vector<Point> conv;
    find_conv(vertex, conv);

    std::cout << conv.size() << "\n";
    for (auto& i: conv) {
        std::cout << i.x << " " << i.y << "\n";
    }

    return 0;
}