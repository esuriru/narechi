set(NARECHI_LAUNCHER_SOURCES
    "src/main.cpp"

    "src/project.cpp"
    "src/project_asset.cpp"

    "src/editor_layer.cpp"
    "src/launcher_layer.cpp"

    "src/panels/content_browser_panel.cpp"
)

add_executable(narechi-launcher ${NARECHI_LAUNCHER_SOURCES})

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