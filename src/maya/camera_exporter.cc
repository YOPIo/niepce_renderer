#include "camera_exporter.h"
#include "attribute_utils.h"
#include "utilities.h"
#include "../core/vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
CameraExporter::CameraExporter (const MString& filename) :
    document_ (filename.asChar ())
{}
/*
// ---------------------------------------------------------------------------
*/
auto CameraExporter::Export () -> MStatus
{
    MStatus status;

    // Get renderable camera path.
    MDagPath path;
    status = FindRenderableCamera (&path);
    if (status != MStatus::kSuccess)
    {
        MGlobal::displayError ("Renderalbe camera was not found.");
        return status;
    }

    // Reference renderable camera.
    const MFnCamera camera (path, &status);

    // Get camera position, lookat and up.
    const auto posi = ToNiepceVector3f (camera.eyePoint (MSpace::kWorld));
    const auto look = ToNiepceVector3f (camera.viewDirection (MSpace::kWorld));
    const auto up   = ToNiepceVector3f (camera.upDirection (MSpace::kWorld));        
    
    // Get size of rendering resolution.
    const auto resolution = Resolution ();

    // Get length of diagonal of film. [mm]
    const auto diagonal = camera.findPlug ("niDiagonalLength");

    // Get field of view. [degree]
    const auto fov = camera.findPlug ("niFieldOfView");

    // Get focus distance. [m]
    const auto focus_dist = camera.findPlug ("niFocusDistance");

    // Get lens aperture. [mm]
    const auto aperture = camera.findPlug ("niLensAperture");

    // Get camera type. (pinhole or realistic)
    const auto type = camera.findPlug ("niCameraType");
}
/*
// ---------------------------------------------------------------------------
*/
auto CameraExporter::FindRenderableCamera (MDagPath* path) -> MStatus
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
auto CameraExporter::Resolution () -> Bounds2f
{
    MSelectionList list;
    MGlobal::getSelectionListByName ("defaultResolution", list);

    if (list.length () > 0)
    {
        MObject obj;
        list.getDependNode (0, obj);
        MFnDependencyNode dnode (obj);

        // Get resolution width and height attributes from dependency node.
        auto width  = dnode.findPlug ("width");
        auto height = dnode.findPlug ("height");
        return Bounds2f (width.asFloat (), height.asFloat ());
    }

    // Failed to get resolution from maya.
    return Bounds2f (600, 400);
}
/*
// ---------------------------------------------------------------------------
*/
}
/*
// ---------------------------------------------------------------------------
*/