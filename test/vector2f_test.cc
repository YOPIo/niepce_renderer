/*
// ---------------------------------------------------------------------------
*/
#include <gtest/gtest.h>
#include "../src/algebra/vector2f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class Vector2fTest : public ::testing::Test {};
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector2fTest, DefaultConstructor)
{
  const Vector2f v;
  EXPECT_EQ (v[0], 0);
  EXPECT_EQ (v[1], 0);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector2fTest, TwoArgConstructor)
{
  const Float x = 1.0;
  const Float y = -5;
  Vector2f v (x, y);
  EXPECT_EQ (v.At (0), x);
  EXPECT_EQ (v.At (1), y);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector2fTest, OneArgConstructor)
{
  const Float x = 3.10;;
  Vector2f v (x);
  EXPECT_EQ (v.X (), x);
  EXPECT_EQ (v.Y (), x);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector2fTest, Setter)
{
  const int x = 3;
  const int y = -1;
  Vector2f v;
  v.SetX (x);
  v.SetY (y);
  EXPECT_EQ (v.X (), x);
  EXPECT_EQ (v.Y (), y);

  v[0] = -x;
  v[1] = -y;
  EXPECT_EQ (v.X (), -x);
  EXPECT_EQ (v.Y (), -y);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector2fTest, Comparison)
{
  const Vector2f v1 (-1.0, 1.5);
  const Vector2f v2 (-1.0, 1.5);
  const Vector2f v3 (-0.9, 1.5);

  EXPECT_EQ (v1, v2);
  EXPECT_NE (v1, v3);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector2fTest, Negative)
{
  const Float x = 8.5;
  const int   y = -8;
  const Vector2f v (x, y);

  EXPECT_EQ (Vector2f (-x, -y), -v);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector2fTest, Add)
{
  const Vector2f v1 (-1.0,  5.0);
  const Vector2f v2 (20.3, -8.9);

  const Vector2f ans1 (v1[0] + v2[0], v1[1] + v2[1]);

  EXPECT_EQ (v1 + v2, ans1);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector2fTest, Sub)
{
  const Vector2f v1 (-1.0,  5.0);
  const Vector2f v2 (20.3, -8.9);

  const Vector2f v12 (-21.3,  13.9);
  const Vector2f v21 ( 21.3, -13.9);

  EXPECT_EQ (v1 - v2, v12);
  EXPECT_EQ (v2 - v1, v21);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector2fTest, Mul)
{
  const Vector2f v1 (-1.0, 9.98);
  const Vector2f v2 ( 6.9, 7.16);
  const Float    t1 (8.0);

  const Vector2f ans1 (v1[0] * t1, v1[1] * t1);
  const Vector2f ans2 (v1[0] * v2[0], v1[1] * v2[1]);

  EXPECT_EQ (v1 * t1, ans1);
  EXPECT_EQ (Multiply (v1, v2), ans2);

}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector2fTest, Div)
{
  const Vector2f v1 (4.0, 9.0);
  const Float    t1 (2);

  const Vector2f ans1 (2.0, 4.5);

  EXPECT_EQ (v1 / t1, ans1);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector2fTest, Length)
{
  const Vector2f v (10.0, 10.0);
  const Float v_length         = 10 * std::sqrt (2);
  const Float v_length_squared = std::pow (10 * std::sqrt (2), 2.0);

  EXPECT_EQ (v.Length (), v_length);
  EXPECT_EQ (v.LengthSquared (), v_length_squared);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector2fTest, Normalize)
{
  Vector2f v (3.0, 3.0);
  const Vector2f nv1 = v.Normalized ();

  const Vector2f nv2 = v.Normalize ();
  EXPECT_EQ (nv2, v);
  EXPECT_EQ (v.IsNormalized (), true);
  EXPECT_EQ (v.Length (), 1.0);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector2fTest, NaN)
{
  Vector2f nan (0.0, -800);
  EXPECT_EQ (nan.HasNaN (), false);

  nan[0] = std::asin (1.1);
  EXPECT_EQ (nan.HasNaN (), true);

  nan[1] = std::sqrt (-0.675);
  EXPECT_EQ (nan.HasNaN (), true);

  nan[0] = std::log (-1.5);
  EXPECT_EQ (nan.HasNaN (), true);

  nan[1] = -225 % 2;
  EXPECT_EQ (nan.HasNaN (), true);

  const Float n = std::asin (1.1);
  nan[0] = n * 100;
  EXPECT_EQ (nan.HasNaN (), true);

  nan[1] = n / 1.0;
  EXPECT_EQ (nan.HasNaN (), true);

  nan[0] = n + 100;
  EXPECT_EQ (nan.HasNaN (), true);

  nan[1] = n - 100;
  EXPECT_EQ (nan.HasNaN (), true);

  nan[0] = n * 100;
  EXPECT_EQ (nan.HasNaN (), true);

  nan[1] = n / 100;
  EXPECT_EQ (nan.HasNaN (), true);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/

