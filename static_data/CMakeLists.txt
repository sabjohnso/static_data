configure_file( config.hpp.in config.hpp )

install( FILES
  ${CMAKE_CURRENT_BINARY_DIR}/config.hpp
  import.hpp
  list.hpp
  nothing.hpp
  static_data.hpp
  zipper.hpp
  DESTINATION ${STATIC_DATA_INSTALL_INCLUDE_DIR} )
