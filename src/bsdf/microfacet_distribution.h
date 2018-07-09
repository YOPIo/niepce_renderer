/*!
 * @file microfacet_distribution.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _MICROFACET_DISTRIBUTION_H_
#define _MICROFACET_DISTRIBUTION_H_
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class MicrofacetDistribution
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class MicrofacetDistribution
{
public:
  //! The default class constructor.
  MicrofacetDistribution () = default;

  //! The copy constructor of the class.
  MicrofacetDistribution (const MicrofacetDistribution& distrib) = default;

  //! The move constructor of the class.
  MicrofacetDistribution (MicrofacetDistribution&& distrib) = default;

  //! The default class destructor.
  virtual ~MicrofacetDistribution () = default;

  //! The copy assignment operator of the class.
  auto operator = (const MicrofacetDistribution& distrib)
    -> MicrofacetDistribution& = default;

  //! The move assignment operator of the class.
  auto operator = (MicrofacetDistribution&& distrib)
    -> MicrofacetDistribution& = default;

private:
  
}; // class MicrofacetDistribution
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _MICROFACET_DISTRIBUTION_H_
