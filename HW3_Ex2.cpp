//Name: Nguyễn Thị Thu Uyên
//Student's ID: 22521643
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <float.h>

using namespace std;

struct Point {
    int x, y;
};

bool compareX(const Point& a, const Point& b) {
    return a.x < b.x;
}

bool compareY(const Point& a, const Point& b) {
    return a.y < b.y;
}

double distance(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double closestPairRec(vector<Point>& pointsX, vector<Point>& pointsY, int left, int right) {
    if (right - left <= 3) {
        double minDist = DBL_MAX;
        for (int i = left; i < right; ++i) {
            for (int j = i + 1; j < right; ++j) {
                minDist = min(minDist, distance(pointsX[i], pointsX[j]));
            }
        }
        return minDist;
    }

    int mid = left + (right - left) / 2;
    Point midPoint = pointsX[mid];

    vector<Point> pointsYLeft, pointsYRight;
    for (const auto& point : pointsY) {
        if (point.x <= midPoint.x) {
            pointsYLeft.push_back(point);
        } else {
            pointsYRight.push_back(point);
        }
    }

    double distLeft = closestPairRec(pointsX, pointsYLeft, left, mid);
    double distRight = closestPairRec(pointsX, pointsYRight, mid, right);
    double minDist = min(distLeft, distRight);

    vector<Point> strip;
    for (const auto& point : pointsY) {
        if (abs(point.x - midPoint.x) < minDist) {
            strip.push_back(point);
        }
    }

    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; ++j) {
            minDist = min(minDist, distance(strip[i], strip[j]));
        }
    }

    return minDist;
}

double closestPair(vector<Point>& points) {
    vector<Point> pointsX = points;
    vector<Point> pointsY = points;

    sort(pointsX.begin(), pointsX.end(), compareX);
    sort(pointsY.begin(), pointsY.end(), compareY);

    return closestPairRec(pointsX, pointsY, 0, points.size());
}

int main() {
    vector<Point> points = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    cout << "The smallest distance is " << closestPair(points) << endl;
    return 0;
}
