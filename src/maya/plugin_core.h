#ifndef _PLUGIN_CORE_H_
#define _PLUGIN_CORE_H_
/*
// ---------------------------------------------------------------------------
*/
#include <maya/MGlobal.h>
#include <maya/MStatus.h>
/*
// ---------------------------------------------------------------------------
*/
#define NIEPCE_CHECK_MSTATUS(status, msg)\
{\
    MStatus s = (status);\
    if (s != MStatus::kSuccess)\
    {\
        MGlobal::displayError ("Niepce : " + MString ((msg)));\
    }\
}
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
static constexpr char kVendorString[]  = "";
static constexpr char kVersionString[] = "0.1.0";
/*
// ---------------------------------------------------------------------------
*/
}
/*
// ---------------------------------------------------------------------------
*/
#endif // _PLUGIN_CORE_H_