/*
// ---------------------------------------------------------------------------
*/
#include <gtest/gtest.h>
#include "../src/core/vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class Vector3fTest : public ::testing::Test {};
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector3fTest, DefaultConstructor)
{
  const Vector3f v;
  EXPECT_EQ (v[0], 0);
  EXPECT_EQ (v[1], 0);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector3fTest, TwoArgConstructor)
{
  const Float x = 1.0;
  const Float y = -5;
  const Float z = 999.0;
  Vector3f v (x, y, z);
  EXPECT_EQ (v.At (0), x);
  EXPECT_EQ (v.At (1), y);
  EXPECT_EQ (v.At (2), z);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector3fTest, OneArgConstructor)
{
  const Float x = 3.10;;
  Vector3f v (x);
  EXPECT_EQ (v.X (), x);
  EXPECT_EQ (v.Y (), x);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector3fTest, Setter)
{
  const int x = 3;
  const int y = -1;
  const int z = 89;

  Vector3f v;
  v.SetX (x);
  v.SetY (y);
  v.SetZ (z);
  EXPECT_EQ (v.X (), x);
  EXPECT_EQ (v.Y (), y);
  EXPECT_EQ (v.Z (), z);

  v = -v;
  EXPECT_EQ (v.X (), -x);
  EXPECT_EQ (v.Y (), -y);
  EXPECT_EQ (v.Z (), -z);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector3fTest, Comparison)
{
  const Vector3f v1 (-1.0, 1.5, -0.1);
  const Vector3f v2 (-1.0, 1.5, -0.1);
  const Vector3f v3 (-0.9, 1.5, 25.3);

  EXPECT_EQ (v1, v2);
  EXPECT_NE (v1, v3);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector3fTest, Negative)
{
  const Float x = 8.5;
  const int   y = -8;
  const Float z = -0.01;
  const Vector3f v (x, y, z);

  EXPECT_EQ (Vector3f (-x, -y, -z), -v);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector3fTest, Add)
{
  const Vector3f v1 (-1.0,  5.0, -19.2);
  const Vector3f v2 (20.3, -8.9,  -8.1);

  const Vector3f ans1 (v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);

  EXPECT_EQ (v1 + v2, ans1);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector3fTest, Sub)
{
  const Vector3f v1 (-1.0,  5.0, -19.2);
  const Vector3f v2 (20.3, -8.9,  -8.1);

  const Vector3f ans1 (v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);

  EXPECT_EQ (v1 - v2, ans1);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector3fTest, Mul)
{
  const Vector3f v1 (-1.0,  5.0, -19.2);
  const Vector3f v2 (20.3, -8.9,  -8.1);
  const Float t = 8.0;

  const Vector3f ans1 (v1[0] * t, v1[1] * t, v1[2] * t);
  const Vector3f ans2 (v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);

  EXPECT_EQ (v1 * t,  ans1);
  EXPECT_EQ (Multiply (v1, v2), ans2);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector3fTest, Div)
{
  const Vector3f v1 (4.0, 9.0, -15.3);
  const Float    t1 (2);

  const Vector3f ans1 (v1[0] / t1, v1[1] / t1, v1[2] / t1);

  EXPECT_EQ (v1 / t1, ans1);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector3fTest, Length)
{
  const Vector3f v (10.0, 10.0, 10.0);
  const Float v_length         = std::sqrt (300);
  const Float v_length_squared = 300;

  EXPECT_NEAR (v.Length (), v_length, 1e-5);
  EXPECT_NEAR (v.LengthSquared (), v_length_squared, 1e-5);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (Vector3fTest, Normalize)
{
  Vector3f v (3.0, 3.0, 3.0);
  const Vector3f nv1 = v.Normalize ();

  const Vector3f nv2 = v.Normalize ();
  EXPECT_EQ (nv2, v);
  EXPECT_NEAR (v.Length (), static_cast <Float> (1.0), 1e-5);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/

