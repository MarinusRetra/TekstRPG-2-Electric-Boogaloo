cmake_minimum_required(VERSION 3.10.0)
project(Dude VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB_RECURSE PROJECT_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/Source Files/*.cpp"
)

file(GLOB_RECURSE PROJECT_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/Header Files/*.h"
)

#Add BearLibTerminal
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


#Add REXSpeeder
set(REX_FLD ../Librarby/REXSpeeder)
message("REXSpeeder Folder: ${REX_FLD}")

find_library(REX_LIB
    NAMES rexspeeder.lib
    PATHS ${REX_FLD}/build/Debug
)
message("REXSpeeder Library: ${REX_LIB}")

find_path(REX_HEADER
    NAMES REXSpeeder.h
    PATHS ${REX_FLD}/include
)
message("REXSpeeder Header: ${REX_HEADER}")

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${BLT_LIB} ${REX_LIB})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${BLT_HEADER}
    ${REX_HEADER}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Header Files
)


set(FONTS_FLD ${CMAKE_CURRENT_SOURCE_DIR}/ResourceFiles/Fonts)
message("Fonts: ${FONTS_FLD}")

set(CONFIG ${CMAKE_CURRENT_SOURCE_DIR}/config.ini)
message("Config: ${CONFIG}")


# Copies the dll from BearLibTerminal and puts it into my build folder.
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${BLT_BIN}/BearLibTerminal.dll
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# Deletes the old config.ini and copies the config.ini from the project after building and places it into my build folder.
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E rm -f
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/config.txt
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CONFIG}
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# Deletes the old fonts folder, copies it from the project after building and places it into my build folder.
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E rm -rf
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/Fonts
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${FONTS_FLD}
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/Fonts
)



