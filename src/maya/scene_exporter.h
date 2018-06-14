#ifndef _SCENE_EXPORTER_H_
#define _SCENE_EXPORTER_H_
/*
// ---------------------------------------------------------------------------
*/
#include "camera_exporter.h"
/*
// ---------------------------------------------------------------------------
*/
#include <string>
/*
// ---------------------------------------------------------------------------
*/
#include "../ext/tinyxml2/tinyxml2.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class SceneExporter
{
public:
    //! The default constructor.
    SceneExporter () = delete;

    //! The constructor takes filename.
    SceneExporter (const char* filename);

    //! The default copy constructor.
    SceneExporter (const SceneExporter& exporter) = default;

    //! The default move constructor.
    SceneExporter (SceneExporter&& exporter) = default;

    //! The default destructor.
    ~SceneExporter () = default;

    //! The default copy assignment operator.
    auto operator = (const SceneExporter& exporter) -> SceneExporter& = default;

    //! The default move assignment operator.
    auto operator = (SceneExporter&& exporter) -> SceneExporter& = default;

public:

private:
    std::string filename_;
    tinyxml2::XMLDocument xml_;

    CameraExporter camera_;
};
/*
// ---------------------------------------------------------------------------
*/
}
/*
// ---------------------------------------------------------------------------
*/
#endif // !_SCENE_EXPORTER_H_
