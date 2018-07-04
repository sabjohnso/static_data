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
     * @brief Test the zipper class
     */
    struct zipper_tester
    {
      zipper_tester() : accum( 0 ) {
	
	construction_test();
	destructor_test();
	manipulation_test();
      }
      
      operator int() const { return accum; }
      
    private:
      
      void
      construction_test(){
	
	STATIC_DATA_STATIC_TEST( iszipper( zipper( nothing, nothing )));
	STATIC_DATA_STATIC_TEST( iszipper( zipper( list( 1, 2, 3 ), nothing )));
	STATIC_DATA_STATIC_TEST( iszipper( empty_zipper ));
	STATIC_DATA_STATIC_TEST( iszipper( make_zipper( 1, 2, 3, 4 )));
	
      }

      void
      destructor_test(){
	
	STATIC_DATA_STATIC_TEST( data( make_zipper( 1, 2, 3, 4 )) == list( 1, 2, 3, 4 ));
	STATIC_DATA_STATIC_TEST( context( make_zipper( 1, 2, 3, 4 )) == nothing );
	STATIC_DATA_STATIC_TEST( data( zipper( list( 3, 4 ), list( 2, 1 ))) == list( 3, 4 ));
	STATIC_DATA_STATIC_TEST( context( zipper( list( 3, 4 ), list( 2, 1 ))) == list( 2, 1 ));

	STATIC_DATA_STATIC_TEST( head( make_zipper( 1, 2, 3, 4  )) == 1 );
	STATIC_DATA_STATIC_TEST( data( fwd( make_zipper( 1, 2, 3, 4 ))) == list( 2, 3, 4 ));
	STATIC_DATA_STATIC_TEST( context( fwd( make_zipper( 1, 2, 3, 4 ))) == list( 1 ));

	STATIC_DATA_STATIC_TEST(
	  eq( tail( make_zipper( 1, 2, 3, 4 )),
	      zipper( list( 2, 3, 4 ), list( 1 ))));
	
	STATIC_DATA_STATIC_TEST(
	  equal( tail( make_zipper( 1, 2, 3, 4 )),
		 make_zipper( 2, 3, 4 )));

	STATIC_DATA_STATIC_TEST( length( make_zipper( 1, 2, 3, 4 )) == 4 );
	STATIC_DATA_STATIC_TEST( length( fwd( make_zipper( 1, 2, 3, 4 ))) == 3 );
	STATIC_DATA_STATIC_TEST( total_length( fwd( make_zipper( 1, 2, 3, 4 ))) == 4 );
	
      }

      void
      manipulation_test(){
	STATIC_DATA_STATIC_TEST( make_zipper( 1, 2 ) == make_zipper( 1, 2 ));
	STATIC_DATA_STATIC_TEST( bwd( fwd( make_zipper( 1, 2 ))) ==
				 make_zipper( 1, 2 ));
	STATIC_DATA_STATIC_TEST(
	  head( push( 1, empty_zipper )) == 1 );

	STATIC_DATA_STATIC_TEST(
	  head( push( 1, make_zipper( 2 ))) == 1 );
	
	
      }
      
      int accum;
      
    }; // end of struct zipper_tester
    
  } // end of namespace Testing  
} // end of namespace StaticData


int
main( int, char** )
{
  int accum = 0;
  accum += StaticData::Testing::zipper_tester();
  return accum;
}
