cmake_minimum_required(VERSION 3.16)
project(Nyx)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

function(include_dependency libName gitURL gitTag)
    FetchContent_Declare(${libName}
            GIT_REPOSITORY ${gitURL}
            GIT_TAG ${gitTag}
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(${libName})
endfunction()

set(LIB1 raylib)
find_package(${LIB1} QUIET)
if (NOT ${LIB1}_FOUND)
    set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
    include_dependency(${LIB1} https://github.com/raysan5/raylib.git 5.0)
endif()

add_executable(Nyx main.cpp)
target_link_libraries(Nyx PRIVATE ${LIB1})