message(STATUS "Fetching imgui-docking")

FetchContent_MakeAvailable(imgui)

set(IMGUI_SRC_FILES
    "imgui.cpp" "imgui_draw.cpp" "imgui_demo.cpp" "imgui_tables.cpp"
    "imgui_widgets.cpp" "misc/cpp/imgui_stdlib.cpp"
)
list(TRANSFORM IMGUI_SRC_FILES PREPEND ${imgui_SOURCE_DIR}/)

# For now, we will only be using GLFW, hence, we do not care about the API for
# this as Vulkan and OpenGL can both use GLFW
if(${NRC_RENDERER_API} STREQUAL "opengl")
    set(IMGUI_BACKEND_SRC_FILES "backends/imgui_impl_glfw.cpp"
                                "backends/imgui_impl_opengl3.cpp"
    )
elseif(${NRC_RENDERER_API} STREQUAL "vulkan")
    set(IMGUI_BACKEND_SRC_FILES "backends/imgui_impl_glfw.cpp"
                                "backends/imgui_impl_vulkan.cpp"
    )
else()
    error("Unsupported Renderer API: " ${NRC_RENDERER_API})
endif()
list(TRANSFORM IMGUI_BACKEND_SRC_FILES PREPEND ${imgui_SOURCE_DIR}/)

add_library(imgui STATIC ${IMGUI_SRC_FILES} ${IMGUI_BACKEND_SRC_FILES})

target_include_directories(
    imgui PRIVATE ${imgui_SOURCE_DIR} ${GLFW_SOURCE_DIR}/include
)

set(NRC_IMGUI_SOURCE_DIR
    ${imgui_SOURCE_DIR}
    PARENT_SCOPE
)
