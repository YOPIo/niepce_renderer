#ifndef _CAMERA_EXPORTER_H_
#define _CAMERA_EXPORTER_H_
/*
// ---------------------------------------------------------------------------
*/
#include <maya/MDagPath.h>
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
/*
// ---------------------------------------------------------------------------
*/
{
/*
// ---------------------------------------------------------------------------
*/
class CameraExporter
{
 public:    
    //! The default constructor.
    CameraExporter () = default;

    //! The copy constructor.
    CameraExporter (const CameraExporter& exporter) = default;

    //! The move constructor.
    CameraExporter (CameraExporter&& exporter) = default;

    //! The default destructor.
    ~CameraExporter () = default;

    //! The copy assignment operator of the class.
    auto operator = (const CameraExporter& exporter) -> CameraExporter& = default;

    //! The move assignment operator of the class.
    auto operator = (CameraExporter&& exporter) -> CameraExporter& = default;

 public:
     static auto IsRenderable (const MDagPath& path) -> bool;

};
/*
// ---------------------------------------------------------------------------
*/
}
/*
// ---------------------------------------------------------------------------
*/
#endif // !_CAMERA_EXPORTER_H_

