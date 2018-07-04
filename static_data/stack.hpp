#ifndef STACK_HPP_INCLUDED_1810632271234553245
#define STACK_HPP_INCLUDED_1810632271234553245 1

//
// ... Static Data header files
//
#include <static_data/import.hpp>
#include <static_data/nothing.hpp>
#include <static_data/list.hpp>


namespace StaticData
{
  namespace Core
  {

    template< typename Ts >
    class stack {
    public:

      using storage_type = Ts;
      static_assert( islist_type( type<storage_type> ));

      template< typename Us >
      constexpr
      stack( Us&& input ) : storage( forward<Us>( input ) )
      {}

      constexpr
      stack( const stack& input )
	: storage( input.storage )
      {}

      constexpr
      stack( stack&& input )
	: storage( move( input.storage ))
      {}

    private:

      storage_type storage;

      friend constexpr bool
      has_data( const stack& xs ){ return has_data( xs.storage ); }

      friend constexpr bool
      empty( const stack& xs ){ return empty( xs.storage ); }

      friend constexpr bool
      isstack( const stack&  ){ return true; }

      friend constexpr decltype(auto)
      top( const stack& xs ){ return head( xs.storage ); }

      friend constexpr decltype(auto)
      top( stack&& xs ){ return head( move( xs.storage )); }

      friend constexpr auto
      pop( const stack& xs ){ return stack( tail( xs.storage )); }

      friend constexpr auto
      pop( stack&& xs ){ return stack( tail( move( xs.storage ))); }

      template< typename T >
      friend constexpr auto
      push( T&& x, const stack& xs ){
	return stack( cons( forward<Ts>( x ), xs.storage ));
      }

      template< typename T >
      friend constexpr auto
      push( T&& x, stack&& xs ){
	return stack( cons( forward<Ts>( x ), move( xs.storage )));
      }

      
	
    }; // end of class stack

    template< typename T >
    constexpr bool
    isstack( const T& ){ return false; }


    template< typename Ts >
    stack( Ts&& xs ) -> stack<decay_t<Ts>>;


    template< typename ... Ts >
    constexpr auto
    make_stack( Ts&& ... xs ){
      return stack( list( forward<Ts>( xs ) ... ));
    }

    constexpr auto empty_stack = make_stack();
    
  } // end of namespace Core
} // end of namespace StaticData

#endif // !defined STACK_HPP_INCLUDED_1810632271234553245
