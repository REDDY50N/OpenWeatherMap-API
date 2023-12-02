#
# Build the Doxygen documentation on Release build
#

find_package(Doxygen)
find_program(GRAPHVIZ dot)

if(NOT DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is not installed! Hint: `sudo apt install doxygen` and clean cmake cache before build!")
elseif(NOT GRAPHVIZ)
    message(FATAL_ERROR "Graphviz is not installed! Hint: `sudo apt install graphviz` and clean cmake cache before build!")
endif()


IF(${CMAKE_BUILD_TYPE} MATCHES Debug)
    message("CMAKE_BUILD_TYPE: Debug")
ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
    message("CMAKE_BUILD_TYPE: Release")

    set( DOXYGEN_OUTPUT_DIRECTORY doxygen )
    set( DOXYGEN_COLLABORATION_GRAPH YES )
    set( DOXYGEN_EXTRACT_ALL YES )
    set( DOXYGEN_CLASS_DIAGRAMS YES )
    set( DOXYGEN_HIDE_UNDOC_RELATIONS NO )
    set( DOXYGEN_HAVE_DOT YES )
    set( DOXYGEN_CLASS_GRAPH YES )
    set( DOXYGEN_CALL_GRAPH YES )
    set( DOXYGEN_CALLER_GRAPH YES )
    set( DOXYGEN_COLLABORATION_GRAPH YES )
    set( DOXYGEN_BUILTIN_STL_SUPPORT YES )
    set( DOXYGEN_EXTRACT_PRIVATE YES )
    set( DOXYGEN_EXTRACT_PACKAGE YES )
    set( DOXYGEN_EXTRACT_STATIC YES )
    set( DOXYGEN_EXTRACT_LOCALMETHODS YES )
    set( DOXYGEN_UML_LOOK YES )
    set( DOXYGEN_UML_LIMIT_NUM_FIELDS 50 )
    set( DOXYGEN_TEMPLATE_RELATIONS YES )
    set( DOXYGEN_DOT_GRAPH_MAX_NODES 100 )
    set( DOXYGEN_MAX_DOT_GRAPH_DEPTH 0 )
    set( DOXYGEN_DOT_TRANSPARENT YES )

    doxygen_add_docs( doxygen ${RPP_PROJECT_SOURCE_DIR} )

    doxygen_add_docs( doxygen_ehmi
            src/ #[filesOrDirs...]
            [ALL]
            #[USE_STAMP_FILE]
            #[WORKING_DIRECTORY dir]
            #[COMMENT comment]
            #[CONFIG_FILE filename]
    )

    message("Doxygen build successful!")
ENDIF()

