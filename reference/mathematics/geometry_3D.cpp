#include <bits/stdc++.h>
using namespace std;

class pv {
 public:
  double x, y, z;
  pv() {}
  pv(const double &x, const double &y, const double &z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }
  pv operator+(const pv &other) const {
    return pv(this->x + other.x, this->y + other.y, this->z + other.z);
  }
  pv operator-(const pv &other) const {
    return pv(this->x - other.x, this->y - other.y, this->z - other.z);
  }
  pv operator*(const double &k) const {
    return pv(this->x * k, this->y * k, this->z * k);
  }
  static double cross(const pv &A, const pv &B) {
    double x = (A.y * B.z) - (A.z * B.y);
    double y = (A.z * B.x) - (A.x * B.z);
    double z = (A.x * B.y) - (A.y * B.x);
    return norm(pv(x, y, z));
  }
  static double dot(const pv &A, const pv &B) {
    double X = (A.x * B.x);
    double Y = (A.y * B.y);
    double Z = (A.z * B.z);
    return X + Y + Z;
  }
  static double norm(const pv &P) { return sqrt(dot(P, P)); }
};

int main() {
  int t;
  scanf("%d", &t);
  while (t-- > 0) {
    vector<pv> v;
    for (int i = 0; i < 4; ++i) {
      int x, y, z;
      scanf("%d %d %d", &x, &y, &z);
      v.push_back(pv(x, y, z));
    }
    int r;
    scanf("%d", &r);
    double lo = 0, hi = 1123456789.0;
    for (int i = 0; i < 150; ++i) {
      const double mid = lo + ((hi - lo) / 2.0);
      pv P = v[0];
      pv Q = v[1] + (v[2] * mid);
      pv C = v[3];
      double distance = fabs(pv::cross(Q - P, C - P)) / pv::norm(Q - P);
      if (distance < r)
        lo = mid;
      else
        hi = mid;
    }
    printf("%.10lf\n", lo);
  }
  return 0;
}