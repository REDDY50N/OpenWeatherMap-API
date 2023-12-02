cmake_minimum_required (VERSION 3.16)

find_package(Doxygen)
find_program(GRAPHVIZ dot)

if(NOT DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is not installed! Hint: `sudo apt install doxygen` and clean cmake cache before build!")
elseif(NOT GRAPHVIZ)
    message(FATAL_ERROR "Graphviz is not installed! Hint: `sudo apt install graphviz` and clean cmake cache before build!")
elseif (DOXYGEN_FOUND)
    # configure doxygen configuration file
    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/doxygen/Doxyfile.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${doxyfile_in} ${doxyfile} @ONLY)

    # Note: build is triggered in top level cmake file
    add_custom_target(Doxygen
            COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating the documentation with Doxygen ..."
            VERBATIM)

    # Optional: Install docs on the system
    # Note: Docs are in [build_dir]/docs/doxygen/html/index.html
    install(
         DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs/doxygen/html
         DESTINATION ./share/doc/${PROJECT_NAME}
         OPTIONAL)
endif()