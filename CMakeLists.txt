cmake_minimum_required(VERSION 3.10.0)
project(Dude VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB_RECURSE PROJECT_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/Source Files/*.cpp"
)

file(GLOB_RECURSE PROJECT_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/Header Files/*.h"
)

set(BLT_FLD ../Librarby/BearLibTerminal_0.15.8)
message("BearLibTerminal Folder: ${BLT_FLD}")

find_library(BLT_LIB
    NAMES BearLibTerminal.lib
    PATHS ${BLT_FLD}/Windows64
)

message("BearLibTerminal Library: ${BLT_LIB}")

find_path(BLT_HEADER
    NAMES BearLibTerminal.h
    PATHS ${BLT_FLD}/Include/C
)

message("BearLibTerminal Header: ${BLT_HEADER}")

find_path(BLT_BIN
    NAMES BearLibTerminal.dll
    PATHS ${BLT_FLD}/Windows64
)

message("BearLibTerminal Binary: ${BLT_BIN}")

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
)

add_subdirectory(../Librarby/REXSpeeder/cmake rexspeeder-build)

target_link_libraries(${PROJECT_NAME} PRIVATE ${BLT_LIB} rexspeeder)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${BLT_HEADER}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Header Files
    ../Librarby/RexSpeeder/include
)

# Copies the dll and puts it next to my .exe after building
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${BLT_BIN}/BearLibTerminal.dll
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
