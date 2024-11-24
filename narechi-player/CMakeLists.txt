set(NARECHI_PLAYER_SOURCES
    "src/main.cpp"
    "src/scene_layer.cpp"
)

add_executable(narechi-player ${NARECHI_PLAYER_SOURCES})

target_link_libraries(
    narechi-player
    PUBLIC
    narechi-engine
)

target_include_directories(narechi-player PRIVATE
    "include")

target_compile_definitions(narechi-player PRIVATE
    "NRC_PLATFORM_WINDOWS")