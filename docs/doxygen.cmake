#
# Build the Doxygen documentation on Release build
#

if (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")

    find_package(Doxygen)
    find_program(GRAPHVIZ dot)

    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is not installed! Hint: `sudo apt install doxygen` and clean cmake cache before build!")
    elseif(NOT GRAPHVIZ)
        message(FATAL_ERROR "Graphviz is not installed! Hint: `sudo apt install graphviz` and clean cmake cache before build!")
    elseif (DOXYGEN_FOUND)

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

        #set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/doxygen/Doxyfile.in)
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

        #set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc/doxygen-build/)

        # Doxygen konfigurieren
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        message("Doxygen build started ...")


        # Beachte: Der Build wird in der Top-Level-CMake-Datei ausgelöst
        add_custom_target( doxygen_ehmi ALL
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                COMMENT "Generating the documentation with Doxygen ..."
                VERBATIM)


        # Optional: Installiere die Dokumentation im System
        # Beachte: Die Dokumente befinden sich in [build_dir]/docs/doxygen/html/index.html
        # install(
        #     DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs/doxygen/html
        #     DESTINATION ./share/doc/${PROJECT_NAME}
        #     OPTIONAL)
    endif()
endif()
