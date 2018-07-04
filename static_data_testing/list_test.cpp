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
     * @brief test the list functionality 
     */
    struct list_tester
    {
      list_tester() : accum( 0 ) {
	constructors_test();
	predicates_test();
	list_destructors_test();
	list_manipulation_test();
      }
      operator int() const { return accum; }

    private:
      
      void
      constructors_test(){
	STATIC_DATA_STATIC_TEST( islist( cons(1, nothing)));
	STATIC_DATA_STATIC_TEST( islist( cons(1, cons( 2, nothing ))));

	STATIC_DATA_STATIC_TEST( islist( list()));
	STATIC_DATA_STATIC_TEST( list() == nothing );

	STATIC_DATA_STATIC_TEST( islist( list( 1 )));
	STATIC_DATA_STATIC_TEST( islist( list( 1, 2 )));
	STATIC_DATA_STATIC_TEST( islist( list( 1, 2, 3 )));
      }

      void
      predicates_test(){
	
	STATIC_DATA_STATIC_TEST( islist( list()));
	STATIC_DATA_STATIC_TEST( !has_data( list()));
	STATIC_DATA_STATIC_TEST( empty( list()));

	STATIC_DATA_STATIC_TEST( islist( list( 1 )));
	STATIC_DATA_STATIC_TEST( has_data( list( 1 )));
	STATIC_DATA_STATIC_TEST( ! empty( list( 1 )));
      }

      void
      list_destructors_test(){
	STATIC_DATA_STATIC_TEST( head( list( 1, 2, 3 )) == 1 );
	STATIC_DATA_STATIC_TEST( tail( list( 1, 2, 3 )) == list( 2, 3 ));
	STATIC_DATA_STATIC_TEST( length( list( 1, 2, 3 )) == 3 );
      }

      void
      list_manipulation_test(){
	STATIC_DATA_STATIC_TEST( reverse( list( 1, 2, 3 )) == list( 3, 2, 1 ));
	STATIC_DATA_STATIC_TEST( 
	  append( list( 1, 2 ), list( 3, 4 )) ==
	  list( 1, 2, 3, 4 ));
      }
      
      int accum;
    }; // end of struct list_tester
    
  } // end of namespace Testing
} // end of namespace StaticData


int
main( int, char** )
{
  int accum = 0;
  accum += StaticData::Testing::list_tester();
  return accum;
}
