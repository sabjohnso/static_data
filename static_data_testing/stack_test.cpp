//
// ... Static Data header files
//
#include <static_data/static_data.hpp>

//
// ... Testing header files
//
#include <static_data_testing/test_macros.hpp>



namespace StaticData
{
  namespace Testing
  {

    /** 
     * @brief Test the stack class
     */
    struct stack_tester
    {
      stack_tester() : accum( 0 ) {
	construction_test();
	predicate_test();
      }
      operator int() const { return accum; }


    private:
      void
      construction_test(){

	STATIC_DATA_STATIC_TEST( isstack( stack( nothing )));
	STATIC_DATA_STATIC_TEST( isstack( stack( list( 1, 2, 3 ))));
	STATIC_DATA_STATIC_TEST( isstack( make_stack()));
	STATIC_DATA_STATIC_TEST( isstack( make_stack( 1, 2, 3 )));
	STATIC_DATA_STATIC_TEST( isstack( empty_stack ));
      }

      void
      predicate_test(){
	STATIC_DATA_STATIC_TEST( isstack( stack( list( 1, 2, 3 ))));
	STATIC_DATA_STATIC_TEST( ! isstack( "cow" ));
	STATIC_DATA_STATIC_TEST( has_data( make_stack( 1 )));
	STATIC_DATA_STATIC_TEST( ! has_data( make_stack()));
      }
      
      int accum;
    }; // end of struct stack_tester
    
  } // end of namespace Testing
} // end of namespace StaticData

int
main( int, char** )
{
  int accum = 0;
  
  return accum;
}
