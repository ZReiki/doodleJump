cmake_minimum_required(VERSION 3.30)
project(SFML_Lab LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(SFML_Lab main.cpp
        practice.cpp)
target_link_libraries(SFML_Lab PRIVATE sfml-graphics)
target_compile_features(SFML_Lab PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
            TARGET SFML_Lab
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:SFML_Lab>
            VERBATIM)
endif()