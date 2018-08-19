#include "render_command.h"
/*
// ---------------------------------------------------------------------------
*/
#include "camera_exporter.h"
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

    CameraExporter cexporter ("test.xml");
    cexporter.Export ();
    MGlobal::displayInfo ("Rendering start.");

    return MStatus::kSuccess;
}
/*
// ---------------------------------------------------------------------------
*/
}
/*
// ---------------------------------------------------------------------------
*/