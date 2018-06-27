#include "extension attributes.h"
#include "plugin_core.h"
/*
// ---------------------------------------------------------------------------
*/
#include <maya/MNodeClass.h>
#include <maya/MDGModifier.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnEnumAttribute.h>
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto RegisterCameraExtensionAttributes () -> void
{
    MStatus status;
    MNodeClass node ("camera");
    MDGModifier modifier;
    MObject attr;
    
    // Create enum attribute, pinhole or realistic camera.
    MFnEnumAttribute enum_attr;
    attr = enum_attr.create ("niCameraEnum", // Full name  
                             "niCameraEnum", // Brief name
                             0,              // Default
                             &status);
    enum_attr.addField ("Pinhole", 0);
    enum_attr.addField ("Realistic", 1);
    enum_attr.addToCategory (kCategory);
    modifier.addExtensionAttribute (node, attr);

    // Create float attribute (Film physical lenght) [mm]
    MFnNumericAttribute diagonal;
    attr = diagonal.create ("niDiagonalLength",            // Full name
                            "niDiagonalLength",            // Brief name
                            MFnNumericData::Type::kDouble, // Data type
                            0,                             // Default
                            &status);
    diagonal.addToCategory (kCategory);
    diagonal.setMin (0);
    diagonal.setMax (100);
    modifier.addExtensionAttribute (node, attr);

    // Create float attribute (Field of view). [degree]
    MFnNumericAttribute fov;            // Field of view. [degree]
    attr = fov.create ("niFieldOfView",               // Full name
                       "niFieldOfView",               // Brief name
                       MFnNumericData::Type::kDouble, // Data type
                       45.0,                          // Default
                       &status); 
    fov.addToCategory (kCategory);
    fov.setMin (0);
    fov.setMax (175);
    modifier.addExtensionAttribute (node, attr);
    
    // Create double attribute (Focus distance) [m]
    MFnNumericAttribute focus_distance;
    attr = focus_distance.create ("niFocusDistance",             // Full name
                                  "niFocusDistance",             // Brief name
                                  MFnNumericData::Type::kDouble, // Data type
                                  1,                             // Default
                                  &status);
    focus_distance.addToCategory (kCategory);
    focus_distance.setMin (0);
    focus_distance.setMax (300);
    modifier.addExtensionAttribute (node, attr);

    // Create double attribute (Lens aperture) [mm]
    MFnNumericAttribute aperture;
    attr = aperture.create ("niLensAperture",              // Full name
                            "niLensAperture",              // Brief name
                            MFnNumericData::Type::kDouble, // Data type
                            5,                             // Default
                            &status);
    aperture.addToCategory (kCategory);
    aperture.setMin (0);
    aperture.setMax (500);
    modifier.addExtensionAttribute (node, attr);
}
/*
// ---------------------------------------------------------------------------
*/
auto RegisterExtensionAttributes () -> void
{
    MStatus status;
    MNodeClass node ("camera");
    MDGModifier modifier;
    MFnNumericAttribute num_attr;

    auto attr = num_attr.create ("niLensAperture",
                                 "niLensAperture",
                                 MFnNumericData::Type::kFloat,
                                 0, // default
                                 &status);

    num_attr.addToCategory (kCategory);

    modifier.addExtensionAttribute (node, attr);
}
/*
// ---------------------------------------------------------------------------
*/
}
/*
// ---------------------------------------------------------------------------
*/
