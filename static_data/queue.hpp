#ifndef QUEUE_HPP_INCLUDED_695231498022688004
#define QUEUE_HPP_INCLUDED_695231498022688004 1
//
// ... Static Data header files
//
#include <static_data/import.hpp>
#include <static_data/list.hpp>


namespace StaticData
{
  namespace Core
  {

    template< typename Ts, typename Us >
    class queue;


    
    template< typename Ts, typename Us >
    queue( Ts&& , Us&& ) -> queue<decay_t<Ts>,decay_t<Us>>;


    
    template< typename Ts, typename Us >
    class queue {
    public:

      using output_type = Ts;
      using input_type = Us;

      static_assert( is_same<decay_t<output_type>,output_type>::value );
      static_assert( is_same<decay_t<input_type>,input_type>::value );
      static_assser( islist_type( type<Ts> ));
      static_assert( islist_type( type<Us> ));
      
      using storage_type = decay_t<decltype(list( declval<Ts>(), declval<Us>()))>;

      template< typename Vs, typename Ws >
      constexpr
      queue( Vs&& xs, Ws&& ys )
	: storage( list( forward<Vs>( xs ), forward<Ws>( ys )))
      {}

      constexpr
      queue( const queue& input ) : storage( input.storage ){}

      constexpr
      queue( queue&& input ) : storage( move( input.storage )){}
      
    private:

      storage_type storage;
      
    }; // end of class queue;
	      
    
  } // end of namespace Core
} // end of namespace StaticData

#endif // !defined QUEUE_HPP_INCLUDED_695231498022688004
