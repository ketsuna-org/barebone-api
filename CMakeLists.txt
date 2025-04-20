cmake_minimum_required(VERSION 3.27)

set(BOT_NAME "bot")
project(${BOT_NAME} VERSION 0.1.0 DESCRIPTION "A discord bot")

aux_source_directory("src" coresrc)

add_executable(${BOT_NAME} ${coresrc})
set(CMAKE_CXX_FLAGS "-isystem /usr/include/c++/11 -isystem /usr/include/x86_64-linux-gnu/c++/11")
include_directories(SYSTEM BEFORE /usr/include)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(DPP REQUIRED)
target_link_libraries(${PROJECT_NAME}
        dpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
