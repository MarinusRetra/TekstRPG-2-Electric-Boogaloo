cmake_minimum_required(VERSION 3.10.0)
project(Dude VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB_RECURSE PROJECT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Source Files/*.cpp")

file(GLOB_RECURSE PROJECT_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Header Files/*.h")


#Change this to path to a folder with all of your libraries
#The names of your libraries should match: BearLibTerminal, REXSpeeder, ZLIB
set(LIBRARY_FOLDER ../Librarby) 
message("Library Folder: ${LIBRARY_FOLDER}")


#Add BearLibTerminal
set(BLT_FLD ${LIBRARY_FOLDER}/BearLibTerminal)
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

#Add ZLIB
set(ZLIB_FLD ${LIBRARY_FOLDER}/ZLIB)
message("ZLIB Folder: ${ZLIB_FLD}")

#Add REXSpeeder
set(REX_FLD ${LIBRARY_FOLDER}/REXSpeeder)
message("REXSpeeder Folder: ${REX_FLD}")

add_library(REX_LIB STATIC ${REX_FLD}/src/REXSpeeder.cpp)
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

add_subdirectory(${LIBRARY_FOLDER}/ZLIB zlib-build)
target_include_directories(REX_LIB PUBLIC ${REX_HEADER} ${ZLIB_HEADER})
target_link_libraries(REX_LIB PUBLIC zlib)

target_link_libraries(${PROJECT_NAME} PRIVATE ${BLT_LIB} REX_LIB)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${ZLIB_HEADER}
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
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
 #       ${BLT_LIB}/BearLibTerminal.lib
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
       $<TARGET_FILE:zlib>
       $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:REX_LIB>
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



