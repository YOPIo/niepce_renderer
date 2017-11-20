#ifndef _CONSTANT_TEXTURE_H_
#define _CONSTANT_TEXTURE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "texture.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
template <typename DataType> class ConstantTexure;
/*
// ---------------------------------------------------------------------------
*/
template <typename DataType>
auto CreateConstantTexture (const DataType& data) -> TexturePtr <DataType>;
/*
// ---------------------------------------------------------------------------
*/
template <typename ReturnType>
class ConstantTexture : public Texture<ReturnType>
{
  /* ConstantTexture public Constructors */
 public:
  ConstantTexture ();
  ConstantTexture (const ReturnType& value);


  /* ConstantTexture public destructor */
public:
  virtual ~ConstantTexture () = default;


  /* ConstantTexture public operators*/
public:
  ConstantTexture (const ConstantTexture&  texture) = default;
  ConstantTexture (      ConstantTexture&& texture) = default;

  auto operator = (const ConstantTexture&  texture) -> ConstantTexture&
      = default;
  auto operator = (      ConstantTexture&& texture) -> ConstantTexture&
      = default;


  /* ConstantTexture public methods  */
 public:
  auto Evaluate (const SurfaceInteraction& si) const
    -> ReturnType override final;

  auto ToString () const -> std::string override final;


  /* ConstantTexture private data */
 private:
  ReturnType value_;

}; // class ConstantTexture
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _CONSTANT_TEXTURE_H_
