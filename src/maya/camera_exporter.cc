#include "camera_exporter.h"
#include "attribute_utils.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/

/*
// ---------------------------------------------------------------------------
*/
auto CameraExporter::IsRenderable (const MDagPath& path) -> bool
{
    bool is_renderable = false;
    MStatus status = GetAttribute (path.node (), "renderable", &is_renderable);
    // TODO: Error check
    return is_renderable;
}
/*
// ---------------------------------------------------------------------------
*/
}
/*
// ---------------------------------------------------------------------------
*/