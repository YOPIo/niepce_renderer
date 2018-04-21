/*!
 * @file status.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/21
 * @details 
 */
#include "status.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Status::Status () :
  status_code_ (kSuccess)
{}
/*
// ---------------------------------------------------------------------------
*/
Status::Status (Status::Code code) :
  status_code_ (code)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Status::ToSuccess () -> void
{
  status_code_ = Status::kSuccess;
}
/*
// ---------------------------------------------------------------------------
*/
auto Status::ErrorString () const -> String
{
  return error_;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
