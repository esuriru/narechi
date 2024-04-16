set(NARECHI_LAUNCHER_SOURCES
    "src/editor_app.hpp"
    "src/editor_app.cpp"

    "src/editor_layer.hpp"
    "src/editor_layer.cpp"
)


add_executable(narechi-launcher ${NARECHI_LAUNCHER_SOURCES})

target_link_libraries(
    narechi-launcher
    PUBLIC 
    narechi-engine
)

target_include_directories(narechi-launcher PRIVATE
    "src")

target_compile_definitions(narechi-launcher PRIVATE
    "NRC_PLATFORM_WINDOWS;NRC_DEBUG;")

# Copy dependencies into the exe
add_custom_command(TARGET narechi-launcher POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
        $<TARGET_RUNTIME_DLLS:narechi-launcher> 
        $<TARGET_FILE_DIR:narechi-launcher>
    COMMAND_EXPAND_LISTS
)