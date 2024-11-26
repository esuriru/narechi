include(${NRC_CMAKE_DIR}/EmbedAsset.cmake)

set(NARECHI_LAUNCHER_SOURCES
    "src/main.cpp"

    "src/project.cpp"
    "src/project_asset.cpp"

    "src/editor_layer.cpp"
    "src/launcher_layer.cpp"

    "src/panels/content_browser_panel.cpp"
    "src/panels/sprite_import_panel.cpp"
    "src/panels/scene_view_panel.cpp"
    "src/panels/build_panel.cpp"
    "src/panels/editor_panel.cpp"
)

 
add_executable(narechi-launcher ${NARECHI_LAUNCHER_SOURCES})

add_dependencies(narechi-launcher narechi-player)

set(NRC_LAUNCHER_BIN_DIR ${CMAKE_CURRENT_BINARY_DIR})

set(nrc_player_chunk_id 0)

while(nrc_player_chunk_id LESS ${NRC_PLAYER_CHUNK_COUNT})
    set(current_player_chunk_file "${CMAKE_CURRENT_BINARY_DIR}/narechi_player${nrc_player_chunk_id}.cpp")

    if(NOT EXISTS ${current_player_chunk_file})
        file(WRITE ${current_player_chunk_file} "")
    endif()

    target_sources(narechi-launcher PRIVATE ${current_player_chunk_file})

    math(EXPR nrc_player_chunk_id "${nrc_player_chunk_id} + 1")
endwhile()

target_link_libraries(
    narechi-launcher
    PUBLIC
    narechi-engine
)

target_include_directories(narechi-launcher PRIVATE
    "include")

target_compile_definitions(narechi-launcher PRIVATE
    "NRC_PLATFORM_WINDOWS"
    "NRC_DEBUG")

# Copy asset dependencies
add_custom_command(
    TARGET narechi-launcher PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Copy library dependencies into the exe
add_custom_command(TARGET narechi-launcher POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_RUNTIME_DLLS:narechi-launcher>
    $<TARGET_FILE:narechi-launcher>
    $<TARGET_FILE_DIR:narechi-launcher>
    COMMAND_EXPAND_LISTS
)

embed_binary_to_byte_array(narechi-launcher "${NRC_ASSET_DIR}/file_icon.png")
embed_binary_to_byte_array(narechi-launcher "${NRC_ASSET_DIR}/folder_icon.png")