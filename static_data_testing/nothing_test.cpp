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
     * @brief Test nothing
     */
    struct nothing_test
    {
      nothing_test() : accum( 0 ) {
	predicates_test();
	list_destructors_test();
	list_manipulation_test();
      }
      operator int() const { return accum; }
    private:

      void
      predicates_test(){
	STATIC_DATA_STATIC_TEST( ! has_data( nothing ));
	STATIC_DATA_STATIC_TEST( empty( nothing ));
	STATIC_DATA_STATIC_TEST( islist( nothing ));
      }
      
      void
      list_destructors_test(){
	STATIC_DATA_STATIC_TEST( head( nothing ) == nothing );
	STATIC_DATA_STATIC_TEST( tail( nothing ) == nothing );
	STATIC_DATA_STATIC_TEST( length( nothing ) == 0 );
      }

      void
      list_manipulation_test(){
	STATIC_DATA_STATIC_TEST( reverse( nothing ) == nothing );
	STATIC_DATA_STATIC_TEST( append( nothing, list( 1, 2 )) == list( 1, 2 ));
	STATIC_DATA_STATIC_TEST( map( []( auto x ){ return x*x; }, nothing ) == nothing );
	
      }
      

      
      int accum;
    }; // end of struct nothing_test



    
  } // end of namespace Testing
} // end of namespace StaticData

int
main( int, char** )
{
  int accum = 0;
  accum += StaticData::Testing::nothing_test();
  return accum;
}
