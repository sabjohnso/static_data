#
# ... Build script for static_data
#

cmake_minimum_required( VERSION 3.7 )

project( STATIC_DATA )

set( STATIC_DATA_MAJOR 0)
set( STATIC_DATA_MINOR 1)
set( STATIC_DATA_UPDATE 0)
set( STATIC_DATA_VERSION static_data-${STATIC_DATA_MAJOR}.${STATIC_DATA_MINOR} )
set( STATIC_DATA_VERSION_UPDATE ${STATIC_DATA_VERSION}.${STATIC_DATA_UPDATE} )

option( BUILD_STATIC_DATA_TESTING  "Build the static_data  tests" ON )
option( BUILD_STATIC_DATA_DOCUMENTATION "Build the static_data documentation" ON )

include_directories( 
  ${STATIC_DATA_SOURCE_DIR}
  ${STATIC_DATA_BINARY_DIR} )

if( NOT STATIC_DATA_INSTALL_INCLUDE_DIR)
  set( STATIC_DATA_INSTALL_INCLUDE_DIR include/static_data
    CACHE PATH "Path for installation of header files" )
endif( NOT STATIC_DATA_INSTALL_INCLUDE_DIR)

add_subdirectory( static_data )



#
# ... Testing 
#
if( BUILD_STATIC_DATA_TESTING )
  enable_testing()
  add_subdirectory( static_data_testing )
endif( BUILD_STATIC_DATA_TESTING )



#
# ... Documentation
#
if( BUILD_STATIC_DATA_DOCUMENTATION )

  configure_file( Doxyfile.in Doxyfile )

  if( NOT STATIC_DATA_INSTALL_DOC_DIR)
    set( STATIC_DATA_INSTALL_DOC_DIR share/doc/${STATIC_DATA_VERSION}
      CACHE PATH "Path for installation of documentation files" )
  endif( NOT STATIC_DATA_INSTALL_DOC_DIR)

  if( NOT STATIC_DATA_INTALL_MAN_DIR)
    set( STATIC_DATA_INTALL_MAN_DIR include/static_data
      CACHE PATH "Path for installation of man files" )
  endif( NOT STATIC_DATA_INTALL_MAN_DIR)

  find_package( Doxygen REQUIRED )

  add_custom_command(
    OUTPUT ${STATIC_DATA_BINARY_DIR}/doxygen.log
    COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile > doxygen.log
    MAIN_DEPENDENCY Doxyfile
    DEPENDS ${STATIC_DATA_BINARY_DIR}/static_data
    WORKING_DIRECTORY ${STATIC_DATA_BINARY_DIR} )

  add_custom_target(
    static_data_documentation ALL
    DEPENDS ${STATIC_DATA_BINARY_DIR}/doxygen.log )

  install( DIRECTORY ${STATIC_DATA_BINARY_DIR}/doc/html DESTINATION ${STATIC_DATA_INSTALL_DOC_DIR} )
  install( DIRECTORY ${STATIC_DATA_BINARY_DIR}/doc/man DESTINATION ${STATIC_DATA_INTALL_MAN_DIR} )
endif( BUILD_STATIC_DATA_DOCUMENTATION )

# end of build definition for static_data
