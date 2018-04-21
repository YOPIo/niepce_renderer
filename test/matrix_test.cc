/*
// ---------------------------------------------------------------------------
// Test file for matrix4x4
// ---------------------------------------------------------------------------
*/
#include <gtest/gtest.h>
#include "../src/algebra/matrix4x4f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class MatrixTest : public ::testing::Test {};
/*
// ---------------------------------------------------------------------------
*/
TEST_F (MatrixTest, HasNaN)
{
  Matrix4x4f m = Matrix4x4f ();

  EXPECT_EQ (m.HasNaN (), false);

  m (0, 3) = 1.5 / 0;
  EXPECT_EQ (m.HasNaN(), true);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (MatrixTest, OperatorAdd)
{
  const Matrix4x4f m1 = Matrix4x4f (1, 2, 3, 4,
                                    5, 6, 7, 8,
                                    8, 7, 6, 5,
                                    4, 3, 2, 1);
  const Matrix4x4f m2 = Matrix4x4f (8, 7, 6, 5,
                                    4, 3, 2, 1,
                                    1, 2, 3, 4,
                                    5, 6, 7, 8);
  /*
    should be
    [9, 9, 9, 9]
    [9, 9, 9, 9]
    [9, 9, 9, 9]
    [9, 9, 9, 9]
  */
  Matrix4x4f m3  = m1 + m2;
  Matrix4x4f ans (9, 9, 9, 9,
                  9, 9, 9, 9,
                  9, 9, 9, 9,
                  9, 9, 9, 9);
  EXPECT_EQ (m3, ans);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (MatrixTest, OperatorSub)
{
  const Matrix4x4f m1 = Matrix4x4f (1, 2, 3, 4,
                                    5, 6, 7, 8,
                                    8, 7, 6, 5,
                                    4, 3, 2, 1);
  const Matrix4x4f m2 = Matrix4x4f (8, 7, 6, 5,
                                    4, 3, 2, 1,
                                    1, 2, 3, 4,
                                    5, 6, 7, 8);
  /*
    should be
    [-7, -5, -3, -1]
    [ 1,  3,  5,  7]
    [ 7,  5,  3,  1]
    [-1, -3, -5, -7]
  */
  Matrix4x4f m3  = m1 - m2;
  Matrix4x4f ans (-7, -5, -3, -1,
                  1,  3,  5,  7,
                  7,  5,  3,  1,
                  -1, -3, -5, -7);
  EXPECT_EQ (m3, ans);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (MatrixTest, OperatorMul)
{
  const Matrix4x4f m1 (1, 3, 5, 7,
                       2, 4, 6, 8,
                       7, 5, 3, 1,
                       8, 6, 4, 2);
  const Matrix4x4f m2 (1, 2, 3, 4,
                       5, 6, 7, 8,
                       8, 7, 6, 5,
                       4, 3, 2, 1);

  /*
    Matrix = Matrix * Matrix
    [ 84, 76, 68,  60]   [1, 3, 5, 7]   [1, 2, 3, 4]
    [102, 94, 86,  78] = [2, 4, 6, 8] * [5, 6, 7, 8]
    [ 60, 68, 76,  84]   [7, 5, 3, 1]   [8, 7, 6, 5]
    [ 78, 86, 94, 102]   [8, 6, 4, 2]   [4, 3, 2, 1]
  */
  const Matrix4x4f m ( 84, 76, 68,  60,
                       102, 94, 86,  78,
                       60, 68, 76,  84,
                       78, 86, 94, 102);
  EXPECT_EQ (m, m1 * m2);


  /*
    Vector3 = Matrix * Vector3
    [-22]   [1, 3, 5, 7]   [-1]
    [-28] = [2, 4, 6, 8] * [-2]
    [-26]   [7, 5, 3, 1]   [-3]
    [   ]   [8, 6, 4, 2]   [  ]
  */
  const Vector3f vec3 (-1, -2, -3);
  EXPECT_EQ (m * vec3, Vector3f (-22, -28, -26));


  /*
    Vector4 = Matrix * Vector4
    [50]   [1, 3, 5, 7]   [1]
    [60] = [2, 4, 6, 8] * [2]
    [30]   [7, 5, 3, 1]   [3]
    [40]   [8, 6, 4, 2]   [4]
  */
  const Vector4f vec4 (1, 2, 3, 4);
  EXPECT_EQ (m * vec4, Vector4f (50, 60, 30, 40));


  /*
    Point3 = Matrix * Point3
    [18]   [1, 3, 5, 7]   [-1]
    [20] = [2, 4, 6, 8] * [ 2]
    [-2]   [7, 5, 3, 1]   [-3]
    [  ]   [8, 6, 4, 2]   [  ]
  */
  const Point3f p3 (-1, 2, -3);
  EXPECT_EQ (m * p3, Point3f (18, 20, -2));


  /*
    Point4 = Matrix * Point4
    [-18]   [1, 3, 5, 7]   [ 1]
    [-20] = [2, 4, 6, 8] * [-2]
    [  2]   [7, 5, 3, 1]   [ 3]
    [  0]   [8, 6, 4, 2]   [-4]
  */
  const Point4f p4 (1, -2, 3, -4);
  EXPECT_EQ (m * p4, Point4f (-18, -20, 2, 0));


  /*
    Normal3 = Matrix * Normal3
    [3]   [1, 3, 5, 7]   [0]
    [4] = [2, 4, 6, 8] * [1]
    [5]   [7, 5, 3, 1]   [0]
    [ ]   [8, 6, 4, 2]   [ ]
  */
  const Normal3f n (3, 4, 5);
  EXPECT_EQ (m * n, Normal3f (0, 1, 0));


  /*
    Matrix = Matrix * real
    [ 3,  9, 15, 21]   [1, 3, 5, 7]
    [ 6, 12, 18, 24] = [2, 4, 6, 8] * 3;
    [21, 15,  9,  3]   [7, 5, 3, 1]
    [24, 18, 12,  6]   [8, 6, 4, 2]
  */
  const Matrix4x4f mt ( 3,  9, 15, 21,
                        6, 12, 18, 24,
                        21, 15,  9,  3,
                        24, 18, 12,  6);
  EXPECT_EQ (mt, m * 3);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (MatrixTest, Inverse)
{
  const Matrix4x4f mat (3, 1, 1, 2,
                        5, 1, 3, 4,
                        2, 0, 1, 0,
                        1, 3, 2, 1);

  /*
    Inversed:
    A * A^-1 = A^-1 * A = I
  */
  const Matrix4x4f inv = Inverse (mat);
  const Matrix4x4f i1  = mat * inv;
  const Matrix4x4f i2  = inv * mat;
  const Matrix4x4f i   = Matrix4x4f::Identity ();
  const Float     thr = 0.0001;

  auto EXPECT_EQ_WITH_ERROR = []
      (
          const Matrix4x4f& rhs,
          const Matrix4x4f& lhs,
          Float threashold
       )
      -> void
      {
        for (uint32_t r = 0; r < 4; ++r)
        {
          for (uint32_t l = 0; l < 4; ++l)
          {
            if (std::abs (rhs (r, l) - lhs (r, l)) >= threashold)
            {
              EXPECT_TRUE (false);
            }
          }
        }
        EXPECT_TRUE (true);
      };

  EXPECT_EQ_WITH_ERROR (i1, i2, thr);
  EXPECT_EQ_WITH_ERROR (i1,  i, thr);
}
/*
// ---------------------------------------------------------------------------
*/
TEST_F (MatrixTest, Identity)
{
  const Matrix4x4f identity (1, 0, 0, 0,
                             0, 1, 0, 0,
                             0, 0, 1, 0,
                             0, 0, 0, 1);
  const Matrix4x4f i = Matrix4x4f::Identity ();

  EXPECT_EQ (i, identity);
}
/*
// ---------------------------------------------------------------------------
*/
}
/*
// ---------------------------------------------------------------------------
*/
