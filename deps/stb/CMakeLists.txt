message(STATUS "Fetching stb")

add_library(stb STATIC "stb_image/src/stb_image.c")

target_include_directories(stb PUBLIC "stb_image/include")
