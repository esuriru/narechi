message(STATUS "Fetching nativefiledialog-extended")

set(NFD_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(NFD_BUILD_SDL2_TESTS OFF CACHE BOOL "" FORCE)
set(NFD_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(nativefiledialog-extended)