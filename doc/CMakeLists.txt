find_package (Doxygen)

if(DOXYGEN_FOUND)
  configure_file (${PROJECT_SOURCE_DIR}/doc/Doxyfile-html.cmake ${PROJECT_BINARY_DIR}/doc/Doxyfile-html)
  add_custom_target (html ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/doc/Doxyfile-html)
endif (DOXYGEN_FOUND)