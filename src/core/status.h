/*!
 * @file status.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/21
 * @details 
 */
#ifndef _STATUS_H_
#define _STATUS_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
#include "string.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Status
//! @brief Niepce renderer status codes.
//! @details x
//! ----------------------------------------------------------------------------
class Status
{
public:
  /*!
   * @enum StatusCode
   * @brief Avaliable status codes.
   * @details 
   */
  enum Code
  {
    kSuccess,          /*!< The operation was successful. */
    kFailure,          /*!< The operation failed. */
    kInvalidParameter, /*!< An invalid parameter was provided. */
    kNotFound,         /*!< Something could not found. */
    kNotImplemented,   /*!<  */
  };

public:
  //! The default class constructor.
  /*!
   * It initialize StatusCode to kSuccess.
   */
  Status ();

  //! The constructor that takes a Status::StatusCode.
  Status (Code code);

  //! The copy constructor of the class.
  Status (const Status& status) = default;

  //! The move constructor of the class.
  Status (Status&& status) = default;

  //! The default class destructor.
  virtual ~Status () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Status& status) -> Status& = default;

  //! The move assignment operator of the class.
  auto operator = (Status&& status) -> Status& = default;

public:
  //! @fn std ErrorString ()
  //! @brief Return the error logs if internal status code is kFailure.
  //! @return Error string.
  //! @exception none
  //! @details 
  auto ErrorString () const -> String;

  //! @fn void ToSuccess ()
  //! @brief Make internal status code to kSuccess.
  //! @return void
  //! @exception none
  //! @details 
  auto ToSuccess () -> void;

private:
  Code   status_code_;
  String error_;
}; // class Status
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _STATUS_H_
