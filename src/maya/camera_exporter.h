#ifndef _CAMERA_EXPORTER_H_
#define _CAMERA_EXPORTER_H_
/*
// ---------------------------------------------------------------------------
*/
#include <maya/MDagPath.h>
#include <maya/MItDependencyNodes.h>
#include <maya/MFnCamera.h>
#include <maya/MGlobal.h>
#include <maya/MSelectionList.h>
/*
// ---------------------------------------------------------------------------
*/
#include "../core/bounds2f.h"
#include "../ext/tinyxml2/tinyxml2.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class CameraExporter
{
 public:    
    //! The default constructor.
    CameraExporter (const MString& filename);

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
    //! 
    auto Export () -> MStatus;

 public:     
     static auto FindRenderableCamera (MDagPath* dag_path) -> MStatus;
     static auto Resolution () -> Bounds2f;

 private:
    tinyxml2::XMLDocument document_;
};
/*
// ---------------------------------------------------------------------------
*/
}
/*
// ---------------------------------------------------------------------------
*/
#endif // !_CAMERA_EXPORTER_H_

