message(STATUS "Fetching stduuid")

set(UUID_SYSTEM_GENERATOR
    ON
    CACHE BOOL "" FORCE
)

FetchContent_MakeAvailable(stduuid)
