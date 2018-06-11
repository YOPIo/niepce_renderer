#include "../../cmake_config.h"
/*
// ---------------------------------------------------------------------------
*/
#ifdef BUILD_MAYA_PLUGIN
/*
// ---------------------------------------------------------------------------
*/
#include "plugin_core.h"
#include "command.h"
#include <maya/MFnPlugin.h>
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
MStatus initializePlugin (MObject obj)
{
    MStatus status;

    // Register the niepce plugin for maya.
    MFnPlugin plugin (obj, kVendorString, kVersionString, "Any", &status);
    NIEPCE_CHECK_MSTATUS (status, "MFnPlugin error.");

    // Register a command for preparing to begin rendering as "nStartRendering".
    plugin.registerCommand ("nStartRendering", RenderCommand::Creator);

    // Import python module to register the renderer.
    const MString cmd ("import registerNiepceRenderer");
    if (MGlobal::executePythonCommand (cmd) != MStatus::kSuccess)
    {
        MGlobal::displayError ("Failed to import python modlule.");
        return status;
    }
    // Register a niepce renderer to maya via python api.
    const MString register_cmd ("registerNiepceRenderer.registerRenderer ();");
    if (MGlobal::executePythonCommand (register_cmd) != MStatus::kSuccess)
    {
        MGlobal::displayError ("Failed to register the niepce renderer.");
        return status;
    }

    return status;
}
/*
// ---------------------------------------------------------------------------
*/
MStatus uninitializePlugin (MObject obj)
{
    // Unregister renderer via python command
    MString cmd ("registerNiepceRenderer.unregisterRenderer ()");
    return MGlobal::executePythonCommand (cmd);  
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace maya
/*
// ---------------------------------------------------------------------------
*/
#endif // BUILD_MAYA_PLUGIN