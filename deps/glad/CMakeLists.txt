message(STATUS "Fetching glad")

add_library(glad STATIC
    "src/gl.c")

target_include_directories(glad PRIVATE
    "include")
