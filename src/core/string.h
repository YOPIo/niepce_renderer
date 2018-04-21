/*!
 * @file string.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/21
 * @details 
 */
#ifndef _STRING_H_
#define _STRING_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class String
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class String
{
public:
  //! The default class constructor.
  /*!
   * It initialize internal string to empty.
   */
  String ();

  //! The constructor that takes std::string
  String (const std::string& str);

  //! The copy constructor of the class.
  String (const String& str) = default;

  //! The move constructor of the class.
  String (String&& str) = default;

  //! The default class destructor.
  virtual ~String () = default;

public:
  //! The copy assignment operator of the class.
  auto operator = (const String& str) -> String& = default;

  //! The move assignment operator of the class.
  auto operator = (String&& str) -> String& = default;

public:
  //! @fn uint32_t Length ()
  //! @brief Return the length of string buffer in this string instance.
  //! @return The length of string buffer.
  //! @exception none
  //! @details
  auto Length () const -> uint32_t;

private:
  std::string str_;
}; // class String
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _STRING_H_
