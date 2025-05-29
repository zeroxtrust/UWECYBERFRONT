cmake_minimum_required(VERSION 3.16)

project(Cyberfront)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

include_directories(include)

find_package(nlohmann_json 3.2.0 QUIET)
if(NOT nlohmann_json_FOUND)
    message(STATUS "nlohmann/json not found via find_package, assuming header-only in include/")
endif()

set(SOURCES
    src/main.cpp
    src/engine.cpp
    src/mission_manager.cpp
    src/ui.cpp
    src/forensic_tools.cpp
    src/load_missions.cpp
    src/load_characters.cpp
    src/game_state.cpp
    src/mission_logic.cpp
)

add_executable(cyberfront ${SOURCES})

target_link_libraries(cyberfront 
    sfml-graphics 
    sfml-window 
    sfml-system 
    sfml-audio
)

if(nlohmann_json_FOUND)
    target_link_libraries(cyberfront nlohmann_json::nlohmann_json)
endif()

if(MSVC)
    target_compile_options(cyberfront PRIVATE /W4)
else()
    target_compile_options(cyberfront PRIVATE -Wall -Wextra -Wpedantic)
endif()

file(COPY ${CMAKE_SOURCE_DIR}/data/ DESTINATION ${CMAKE_BINARY_DIR}/data/)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/assets) 