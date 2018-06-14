#include "scene_exporter.h"
#include "utilities.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
SceneExporter::SceneExporter (const char* filename)
{
    MStatus status;

    // Find a renderable camera's dag node.
    MDagPath dag_path;
     status = FindRenderableCamera (&dag_path);
    
    
}
/*
// ---------------------------------------------------------------------------
*/
}
/*
// ---------------------------------------------------------------------------
*/