message(STATUS "Fetching yaml-cpp")

# Disable deprecated warning
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(yaml-cpp)

set(CMAKE_WARN_DEPRECATED ON CACHE BOOL "" FORCE)