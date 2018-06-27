#ifndef _RENDER_COMMAND_H_
#define _RENDER_COMMAND_H_
/*
// ---------------------------------------------------------------------------
*/
#include <maya/MPxCommand.h>
#include <maya/MGlobal.h>
#include <maya/MDagPath.h>
#include <maya/MFnCamera.h>
#include <maya/MFloatMatrix.h>
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*!
 * @class RenderCommand
 * @brief 
 */
class RenderCommand : public MPxCommand
{
public:
    //! The default class constructor.
    RenderCommand () = default;

    //! The copy constructor of the class.
    RenderCommand (const RenderCommand& camera) = default;

    //! The move constructor of the class.
    RenderCommand (RenderCommand&& camera) = default;

    //! The default class destructor.
    virtual ~RenderCommand () = default;

    //! The copy assignment operator of the class.
    auto operator = (const RenderCommand& camera) -> RenderCommand& = default;

    //! The move assignment operator of the class.
    auto operator = (RenderCommand&& camera) -> RenderCommand& = default;

public:
    /*!
    * @fn void* Creator ()
    * @brief Called by MFnPlugin.registerRenderCommand()
    * @return void*
    * @exception none
    * @details
    */
    static auto Creator () -> void*;

    /*!
    * @fn MStatus doIt ()
    * @brief Definition of RenderCommand.
    * @return MStatus
    * @exception none
    * @details
    */
    auto doIt (const MArgList& args) -> MStatus override final;
    
private:
    static constexpr char kCommandName[] = "nStartRendering";
};
/*
// ---------------------------------------------------------------------------
*/
}
/*
// ---------------------------------------------------------------------------
*/
#endif // _RenderCommand_H_
