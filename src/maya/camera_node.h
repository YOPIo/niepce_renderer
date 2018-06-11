#ifndef _CAMERA_NODE_H_
#define _CAMERA_NODE_H_
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class CameraNode : public 
{
    //! The default CameraNode constructor.
    CameraNode () = default;

    //! The default CameraNode destructor.
    ~CameraNode () = default;

    //! The move constructor of the class.
    CameraNode (CameraNode&& camera) = default;

    //! The default class destructor.
    virtual ~CameraNode () = default;

    //! The copy assignment operator of the class.
    auto operator = (const CameraNode& camera) -> CameraNode& = default;

    //! The move assignment operator of the class.
    auto operator = (CameraNode&& camera) -> CameraNode& = default;
};
/*
// ---------------------------------------------------------------------------
*/
}
/*
// ---------------------------------------------------------------------------
*/
#endif // _CAMERA_NODE_H_

