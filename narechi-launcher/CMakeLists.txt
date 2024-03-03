set(NARECHI_LAUNCHER_SOURCES
    "src/launcher_app.cpp"
)

add_executable(narechi-launcher ${NARECHI_LAUNCHER_SOURCES})

target_link_libraries(
    narechi-launcher
    PUBLIC
    narechi-engine
)

# Copy dependencies into the exe
add_custom_command(TARGET narechi-launcher POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
        $<TARGET_RUNTIME_DLLS:narechi-launcher> 
        $<TARGET_FILE_DIR:narechi-launcher>
    COMMAND_EXPAND_LISTS
)