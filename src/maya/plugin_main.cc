#include "../../cmake_config.h"
/*
// ---------------------------------------------------------------------------
*/
#include "plugin_core.h"
#include "render_command.h"
#include "extension attributes.h"
#include <maya/MFnPlugin.h>
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
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
    plugin.registerCommand ("niStartRendering", RenderCommand::Creator);

    /*   
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
    */

    RegisterCameraExtensionAttributes ();
    // RegisterExtensionAttributes ();

    return MStatus::kSuccess;
}
/*
// ---------------------------------------------------------------------------
*/
MStatus uninitializePlugin (MObject obj)
{
    /*
    // Unregister renderer via python command
    MString cmd ("registerNiepceRenderer.unregisterRenderer ()");
    auto res = MGlobal::executePythonCommand (cmd);
    */


    return MStatus::kSuccess;
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace maya