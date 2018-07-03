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
	
      }
      operator int() const { return accum; }
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
