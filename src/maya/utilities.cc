#include "utilities.h"
/*
// ---------------------------------------------------------------------------
*/
#include <maya/MStatus.h>
#include <maya/MFnCamera.h>
#include <maya/MItDependencyNodes.h>
#include <maya/MGlobal.h>
#include <maya/MPlug.h>
/*
// ---------------------------------------------------------------------------
*/
#include "../core/transform.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto FindRenderableCamera (MDagPath* path) -> MStatus
{
    // Get all camera in the scene
    MItDependencyNodes cameras_nodes (MFn::kCamera);

    // Loop over the camera in the scene
    for (; !cameras_nodes.isDone (); cameras_nodes.next ())
    {
        MFnCamera camera (cameras_nodes.thisNode ());
        // Check renderable parameter as true or not.
        if (camera.findPlug ("renderable").asBool ())
        {
            camera.getPath (*path);
            MGlobal::displayInfo (path->fullPathName ());
            return MStatus::kSuccess;
        }
    }
    return MStatus::kFailure;
}
/*
// ---------------------------------------------------------------------------
*/
}
/*
// ---------------------------------------------------------------------------
*/