/*!
 * @file triangle.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../math/point2f.h"
#include "../math/point3f.h"
#include "../shape/shape.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class TriangleMesh
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class TriangleMesh
{
public:
  //! The default class constructor.
  TriangleMesh () = default;

  //! The constructor takes positions, normals and texcoords.
  TriangleMesh
  (
   const std::vector <Point3f>&  position,
   const std::vector <Vector3f>& normals,
   const std::vector <Point2f>&  texcoords
  );

  //! The copy constructor of the class.
  TriangleMesh (const TriangleMesh& mesh) = default;

  //! The move constructor of the class.
  TriangleMesh (TriangleMesh&& mesh) = default;

  //! The default class destructor.
  virtual ~TriangleMesh () = default;

  //! The copy assignment operator of the class.
  auto operator = (const TriangleMesh& mesh) -> TriangleMesh& = default;

  //! The move assignment operator of the class.
  auto operator = (TriangleMesh&& mesh) -> TriangleMesh& = default;

public:
  /*!
   * @fn Point3f Position (unsigned)
   * @brief 
   * @param[in] 
   * @param[out] 
   * @return 
   * @exception none
   * @details
   */
  auto Position (unsigned int idx) const -> const Point3f&;

  /*!
   * @fn Vector3f& Normal (unsigned)
   * @brief 
   * @param[in] 
   * @param[out] 
   * @return 
   * @exception none
   * @details
   */
  auto Normal (unsigned int idx) const -> const Vector3f&;

  /*!
   * @fn const Texcoord (unsignd)
   * @brief 
   * @param[in] 
   * @param[out] 
   * @return 
   * @exception none
   * @details
   */
  auto Texcoord (unsigned int idx) const -> const Point2f&;


private:
  std::vector <Point3f>  positions_;
  std::vector <Vector3f> normals_;
  std::vector <Point2f>  texcoords_;
}; // class TriangleMesh
//! ----------------------------------------------------------------------------
//! @class Triangle
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Triangle final : public Shape
{
public:
  //! The default class constructor.
  Triangle () = delete;

  //! The constructor takes bool which enable to backface culling.
  Triangle
  (
   const std::array <unsigned int, 3>& position_indices,
   const std::array <unsigned int, 3>& normal_indices,
   const std::array <unsigned int, 3>& texcoord_indices,
   bool backface_culling
  );

  //! The copy constructor of the class.
  Triangle (const Triangle& tri) = default;

  //! The move constructor of the class.
  Triangle (Triangle&& tri) = default;

  //! The default class destructor.
  virtual ~Triangle () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Triangle& tri) -> Triangle& = default;

  //! The move assignment operator of the class.
  auto operator = (Triangle&& tri) -> Triangle& = default;

public:
  auto IsIntersect
  (
   const Ray& ray,
   Intersection* intersection
  )
  const noexcept -> bool override;

private:
  /*!
   * @fn const Normal (unsigned)
   * @brief Get the normal.
   * @param[in] idx unsigned integer.
   * @return 
   * @exception none
   * @details
   */
  auto Normal (unsigned int idx) const -> const Vector3f&;

  /*!
   * @fn Point3f Position ()
   * @brief Get the position as reference from triangle mesh.
   * @param [in] idx Index as unsigned integer.
   * @return Position
   * @exception none
   * @details
   */
  auto Position (unsigned int idx) const -> const Point3f&;

  /*!
   * @fn const Texcoord (unsigned)
   * @brief Get the texcoord
   * @param[in] idx unsigned integer.
   * @return 
   * @exception none
   * @details
   */
  auto Texcoord (unsigned int idx) const -> const Point2f&;

private:
  const bool backface_culling_;

  const std::shared_ptr <TriangleMesh> mesh_;
  const std::array <unsigned int, 3> position_indices_;
  const std::array <unsigned int, 3> normal_indices_;
  const std::array <unsigned int, 3> texcoord_indices_;
}; // class Triangle
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _TRIANGLE_H_
