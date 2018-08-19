/*
// ---------------------------------------------------------------------------
// Test file for matrix4x4
// ---------------------------------------------------------------------------
*/
#include <gtest/gtest.h>
#include "../src/core/matrix4x4f.h"
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
int main () { return 0; }
/*
// ---------------------------------------------------------------------------
*/
}
/*
// ---------------------------------------------------------------------------
*/
