#include "normal3.h"
#include "point2.h"
#include "point3.h"
#include "vector2.h"
#include "vector3.h"

namespace niepce
{

template <typename T>
Point3<T>::Point3() : x(0), y(0), z(0)
{}

template <typename T>
Point3<T>::Point3(T xx, T yy, T zz) : x(xx), y(yy), z(zz)
{
  Warningf(!HasNan(), "Detected a NaN at Point3<T>");
}

template <typename T>
Point3<T>::Point3(const Vector3<T>& v) : x(v.x), y(v.y), z(v.z)
{
  Warningf(!HasNan(), "Detected a NaN at Point3<T>");
}

template <typename T>
Point3<T>::Point3(const Normal3<T>& n) : x(n.x), y(n.y), z(n.z)
{}

template <typename T>
template <typename U>
Point3<T>::Point3(const Point3<U>& p) : x(p.x), y(p.y), z(p.z)
{
  Warningf(!HasNan(), "Detected a NaN at Point3<T>");
}
template <typename T>
template <typename U>
Point3<T>::Point3(const Vector3<U>& v) : x(v.x), y(v.y), z(v.z)
{
  Warningf(!HasNan(), "Detected a NaN at Point3<T>");
}

template <typename T>
Point3<T>::~Point3()
{}

template <typename T>
auto Point3<T>::operator == (const Point3<T>& p) -> bool
{
  return x == p.x && y == p.y && z == p.z;
}

template <typename T>
auto Point3<T>::operator != (const Point3<T>& p) -> bool
{
  return x != p.x || y != p.y || z != p.z;
}

template <typename T>
auto Point3<T>::operator [] (unsigned int idx) const -> T
{
  Warningf( !HasNan(), "Out of bounds.");
  if (idx == 0) { return x; }
  if (idx == 1) { return y; }
  return z;
}

template <typename T>
auto Point3<T>::operator [] (unsigned int idx) -> T&
{
  Warningf( !HasNan(), "Out of bounds.");
  if (idx == 0) { return x; }
  if (idx == 1) { return y; }
  return z;
}

template <typename T>
template <typename U>
Point3<T>::operator Vector3<U> () const
{
  return Vector3<U>(x, y, z);
}

template <typename T>
auto Point3<T>::operator + (const Point3<T>& p) const -> Point3<T>
{
  Warningf( !p.HasNan(), "Detected a NaN at Point3<T>");
  return Point3<T>(x + p.x, y + p.y, z + p.z);
}

template <typename T>
auto Point3<T>::operator + (const Vector3<T>& v) const -> Point3<T>
{
  Warningf( !v.HasNan(), "Detected a NaN at Point3<T>");

  return Point3<T>(x + v.x, y + v.y, z + v.z);
}

template <typename T>
auto Point3<T>::operator - (const Point3<T>& p) const -> Point3<T>
{
  Warningf( !p.HasNan(), "Detected a NaN at Point3<T>");
  return Point3<T>(x - p.x, y - p.y, y - p.z);
}

template <typename T>
auto Point3<T>::operator - (const Vector3<T>& v) const -> Point3<T>
{
  Warningf( !v.HasNan(), "Detected a NaN at Point3<T>");
  return Point3<T>(x + v.x, y + v.y, z + v.z);
}

template <typename T>
auto Point3<T>::operator += (const Point3<T>& p) -> Point3<T>&
{
  Warningf( !p.HasNan(), "Detected a NaN at Point3<T>");
  x += p.x;
  y += p.y;
  z += p.z;
  return *this;
}

template <typename T>
auto Point3<T>::operator += (const Vector3<T>& v) -> Point3<T>&
{
  Warningf( !v.HasNan(), "Detected a NaN at Point3<T>");
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

template <typename T>
auto Point3<T>::operator -= (const Point3<T>& p) -> Point3<T>&
{
  Warningf( !p.HasNan(), "Detected a NaN at Point3<T>");
  x -= p.x;
  y -= p.y;
  z -= p.z;
  return *this;
}

template <typename T>
auto Point3<T>::operator -= (const Vector3<T>& v) -> Point3<T>&
{
  Warningf( !v.HasNan(), "Detected a NaN at Point3<T>");
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}

template <typename T>
template <typename U>
auto Point3<T>::operator * (U f) const -> Point3<T>
{
  return Point3<T>(x * f, y * f, z * f);
}

template <typename T>
template <typename U>
auto Point3<T>::operator / (U f) const -> Point3<T>
{
  Assertf( f != 0, "Division by Zero.");
  Float inv = static_cast<Float>(1) / f;
  return Point3<T>(x * inv, y * inv, z * inv);
}

template <typename T>
template <typename U>
auto Point3<T>::operator *= (U f) -> Point3<T>&
{
  x *= f;
  y *= f;
  z *= f;
  return *this;
}

template <typename T>
template <typename U>
auto Point3<T>::operator /= (U f) -> Point3<T>&
{
  Assertf( f != 0, "Division by Zero.");
  Float inv = static_cast<Float>(1) / f;
  return Point3<T>(x * inv, y * inv, z * inv);
}

template <typename T>
auto Point3<T>::operator - () const -> Point3<T>
{
  return Point3<T>(-x, -y, -z);
}

template <typename T>
auto Point3<T>::HasNan() const -> bool
{
  return niepce::IsNan(x) && niepce::IsNan(y) && niepce::IsNan(z);
}

template <typename T>
auto Point3<T>::LengthSquared() const -> Float
{
  return x * x + y * y + z * z;
}

template <typename T>
auto Point3<T>::Length() const -> Float
{
  return std::sqrt( Length() );
}

template<typename T, typename U>
auto operator * (U f, Point3<T>& p) -> Point3<T>
{
  return p * f;
}

template <typename T>
auto operator << (std::ostream& os, const Point3<T>& p) -> std::ostream&
{
  os << "[" << p.x << ", " << p.y << ", " << p.z << "]";
  return os;
}

template <>
auto operator << (std::ostream& os, const Point3<Float>& p) -> std::ostream&
{
  os << "[" << p.x << ", " << p.y << ", " << p.z << "]";
  return os;
}

template <typename T>
inline auto Distance(const Point3<T>& p1, const Point3<T>& p2) -> Float
{
  return (p1 - p2).Lenght();
}

template <typename T>
inline auto Floor(const Point3<T>& p) -> Point3<T>
{
  return Point3<T>(std::floor(p.x), std::floor(p.y), std::floor(p.z));
}

template <typename T>
inline auto Ceil(const Point3<T>& p) -> Point3<T>
{
  return Point3<T>(std::ceil(p.x), std::ceil(p.y), std::ceil(p.z));
}

template <typename T>
inline auto Lerp(Float t, const Point2<T>& p1, const Point2<T>& p2) -> Point3<T>
{
  return (1 - t) * p1 + t * p2;
}

template <typename T>
inline auto Min(const Point3<T>& p1, const Point3<T>& p2) -> Point3<T>
{
  return Point3<T>(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z)  );
}

template <typename T>
inline auto Max(const Point3<T>& p1, const Point3<T>& p2) -> Point3<T>
{
  return Point3<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z, p2.z)  );
}

template <typename T>
inline auto Abs(const Point2<T>& p) -> Point3<T>
{
  return Point3<T>(std::abs(p.x), std::abs(p.y), std::abs(p.z));
}

template class Point3<Float>;
template class Point3<int>;

}  // namespace niepce
