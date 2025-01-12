include(${NRC_CMAKE_DIR}/EmbedAsset.cmake)

set(NARECHI_SOURCES
    "src/core/logger.cpp"
    "src/core/app.cpp"
    "src/core/window.cpp"
    "src/core/layer_stack.cpp"
    "src/asset/asset.cpp"
    "src/asset/scene_asset.cpp"
    "src/asset/sprite_asset.cpp"
    "src/asset/component_def_asset.cpp"
    "src/file/nfd_context.cpp"
    "src/gui/window.cpp"
    "src/gui/element.cpp"
    "src/gui/text_element.cpp"
    "src/gui/space_element.cpp"
    "src/gui/table_element.cpp"
    "src/gui/text_input_element.cpp"
    "src/gui/float_input_element.cpp"
    "src/gui/button_element.cpp"
    "src/gui/image_button_element.cpp"
    "src/gui/menu_bar.cpp"
    "src/gui/image_element.cpp"
    "src/gui/scope/table_scope.cpp"
    "src/gui/scope/tree_node_scope.cpp"
    "src/imgui/imgui_context.cpp"
    "src/imgui/imgui_window.cpp"
    "src/imgui/imgui_text_element.cpp"
    "src/imgui/imgui_table_element.cpp"
    "src/imgui/imgui_space_element.cpp"
    "src/imgui/imgui_text_input_element.cpp"
    "src/imgui/imgui_float_input_element.cpp"
    "src/imgui/imgui_button_element.cpp"
    "src/imgui/imgui_image_button_element.cpp"
    "src/imgui/imgui_menu_bar.cpp"
    "src/imgui/imgui_image_element.cpp"
    "src/imgui/scope/imgui_table_scope.cpp"
    "src/imgui/scope/imgui_tree_node_scope.cpp"
    "src/graphics/graphics_context.cpp"
    "src/graphics/renderer_api.cpp"
    "src/graphics/image.cpp"
    "src/graphics/render_command.cpp"
    "src/graphics/framebuffer.cpp"
    "src/graphics/texture2d.cpp"
    "src/graphics/vertex_buffer.cpp"
    "src/graphics/vertex_array.cpp"
    "src/graphics/index_buffer.cpp"
    "src/graphics/render2d.cpp"
    "src/graphics/handle.cpp"
    "src/graphics/buffer_element.cpp"
    "src/graphics/shader.cpp"
    "src/graphics/sprite.cpp"
    "src/scene/scene.cpp"
    "src/platform/win32/win32window.cpp"
    "src/utils/time_utils.cpp"
    "src/utils/file_utils.cpp"
)

if(${NRC_RENDERER_API} STREQUAL "opengl")
    set(RENDERER_API_SOURCES
        "src/platform/opengl/opengl_context.cpp"
        "src/platform/opengl/opengl_renderer_api.cpp"
        "src/platform/opengl/opengl_texture2d.cpp"
        "src/platform/opengl/opengl_vertex_buffer.cpp"
        "src/platform/opengl/opengl_vertex_array.cpp"
        "src/platform/opengl/opengl_index_buffer.cpp"
        "src/platform/opengl/opengl_shader.cpp"
        "src/platform/opengl/opengl_framebuffer.cpp"
    )
elseif(${NRC_RENDERER_API} STREQUAL "vulkan")
    set(RENDERER_API_SOURCES
        "src/platform/vulkan/vulkan_renderer_api.cpp"
        "src/platform/vulkan/vulkan_shader.cpp"
        "src/platform/vulkan/vulkan_framebuffer.cpp"
    )
else()
    error("Unsupported Renderer API: " ${NRC_RENDERER_API})
endif()

add_library(narechi-engine SHARED ${NARECHI_SOURCES} ${RENDERER_API_SOURCES})

target_link_libraries(narechi-engine PRIVATE glfw)
target_link_options(narechi-engine PUBLIC -static-libstdc++)

target_include_directories(narechi-engine PUBLIC "include")

# TODO - Build static or shared setting
target_compile_definitions(narechi-engine PRIVATE "NOMINMAX")
target_compile_definitions(
    narechi-engine INTERFACE "IMGUI_DISABLE_OBSOLETE_FUNCTIONS"
)

if(WIN32)
    target_compile_definitions(
        narechi-engine PRIVATE "NRC_PLATFORM_WINDOWS" "NRC_DEBUG"
                               "NRC_BUILD_DLL"
    )
else()

endif()

if(${NRC_RENDERER_API} STREQUAL "opengl")
    target_compile_definitions(narechi-engine PRIVATE "NRC_RENDERER_API_OPENGL")
elseif(${NRC_RENDERER_API} STREQUAL "vulkan")
    target_compile_definitions(narechi-engine PRIVATE "NRC_RENDERER_API_VULKAN")
else()
    error("Unsupported Renderer API: " ${NRC_RENDERER_API})
endif()

embed_text_to_std_string(
    narechi-engine "${NRC_ASSET_DIR}/shaders/texture_v.glsl"
)
embed_text_to_std_string(
    narechi-engine "${NRC_ASSET_DIR}/shaders/texture_f.glsl"
)

if(NOT DEFINED NRC_DISABLE_BUILD_EMBED)
    set(NRC_ENGINE_CHUNK_COUNT 1)
    set(NRC_ENGINE_CHUNK_COUNT
        ${NRC_ENGINE_CHUNK_COUNT}
        PARENT_SCOPE
    )
    message(STATUS "Engine to be packed in ${NRC_ENGINE_CHUNK_COUNT} chunks")

    add_custom_command(
        TARGET narechi-engine
        POST_BUILD
        COMMAND
            ${CMAKE_COMMAND} -DNRC_PLAYER_BINARY=$<TARGET_FILE:narechi-engine>
            -DNRC_SOURCE_DIR=${CMAKE_SOURCE_DIR}
            -DNRC_LAUNCHER_BIN_DIR=$<TARGET_FILE_DIR:narechi-launcher>
            -DNRC_PLAYER_CHUNK_COUNT=${NRC_ENGINE_CHUNK_COUNT} -P
            ${NRC_CMAKE_DIR}/scripts/EmbedPlayer.cmake
    )
else()
endif()
