cmake_minimum_required (VERSION 3.0)

# Find autodesk maya
if (Maya_FOUND)
    set (SOURCE_FILES "plugin_main.cc"
					  "render_command.cc"
					  "utilities.cc"
					  "camera_exporter.cc"
					  "attribute_utils.cc"
					  "scene_exporter.cc")

    add_library (${PROJECT_NAME} SHARED ${SOURCE_FILES})
    target_link_libraries (${PROJECT_NAME}
							Renderer
							Scene
							Texture
							Material
							Camera
							Bsdf
							Shape
							Primitive
							Sampler
							Random
							Ext
							Core
							Maya::Maya)
    target_include_directories (${PROJECT_NAME} PRIVATE Maya::Maya)
    MAYA_PLUGIN (${PROJECT_NAME})
else ()
    message (STATUS "Could not found autodesk maya.")
endif ()