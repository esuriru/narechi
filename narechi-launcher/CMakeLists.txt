set(NARECHI_LAUNCHER_SOURCES
    "src/launcher_app.cpp"
)

add_executable(narechi-launcher ${NARECHI_LAUNCHER_SOURCES})

target_link_libraries(
    narechi-launcher
    PUBLIC
    narechi-engine
)

install(TARGETS narechi-launcher DESTINATION bin)