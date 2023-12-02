### PDS VERSION ZUR ANZEIGE IM HMI

# Hinweis:
# Versionsnummern bei Release anpassen
# Datei: version.txt

include(cmake/git-commands.cmake)

# Easy Version String
file(STRINGS "${PROJECT_SOURCE_DIR}/VERSION" VERSION)
set(CPACK_PACKAGE_VERSION ${VERSION})
add_definitions(-DVERSION_STRING="${VERSION}")

# Extrahiere den Git Commit Hash
set(PDS_VERSION_NUMBER ${VERSION}-${GIT_COMMIT_HASH})
set(PDS_VERSION_STRING ${PDS_VERSION_NUMBER})

# timestamp only on release because of cache reset
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    string(TIMESTAMP BUILD_TIMESTAMP "%Y-%m-%d" UTC)
    add_definitions(-DCMAKE_BUILD_TIMESTAMP="${BUILD_TIMESTAMP}")
endif ()

# cmake info message
message("")
message(STATUS "PDS VERSION: ${PDS_VERSION_NUMBER}")
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "BUILD TIMESTAMP: ${BUILD_TIMESTAMP}")
endif()
message("")
