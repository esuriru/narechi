message(STATUS "Fetching lua")

FetchContent_MakeAvailable(lua)

set(LUA_SRC_FILES
    "lapi.c"
    "lauxlib.c"
    "lbaselib.c"
    "lcode.c"
    "lcorolib.c"
    "lctype.c"
    "ldblib.c"
    "ldebug.c"
    "ldo.c"
    "ldump.c"
    "lfunc.c"
    "lgc.c"
    "linit.c"
    "liolib.c"
    "llex.c"
    "lmathlib.c"
    "lmem.c"
    "loadlib.c"
    "lobject.c"
    "lopcodes.c"
    "loslib.c"
    "lparser.c"
    "lstate.c"
    "lstring.c"
    "lstrlib.c"
    "ltable.c"
    "ltablib.c"
    "ltests.c"
    "ltm.c"
    "lua.c"
    "lundump.c"
    "lutf8lib.c"
    "lvm.c"
    "lzio.c"
)

list(TRANSFORM LUA_SRC_FILES PREPEND ${lua_SOURCE_DIR}/)

add_library(lua ${LUA_SRC_FILES})
add_library(lua::lua ALIAS lua)

target_include_directories(lua PUBLIC ${lua_SOURCE_DIR})
