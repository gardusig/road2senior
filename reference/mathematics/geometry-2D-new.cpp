#include <bits/stdc++.h>

namespace geometry2D {
// classes --------------------------------------------------------------------
template <typename T>
class PointVector {
 public:
  T x, y;

  PointVector(const T &x, const T &y);

  const PointVector<T> operator+(const PointVector<T> &other) const;
  const PointVector<T> operator-(const PointVector<T> &other) const;
  const PointVector<T> operator*(const T &k) const;
  const PointVector<T> operator/(const T &k) const;

  const bool operator<(const PointVector<T> &other) const;
  const bool operator==(const PointVector<T> &other) const;
};

template <typename T>
class LineRaySegment {
 public:
  T a, b, c;
  PointVector<T> start, finish, direction;

  LineRaySegment(const T &a, const T &b, const T &c);
  LineRaySegment(const PointVector<T> &start, const PointVector<T> &finish);
};

template <typename T>
class Circle {
 public:
  PointVector<T> center;
  T r;

  Circle() {}
  Circle(const PointVector<T> &center, const T &r);
};

template <typename T>
inline PointVector<T>::PointVector(const T &x, const T &y) {
  this->x = x;
  this->y = y;
}

template <typename T>
inline const PointVector<T> PointVector<T>::operator+(
    const PointVector<T> &other) const {
  return PointVector<T>(this->x + other.x, this->y + other.y);
}

template <typename T>
inline const PointVector<T> PointVector<T>::operator-(
    const PointVector<T> &other) const {
  return PointVector<T>(this->x - other.x, this->y - other.y);
}

template <typename T>
inline const PointVector<T> PointVector<T>::operator*(const T &k) const {
  return PointVector<T>(this->x * k, this->y * k);
}

template <typename T>
inline const PointVector<T> PointVector<T>::operator/(const T &k) const {
  return PointVector<T>(this->x / k, this->y / k);
}

template <typename T>
inline const bool PointVector<T>::operator<(const PointVector<T> &other) const {
  if (this->x == other.x) {
    return this->y < other.y;
  }
  return this->x < other.x;
}

template <typename T>
inline const bool PointVector<T>::operator==(
    const PointVector<T> &other) const {
  return this->x == other.x and this->y == other.y;
}
// classes --------------------------------------------------------------------

// methods --------------------------------------------------------------------
template <typename T>
T cross(const PointVector<T> &A, const PointVector<T> &B) {
  return (A.x * B.y) - (A.y * B.x);
}

template <typename T>
T dot(const PointVector<T> &A, const PointVector<T> &B) {
  return (A.x * B.x) + (A.y * B.y);
}

template <typename T>
double angle(const PointVector<T> &A, const PointVector<T> &O,
             const PointVector<T> &B) {
  const PointVector<T> C = A - O;
  const PointVector<T> D = B - O;
  if (cross(C, D) > 0) {
    return std::acos(-1) * 2.0 - acos(dot(C, D) / (norm(C) * norm(D)));
  }
  return std::acos(dot(C, D) / (norm(C) * norm(D)));
}

double degree_to_radian(const double &degree) {
  return degree * acos(-1) / 180.0;
}

double radian_to_degree(const double &radian) {
  return radian * 180.0 / acos(-1);
}

template <typename T>
double norm(const PointVector<T> &P) {
  return std::sqrt(dot(P, P));
}

template <typename T>
PointVector<T> perpendicular(const PointVector<T> &P) {
  return PointVector<T>(-P.y, P.x);
}

template <typename T>
PointVector<T> rotate(const PointVector<T> &P, const T &rad) {
  const T x = (P.x * std::cos(rad)) - (P.y * std::sin(rad));
  const T y = (P.x * std::sin(rad)) + (P.y * std::cos(rad));
  return PointVector<T>(x, y);
}

template <typename T>
PointVector<T> unit(const PointVector<T> &P) {
  return P / norm(P);
}

template <typename T>
LineRaySegment<T> bisector(const PointVector<T> &A, const PointVector<T> &O,
                           const PointVector<T> &B) {
  const PointVector<T> X = (A - O);
  const PointVector<T> Y = (B - O);
  if (cross(X, Y) != 0) {
    return LineRaySegment<T>(O, O + unit(X) + unit(Y));
  }
  if ((X.x < 0 and Y.x >= 0) or (X.x >= 0 and Y.x < 0) or
      (X.y < 0 and Y.y >= 0) or (X.y >= 0 and Y.y < 0)) {
    return LineRaySegment<T>(O, O + perpendicular(X));
  }
  return LineRaySegment<T>(O, O + X);
}

namespace distance {
template <typename T>
double line_line(const LineRaySegment<T> &l1, const LineRaySegment<T> &l2) {
  const vector<PointVector<T>> intersection = line_line_intersect(l1, l2);
  if (intersection.empty()) {
    return distance_point_line(l1.start, l2);
  }
  return 0.0;
}
}  // namespace distance

// double distance_line_line(const lrs &l1, const lrs &l2);
// double distance_point_line(const pv &point, const lrs &line);
// double distance_point_ray(const pv &point, const lrs &ray);
// double distance_point_segment(const pv &point, const lrs &segment);
// double distance_ray_ray(const lrs &r1, const lrs &r2);
// double distance_ray_line(const lrs &ray, const lrs &line);
// double distance_segment_segment(const lrs &s1, const lrs &s2);
// double distance_segment_ray(const lrs &segment, const lrs &ray);
// double distance_segment_line(const lrs &segment, const lrs &line);
// vector<pv> line_line_intersect(const lrs &l1, const lrs &l2);
// bool point_inside_line(const pv &point, const lrs &line);
// bool point_inside_ray(const pv &point, const lrs &ray);
// bool point_inside_segment(const pv &point, const lrs &segment);
// vector<pv> circle_circle_intersection(const circle &c1, const circle &c2);
// vector<pv> circle_line_intersection(const circle &_circle, const lrs &line);
// pv circle_inside_triangle_center(const pv &A, const pv &B, const pv &C);
// double circle_outside_triangle_radius(const pv &A, const pv &B, const pv &C);
// bool point_inside_circle(const pv &P, const circle &_circle);
// vector<pv> build_convex_hull(const vector<pv> &points);
// methods --------------------------------------------------------------------
}  // namespace geometry2D

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);

  return 0;
}