#include "render_command.h"
#include "utilities.h"
#include <maya/MGlobal.h>
#include <maya/MDagPath.h>
#include <maya/MFnCamera.h>
#include <maya/MFloatMatrix.h>

#include "../core/matrix4x4f.h"
#include "../core/transform.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto RenderCommand::Creator () -> void*
{
    return new RenderCommand ();
}
/*
// ---------------------------------------------------------------------------
*/
auto RenderCommand::doIt (const MArgList& args) -> MStatus
{
    MStatus status;
        
    // Find a camera for using rendering.
    MDagPath path;
    status = FindRenderableCamera (&path);
    if (status == MStatus::kFailure)
    {
        MGlobal::displayError ("Could not find renderable camera.");
        return MStatus::kFailure;
    }
    // Get Camera DAG node.
    MFnCamera camera (path);
    MFloatMatrix matrix = camera.projectionMatrix (&status);


    return MStatus::kSuccess;
}
/*
// ---------------------------------------------------------------------------
*/
}
/*
// ---------------------------------------------------------------------------
*/