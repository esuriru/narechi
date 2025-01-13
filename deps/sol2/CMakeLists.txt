message(STATUS "Fetching sol2")

set(SOL2_LUA_VERSION
    "5.4.7"
    CACHE STRING "" FORCE
)

set(SOL2_BUILD_LUA
    FALSE
    CACHE BOOL "" FORCE
)

FetchContent_MakeAvailable(sol2)
