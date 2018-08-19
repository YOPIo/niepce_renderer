#ifndef _UTILITIES_H_
#define _UTILITIES_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include <maya/MDagPath.h>
#include <maya/MStatus.h>
#include <maya/MFnCamera.h>
#include <maya/MItDependencyNodes.h>
#include <maya/MGlobal.h>
#include <maya/MObject.h>
#include <maya/MSelectionList.h>
#include <maya/MPlug.h>
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto ToNiepceVector3f (const MVector& v) -> Vector3f;
/*
// ---------------------------------------------------------------------------
// This function is called by GetAttribute<T>.
// ---------------------------------------------------------------------------
template <typename T>
auto GetNonNetworkedTypeAttribute (const MPlug& plug, T* value)
{
    return plug.getValue (value);
}
*/
/*
// ---------------------------------------------------------------------------
template <typename T>
auto GetAttribute
(
    const MObject& node,
    const MString& attribute_name,
    T* value
)
-> MStatus
{
    MStatus status;

    // Create dependency node from MObject.
    MFnDependencyNode dnode (node, &status);

    // Get non-networked type MPlug object.
    MPlug plug = dnode.findPlug (attribute_name, false, &status);
    if (status != MStatus::kSuccess) { return status; }

    // Get non-networked type attribute from MPlug.   
    return status;
}
*/
/*
// ---------------------------------------------------------------------------
*/
}
/*
// ---------------------------------------------------------------------------
*/
#endif // _UTILITIES_H_
