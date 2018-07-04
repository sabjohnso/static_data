#ifndef NOTHING_HPP_INCLUDED_1331875396929448878
#define NOTHING_HPP_INCLUDED_1331875396929448878 1

//
// ... Static Data header files
//
#include <static_data/import.hpp>


namespace StaticData {
  namespace Core {

    
    /**
     * @brief A class representing the absence of data
     *
     * @details This class is intended to represent the absence of data, an
     * empty list, or other concepts  associated with nothingness.
     */
    class Nothing {

      /**
       * @brief Instances of Nothing do not have data.
       */
      friend constexpr bool
      has_data( const Nothing& ){ return false; }

      /**
       * @brief Instances of Nothing are empty
       */
      friend constexpr bool
      empty( const Nothing& ){ return true; }


      /**
       * @brief Instances of Nothing are lists
       */
      friend constexpr bool
      islist( const Nothing& ){ return true; }

      /**
       * @brief The head of an instance of Nothing
       * is an instance of Nothing.
       */
      friend constexpr Nothing
      head( const Nothing& ){ return Nothing{}; }

      /**
       * @brief The tail of an instance of Nothing 
       * is an instance of Nothing.
       */
      friend constexpr Nothing
      tail( const Nothing& ){ return Nothing{}; }


      /**
       * @brief Reversing an instance of Nothing and appending a list
       * is just the appended list
       */
      template< typename Accum >
      friend constexpr auto
      rappend( const Nothing&, Accum&& ys ){ return forward<Accum>( ys ); }

      /** 
       * @brief An instance of Nothing reversed is just
       * an instance of Nothing.
       */
      friend constexpr auto
      reverse( const Nothing& ){ return Nothing{}; }

      
      /**
       * @brief Appending a list to an instance of Nothing is just the 
       * appended list.
       */
      template< typename Us >
      friend constexpr auto 
      append( const Nothing&, Us&& ys ){ return forward<Us>( ys ); }

      /**
       * @brief Instances of Nothing do not have elements.
       */      
      friend constexpr size_t
      length( const Nothing& ){
	return 0;
      }

      /**
       * @brief Mapping a function over an instance of Nothing
       * produces an instance of Nothing
       */
      template< typename F >
      friend constexpr auto
      map( F&&, const Nothing& ){
	return Nothing{};
      }

      /**
       * @brief Nothing is the same thing as nothing.
       */
      friend constexpr bool
      operator ==( const Nothing&, const Nothing& ){ return true; }

      /**
       * @brief Nothing is not the same thing as anything.
       */
      template< typename T >
      friend constexpr bool
      operator ==( const Nothing&, const T& ){ return false; }
  
    }; // end of struct Nothing

    
    /**
     * @brief The cannonical instance of Nothing.
     */
    constexpr Nothing nothing{};
    
    
  } // end of namespace Core
} // end of namespace StaticData


#endif // !defined NOTHING_HPP_INCLUDED_1331875396929448878
