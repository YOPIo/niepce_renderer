/*
// ---------------------------------------------------------------------------
*/
#include <gtest/gtest.h>
#include "../src/core/vector4f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class Vector4fTest : public ::testing::Test {};
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector4fTest, DefaultConstructor)
{
  const Vector4f v;
  EXPECT_EQ (v[0], 0);
  EXPECT_EQ (v[1], 0);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector4fTest, TwoArgConstructor)
{
  const Float x = 1.0;
  const Float y = -5;
  const Float z = 999.0;
  const Float w = -1e-5;
  Vector4f v (x, y, z, w);
  EXPECT_EQ (v.At (0), x);
  EXPECT_EQ (v.At (1), y);
  EXPECT_EQ (v.At (2), z);
  EXPECT_EQ (v.At (3), w);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector4fTest, OneArgConstructor)
{
  const Float x = 3.10;;
  Vector4f v (x);
  EXPECT_EQ (v.X (), x);
  EXPECT_EQ (v.Y (), x);
  EXPECT_EQ (v.Z (), x);
  EXPECT_EQ (v.W (), x);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector4fTest, Setter)
{
  const int x = 3;
  const int y = -1;
  const int z = 89;
  const int w = -25;

  Vector4f v;
  v.SetX (x);
  v.SetY (y);
  v.SetZ (z);
  v.SetW (w);
  EXPECT_EQ (v.X (), x);
  EXPECT_EQ (v.Y (), y);
  EXPECT_EQ (v.Z (), z);
  EXPECT_EQ (v.W (), w);

  v[0] = -x;
  v[1] = -y;
  v[2] = -z;
  v[3] = -w;
  EXPECT_EQ (v.X (), -x);
  EXPECT_EQ (v.Y (), -y);
  EXPECT_EQ (v.Z (), -z);
  EXPECT_EQ (v.W (), -w);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector4fTest, Comparison)
{
  const Vector4f v1 (-1.0, 1.5, -0.1, 1e-10);
  const Vector4f v2 (-1.0, 1.5, -0.1, 1e-10);
  const Vector4f v3 (-0.9, 1.5, 25.3, 1e+5);

  EXPECT_EQ (v1, v2);
  EXPECT_NE (v1, v3);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector4fTest, Negative)
{
  const Float x = 8.5;
  const int   y = -8;
  const Float z = -0.01;
  const Float w = 1e+8;
  const Vector4f v (x, y, z, w);

  EXPECT_EQ (Vector4f (-x, -y, -z, -w), -v);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector4fTest, Add)
{
  const Vector4f v1 (-1.0,  5.0, -19.2, 1e-5);
  const Vector4f v2 (20.3, -8.9,  -8.1, 1e+1);

  const Vector4f ans1 (v1[0] + v2[0], v1[1] + v2[1],
                       v1[2] + v2[2], v1[3] + v2[3]);

  EXPECT_EQ (v1 + v2, ans1);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector4fTest, Sub)
{
  const Vector4f v1 (-1.0,  5.0, -19.2, 1e-5);
  const Vector4f v2 (20.3, -8.9,  -8.1, 1e+2);

  const Vector4f ans1 (v1[0] - v2[0], v1[1] - v2[1],
                       v1[2] - v2[2], v1[3] - v2[3]);

  EXPECT_EQ (v1 - v2, ans1);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector4fTest, Mul)
{
  const Vector4f v1 (-1.0,  5.0, -19.2, 1e-5);
  const Vector4f v2 (20.3, -8.9,  -8.1, 1e+3);
  const Float t = 8.0;

  const Vector4f ans1 (v1[0] * t, v1[1] * t, v1[2] * t, v1[3] * t);
  const Vector4f ans2 (v1[0] * v2[0], v1[1] * v2[1],
                       v1[2] * v2[2], v1[3] * v2[3]);

  EXPECT_EQ (v1 * t,  ans1);
  EXPECT_EQ (Multiply (v1, v2), ans2);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector4fTest, Div)
{
  const Vector4f v1 (4.0, 9.0, -15.3, 1e-5);
  const Float    t1 (2);

  const Vector4f ans1 (v1[0] / t1, v1[1] / t1,
                       v1[2] / t1, v1[3] / t1);

  EXPECT_EQ (v1 / t1, ans1);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector4fTest, Length)
{
  const Vector4f v (10.0, 10.0, 10.0, 10.0);
  const Float v_length         = std::sqrt (400);
  const Float v_length_squared = 400;

  EXPECT_NEAR (v.Length (), v_length, 1e-5);
  EXPECT_NEAR (v.LengthSquared (), v_length_squared, 1e-5);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector4fTest, Normalize)
{
  Vector4f v (3.0, 3.0, 3.0, 3.0);
  const Vector4f nv1 = v.Normalized ();

  const Vector4f nv2 = v.Normalize ();
  EXPECT_EQ (nv2, v);
  EXPECT_NEAR (v.IsNormalized (), true, 1e-5);
  EXPECT_NEAR (v.Length (), static_cast <Float> (1.0), 1e-5);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector4fTest, NaN)
{
  Vector4f nan (1.0, -800, 0.0, 1e-5);
  EXPECT_EQ (nan.HasNaN (), false);

  nan[0] = std::asin (1.1);
  EXPECT_EQ (nan.HasNaN (), true);

  nan[1] = std::sqrt (-0.675);
  EXPECT_EQ (nan.HasNaN (), true);

  nan[2] = std::log (-1.5);
  EXPECT_EQ (nan.HasNaN (), true);

  nan[1] = -225 % 2;
  EXPECT_EQ (nan.HasNaN (), true);

  const Float n = std::asin (1.1);
  nan[2] = n * 100;
  EXPECT_EQ (nan.HasNaN (), true);

  nan[0] = n / n;
  EXPECT_EQ (nan.HasNaN (), true);

  nan[0] = n + 100;
  EXPECT_EQ (nan.HasNaN (), true);

  nan[1] = n - 100;
  EXPECT_EQ (nan.HasNaN (), true);

  nan[2] = n * 100;
  EXPECT_EQ (nan.HasNaN (), true);

  nan[0] = n / 100;
  EXPECT_EQ (nan.HasNaN (), true);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/

