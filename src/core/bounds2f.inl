/*!
 * @file bounds2f.inl
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/5/5
 * @details 
 */
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
inline auto Bounds2f::Max () const noexcept -> Point2f
{
  return max_;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Bounds2f::Min () const noexcept -> Point2f
{
  return min_;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Bounds2f::SetMax (const Point2f& max) noexcept -> void
{
  max_ = max;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Bounds2f::SetMin (const Point2f& min) noexcept -> void
{
  min_ = min;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
