macro( static_data_add_test  name )
  add_executable( ${name}_test ${name}_test.cpp )
  add_test( ${name} ${name}_test ) 
endmacro( static_data_add_test  name )

static_data_add_test( nothing )
