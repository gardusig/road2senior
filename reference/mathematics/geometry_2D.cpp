#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

// point and vector class
class pv {
 public:
  double x, y;

  pv();
  pv(const double &x, const double &y);
  pv operator+(const pv &other) const;
  pv operator-(const pv &other) const;
  pv operator*(const double &k) const;
  pv operator/(const double &k) const;
  bool operator<(const pv &other) const;
  bool operator==(const pv &other) const;
};

// line, ray and segment class
class lrs {
 public:
  double a, b, c;
  pv start, finish, direction;

  lrs();
  lrs(const pv &start, const pv &finish);
  lrs(const double &a, const double &b, const double &c);
};

// circle class
class circle {
 public:
  pv C;
  double r;

  circle() {}
  circle(const pv &C, const double &r);
};

// 2D geometry namespace
namespace _2D {
double angle(const pv &A, const pv &O, const pv &B);
double convert_degree_to_radian(const double &degree);
double convert_radian_to_degree(const double &radian);
double cross(const pv &A, const pv &B);
double dot(const pv &A, const pv &B);
double norm(const pv &P);
pv perpendicular(const pv &P);
pv rotate(const pv &P, const double &rad);
pv unit(const pv &P);
lrs bisector(const pv &A, const pv &O, const pv &B);
double distance_line_line(const lrs &l1, const lrs &l2);
double distance_point_line(const pv &point, const lrs &line);
double distance_point_ray(const pv &point, const lrs &ray);
double distance_point_segment(const pv &point, const lrs &segment);
double distance_ray_ray(const lrs &r1, const lrs &r2);
double distance_ray_line(const lrs &ray, const lrs &line);
double distance_segment_segment(const lrs &s1, const lrs &s2);
double distance_segment_ray(const lrs &segment, const lrs &ray);
double distance_segment_line(const lrs &segment, const lrs &line);
vector<pv> line_line_intersect(const lrs &l1, const lrs &l2);
bool point_inside_line(const pv &point, const lrs &line);
bool point_inside_ray(const pv &point, const lrs &ray);
bool point_inside_segment(const pv &point, const lrs &segment);
vector<pv> circle_circle_intersection(const circle &c1, const circle &c2);
vector<pv> circle_line_intersection(const circle &_circle, const lrs &line);
pv circle_inside_triangle_center(const pv &A, const pv &B, const pv &C);
double circle_outside_triangle_radius(const pv &A, const pv &B, const pv &C);
bool point_inside_circle(const pv &P, const circle &_circle);
vector<pv> build_convex_hull(const vector<pv> &points);
}  // namespace _2D

pv::pv() {}

pv::pv(const double &x, const double &y) {
  this->x = x;
  this->y = y;
}

pv pv::operator+(const pv &other) const { return pv(x + other.x, y + other.y); }

pv pv::operator-(const pv &other) const { return pv(x - other.x, y - other.y); }

pv pv::operator*(const double &k) const { return pv(x * k, y * k); }

pv pv::operator/(const double &k) const { return pv(x / k, y / k); }

// bool pv::operator < (const pv &other) const {
//   if (x != other.x) {
//     return y < other.y;
//   }
//   return x < other.x;
// }

bool pv::operator<(const pv &other) const {
  double cross = _2D::cross(*this, other);
  if (cross > 0) {
    return true;
  }
  if (cross < 0) {
    return false;
  }
  if ((this->x < 0 and other.x >= 0) or (this->x >= 0 and other.x < 0)) {
    return this->x < other.x;
  }
  if ((this->y < 0 and other.y >= 0) or (this->y >= 0 and other.y < 0)) {
    return this->y < other.y;
  }
  return _2D::norm(*this) < _2D::norm(other);
}

bool pv::operator==(const pv &other) const {
  return fabs(x - other.x) + fabs(y - other.y) < EPS;
}

lrs::lrs() {}

lrs::lrs(const pv &start, const pv &finish) {
  this->start = start;
  this->finish = finish;
  this->direction = this->finish - this->start;
  if (direction.x == 0.0) {
    this->a = 1.0;
    this->b = 0.0;
    this->c = -start.x;
  } else {
    double slope = direction.y / direction.x;
    this->a = -slope;
    this->b = 1.0;
    this->c = slope * start.x - start.y;
  }
}

lrs::lrs(const double &a, const double &b, const double &c) {
  this->a = a;
  this->b = b;
  this->c = c;
  if (b == 0.0) {
    this->start = pv(-c / a, 0);
    this->finish = pv(-c / a, 1);
  } else {
    this->start = pv(0, -c / b);
    this->finish = pv(1, -(a + c) / b);
  }
  this->direction = finish - start;
}

double _2D::angle(const pv &A, const pv &O, const pv &B) {
  pv C = A - O, D = B - O;
  // if (_2D::cross(C, D) > 0)
  //   return acos(-1) * 2.0 - acos(_2D::dot(C, D) / (_2D::norm(C) *
  //   _2D::norm(D)));
  return acos(_2D::dot(C, D) / (_2D::norm(C) * norm(D)));
}

double _2D::convert_degree_to_radian(const double &degree) {
  return degree * acos(-1) / 180.0;
}

double _2D::convert_radian_to_degree(const double &radian) {
  return radian * 180.0 / acos(-1);
}

double _2D::cross(const pv &A, const pv &B) {
  return (A.x * B.y) - (A.y * B.x);
}

double _2D::dot(const pv &A, const pv &B) { return (A.x * B.x) + (A.y * B.y); }

double _2D::norm(const pv &P) { return sqrt(_2D::dot(P, P)); }

pv _2D::perpendicular(const pv &P) { return pv(-P.y, P.x); }

pv _2D::rotate(const pv &P, const double &rad) {
  return pv((P.x * cos(rad)) - (P.y * sin(rad)),
            (P.x * sin(rad)) + (P.y * cos(rad)));
}

pv _2D::unit(const pv &P) { return P / _2D::norm(P); }

lrs _2D::bisector(const pv &A, const pv &O, const pv &B) {
  pv X = (A - O);
  pv Y = (B - O);
  if (_2D::cross(X, Y) != 0) {
    return lrs(O, O + (_2D::unit(X) + _2D::unit(Y)));
  }
  if ((X.x < 0 and Y.x >= 0) or (X.x >= 0 and Y.x < 0) or
      (X.y < 0 and Y.y >= 0) or (X.y >= 0 and Y.y < 0)) {
    return lrs(O, O + _2D::perpendicular(X));
  }
  return lrs(O, O + X);
}

double _2D::distance_line_line(const lrs &l1, const lrs &l2) {
  const vector<pv> intersection = _2D::line_line_intersect(l1, l2);
  if (intersection.empty() == false) {
    return 0.0;
  }
  return _2D::distance_point_line(l1.start, l2);
}

double _2D::distance_point_line(const pv &point, const lrs &line) {
  return fabs(_2D::cross(point - line.start, line.direction)) /
         _2D::norm(line.direction);
}

double _2D::distance_point_ray(const pv &point, const lrs &ray) {
  if (_2D::dot(point - ray.start, ray.direction) < -EPS) {
    return _2D::norm(point - ray.start);
  }
  return distance_point_line(point, ray);
}

double _2D::distance_point_segment(const pv &point, const lrs &segment) {
  if (_2D::dot(point - segment.start, segment.finish - segment.start) < -EPS) {
    return _2D::norm(point - segment.start);
  }
  if (_2D::dot(point - segment.finish, segment.start - segment.finish) < -EPS) {
    return _2D::norm(point - segment.finish);
  }
  return _2D::distance_point_line(point, segment);
}

double _2D::distance_ray_ray(const lrs &r1, const lrs &r2) {
  const vector<pv> intersection = _2D::line_line_intersect(r1, r2);
  if (intersection.empty() == false and
      _2D::point_inside_ray(intersection[0], r1) == true and
      _2D::point_inside_ray(intersection[0], r2) == true) {
    return 0.0;
  }
  double ans = LLONG_MAX;
  ans = min(ans, _2D::distance_point_ray(r1.start, r2));
  ans = min(ans, _2D::distance_point_ray(r2.start, r1));
  return ans;
}

double _2D::distance_ray_line(const lrs &ray, const lrs &line) {
  const vector<pv> intersection = _2D::line_line_intersect(ray, line);
  if (intersection.empty() == false and
      _2D::point_inside_ray(intersection[0], ray) == true) {
    return 0.0;
  }
  return _2D::distance_point_line(ray.start, line);
}

double _2D::distance_segment_segment(const lrs &s1, const lrs &s2) {
  const vector<pv> intersection = _2D::line_line_intersect(s1, s2);
  if (intersection.empty() == false and
      _2D::point_inside_segment(intersection[0], s1) == true and
      _2D::point_inside_segment(intersection[0], s2) == true) {
    return 0.0;
  }
  double ans = LLONG_MAX;
  ans = min(ans, _2D::distance_point_segment(s1.start, s2));
  ans = min(ans, _2D::distance_point_segment(s1.finish, s2));
  ans = min(ans, _2D::distance_point_segment(s2.start, s1));
  ans = min(ans, _2D::distance_point_segment(s2.finish, s1));
  return ans;
}

double _2D::distance_segment_ray(const lrs &segment, const lrs &ray) {
  const vector<pv> intersection = _2D::line_line_intersect(segment, ray);
  if (intersection.empty() == false and
      _2D::point_inside_segment(intersection[0], segment) == true and
      _2D::point_inside_ray(intersection[0], ray) == true)
    return 0.0;
  double ans = LLONG_MAX;
  ans = min(ans, _2D::distance_point_ray(segment.start, ray));
  ans = min(ans, _2D::distance_point_ray(segment.finish, ray));
  ans = min(ans, _2D::distance_point_segment(ray.start, segment));
  return ans;
}

double _2D::distance_segment_line(const lrs &segment, const lrs &line) {
  vector<pv> intersection = _2D::line_line_intersect(segment, line);
  if (int(intersection.size()) and
      _2D::point_inside_segment(intersection[0], segment))
    return 0.0;
  double ans = LLONG_MAX;
  ans = min(ans, _2D::distance_point_line(segment.start, line));
  ans = min(ans, _2D::distance_point_line(segment.finish, line));
  return ans;
}

vector<pv> _2D::line_line_intersect(const lrs &l1, const lrs &l2) {
  vector<pv> ans;
  double den = _2D::cross(l1.direction, l2.direction);
  if (fabs(den) < EPS) {
    return ans;
  }
  double t = _2D::cross(l2.start - l1.start, l2.direction) / den;
  ans.push_back(l1.start + (l1.direction * t));
  return ans;
}

bool _2D::point_inside_line(const pv &point, const lrs &line) {
  return (fabs(_2D::cross(point - line.start, line.direction)) < EPS);
}

bool _2D::point_inside_ray(const pv &point, const lrs &ray) {
  if (fabs(_2D::cross(point - ray.start, ray.direction)) > EPS) {
    return false;
  }
  if (_2D::dot(point - ray.start, ray.direction) < -EPS) {
    return false;
  }
  return true;
}

bool _2D::point_inside_segment(const pv &point, const lrs &segment) {
  if (segment.start == segment.finish) {
    return point == segment.start;
  }
  if (fabs(_2D::cross(point - segment.start, segment.direction)) > EPS) {
    return false;
  }
  if (_2D::dot(point - segment.start, segment.finish - segment.start) < -EPS) {
    return false;
  }
  if (_2D::dot(point - segment.finish, segment.start - segment.finish) < -EPS) {
    return false;
  }
  return true;
}

vector<pv> _2D::circle_circle_intersection(const circle &c1, const circle &c2) {
  vector<pv> ans;
  double d = _2D::norm(c1.C - c2.C);
  if (d > c1.r + c2.r or d < fabs(c1.r - c2.r)) {
    return ans;
  }
  double x = (c1.r * c1.r - c2.r * c2.r + d * d) / (2.0 * d);
  if (c1.r * c1.r < x * x) {
    return ans;
  }
  double h = sqrt(c1.r * c1.r - x * x);
  pv P = c1.C + (_2D::unit(c2.C - c1.C) * x);
  if (h < EPS) {
    ans.push_back(P);
    return ans;
  }
  pv Q = _2D::perpendicular(_2D::unit(c2.C - c1.C)) * h;
  ans.push_back(P + Q);
  ans.push_back(P - Q);
  return ans;
}

vector<pv> _2D::circle_line_intersection(const circle &_circle,
                                         const lrs &line) {
  vector<pv> ans;
  double h = _2D::distance_point_line(_circle.C, line);
  if (h > _circle.r) {
    return ans;
  }
  pv P = _2D::line_line_intersect(
      line, lrs(_circle.C, _circle.C + _2D::perpendicular(line.direction)))[0];
  double delta = sqrt(_circle.r * _circle.r - h * h);
  if (delta < EPS) {
    ans.push_back(P);
    return ans;
  }
  pv Q = _2D::unit(line.direction) * delta;
  ans.push_back(P + Q);
  ans.push_back(P - Q);
  return ans;
}

pv _2D::circle_inside_triangle_center(const pv &A, const pv &B, const pv &C) {
  lrs l1 = _2D::bisector(A, B, C);
  lrs l2 = _2D::bisector(B, C, A);
  return _2D::line_line_intersect(l1, l2)[0];
}

double _2D::circle_outside_triangle_radius(const pv &A, const pv &B,
                                           const pv &C) {
  double ab = _2D::norm(A - B);
  double bc = _2D::norm(B - C);
  double ca = _2D::norm(C - A);
  double area = _2D::cross(B - A, C - A);
  return (ab * bc * ca) / (8.0 * area);
}

bool _2D::point_inside_circle(const pv &P, const circle &_circle) {
  return _2D::norm(P - _circle.C) <= _circle.r;
}

vector<pv> _2D::build_convex_hull(const vector<pv> &points) {
  auto v = points;
  int idx = 0;
  for (int i = 1; i < int(v.size()); i += 1) {
    if ((v[i].x < v[idx].x) or (v[i].x == v[idx].x and v[i].y < v[idx].y)) {
      idx = i;
    }
  }
  swap(v[0], v[idx]);
  for (int i = 1; i < int(v.size()); i += 1) {
    v[i] = (v[i] - v[0]);
  }
  sort(v.begin() + 1, v.end());
  for (int i = 1; i < int(v.size()); i += 1) {
    v[i] = (v[i] + v[0]);
  }
  stack<pv> st;
  for (int i = 1; i < int(v.size()); i += 1) {
    if (st.empty() == true) {
      if (_2D::cross(v[i] - v[0], v[(i + 1) % int(v.size())] - v[0]) != 0) {
        st.push(v[0]);
        st.push(v[i]);
        st.push(v[(i + 1) % int(v.size())]);
      }
    } else {
      pv A = v[i];
      while (int(st.size()) > 2) {
        pv B = st.top();
        st.pop();
        pv O = st.top();
        st.pop();
        if (_2D::cross(A - O, B - O) < 0) {
          st.push(O);
          st.push(B);
          break;
        }
        st.push(O);
      }
      st.push(A);
    }
  }
  v.clear();
  while (st.empty() == false) {
    v.push_back(st.top());
    st.pop();
  }
  reverse(v.begin(), v.end());
  return v;
}

// double polygon_area () {
//   double ans = 0;
//   for (int i = 0; i < int(v.size()); ++i)
//     ans += _2D::cross(v[i], v[(i + 1) % int(v.size())]);
//   return fabs(ans /2.0);
// }

// double polygon_perimeter () {
//   double ans = 0;
//   for (int i = 0; i < int(v.size()); ++i)
//     ans += _2D::norm(v[i] - v[(i + 1) % int(v.size())]);
//   return ans;
// }

// bool point_inside_polygon (const pv P) {
//   int lo = 1, hi = int(v.size()) - 2;
//   while (lo <= hi) {
//     const int mid = (lo + hi) >> 1;
//     if (_2D::cross(current - v[0], v[mid + 1] - v[0]) < 0)
//       lo = mid + 1;
//     else if (_2D::cross(current - v[0], v[mid] - v[0]) > 0)
//       hi = mid - 1;
//     else
//       return (_2D::cross(current - v[0], v[mid + 1] - v[0]) >= 0 and
//         _2D::cross(current - v[0], v[mid] - v[0]) <= 0 and
//         _2D::cross(current - v[mid], v[mid + 1] - v[mid]) <= 0);
//   }
//   return false;
// }

// void sort_lowest_first () {
//   int idx = 0;
//   for (int i = 1; i < int(v.size()); ++i)
//     if (v[i].x < v[idx].x or (v[i].x == v[idx].x and v[i].y < v[idx].y))
//       idx = i;
//   vector<pv> other;
//   for (int i = idx; i < int(v.size()); ++i)
//     other.push_back(v[i]);
//   for (int i = 0; i < idx; ++i)
//     other.push_back(v[i]);
//   v = other;
// }

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  return 0;
}