set(NARECHI_PLAYER_SOURCES "src/main.cpp" "src/scene_layer.cpp")

add_executable(narechi-player ${NARECHI_PLAYER_SOURCES})

target_link_libraries(narechi-player PUBLIC narechi-engine)

target_include_directories(narechi-player PRIVATE "include")

target_compile_definitions(narechi-player PRIVATE "NRC_PLATFORM_WINDOWS")

set(NRC_PLAYER_CHUNK_COUNT 1)
set(NRC_PLAYER_CHUNK_COUNT
    ${NRC_PLAYER_CHUNK_COUNT}
    PARENT_SCOPE
)

add_custom_command(
    TARGET narechi-player
    POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -DNRC_PLAYER_BINARY=$<TARGET_FILE:narechi-player>
        -DNRC_SOURCE_DIR=${CMAKE_SOURCE_DIR}
        -DNRC_LAUNCHER_BIN_DIR=$<TARGET_FILE_DIR:narechi-launcher>
        -DNRC_PLAYER_CHUNK_COUNT=${NRC_PLAYER_CHUNK_COUNT} -P
        ${NRC_CMAKE_DIR}/scripts/EmbedPlayer.cmake
)
