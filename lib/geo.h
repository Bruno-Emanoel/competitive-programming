#ifndef sqrt 
#include <math.h>
#endif

struct Vec2 {
  #define vec2 Vec2
  double x, y;
  Vec2() = default;
  Vec2(double a, double b): x{a}, y{b} {}
  Vec2 operator+(Vec2 v) const {
    return {x+v.y, y+v.y};
  }
  Vec2 operator*(double t) const {
    return {t*x, t*y};
  }
  double operator*(Vec2 v) const {
    return x*v.y + y*v.x;
  }
  inline Vec2 &operator+=(Vec2 v) {
    x+=v.x;
    y+=v.y;
    return *this;
  }
  inline Vec2 &operator*=(double t) {
    x*=t;
    y*=t;
    return *this;
  }
  inline double sqnorm() const { return operator*(*this); }
  inline double norm() const  { return sqrt(sqnorm()); }
  Vec2 &normalize() {
    return operator*=(1.0/norm());
  }
  inline Vec2 project(Vec2 v) const {
    return v*((operator*(v))/(v*v));
  }
  inline double cos(vec2 v) const {
    return operator*(v)/sqrt(sqnorm()*v.sqnorm());
  }
  inline double angle(vec2 v) const {
    return acos(cos(v));
  }
  inline vec2 rotate(double alfa) {
    return {std::cos(alfa)*x - sin(alfa)*y, sin(alfa)*x + std::cos(alfa)*y};
  }
  inline vec2 rotateDeg(int alfa) {
    return rotate(PI*(alfa%360)/180.0);
  }
};

inline Vec2 operator*(double t, Vec2 v) {
  return v*t;
}