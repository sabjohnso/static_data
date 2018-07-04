#ifndef ZIPPER_HPP_INCLUDED_741907820090049131
#define ZIPPER_HPP_INCLUDED_741907820090049131 1

//
// ... Static Data header files
//
#include <static_data/nothing.hpp>
#include <static_data/list.hpp>


namespace StaticData{
  namespace Core{



    template< typename Ts, typename Us >
    class zipper;

    template< typename Ts, typename Us >
    zipper( Ts&& xs, Us&& ys ) -> zipper<decay_t<Ts>,decay_t<Us>>;


    
    template< typename Ts, typename Us >
    class zipper {
    public:
	
      using storage_type = 
	decltype( list( declval<Ts>(), declval<Us>()));
      
      static_assert( 
	is_same<decay_t<Ts>,Ts>::value,
	"\nExpected Ts to be free of any reference or "
	"\nor const decorations." );

      static_assert( is_same<decay_t<Us>,Us>::value,
	"\nExpected Us to be free of any  reference "
	"\nor const decoractions" );

      
      static_assert( islist_type(type<Ts>));
      static_assert( islist_type(type<Us>));
              
	
      using data_type = decltype( head( declval<storage_type>()));
      using context_type = decltype( tail( declval<storage_type>()));


      constexpr 
      zipper( zipper&& input )
	: storage( move( input.storage ))
      {}

      constexpr
      zipper( const zipper& input )
	: storage( input.storage )
      {}

      template< typename D, typename C >
      constexpr
      zipper( D&& data, C&& context )
	: storage( list( forward<D>( data ), forward<C>( context ))) {
	static_assert( islist_type( data ));
	static_assert( islist_type( context ));
      }

    private:
	
      storage_type storage;


      friend constexpr bool
      iszipper( const zipper& xs ){ return true; }

      friend constexpr decltype(auto)
      data( zipper&& xs ){ return head( move( xs.storage )); }

      friend constexpr decltype(auto)
      data( const zipper& xs ){ return head( xs.storage ); }
      
      friend constexpr decltype(auto)
      context( zipper&& xs ){ return head( tail( move( xs.storage ))); }
	
      friend constexpr decltype(auto)
      context( const zipper& xs ){ return head( tail( xs.storage )); }

      friend constexpr bool
      has_data( const zipper& xs ){ return has_data( data( xs )); }

      friend constexpr bool
      empty( const zipper& xs ){ return ! has_data( xs ); }

      friend constexpr bool
      atfront( const zipper& xs ){ return empty( context( xs )); }

      friend constexpr bool
      atback( const zipper& xs ){ return empty( xs ); }

      friend constexpr bool
      completely_empty( const zipper& xs ){ return empty( data( xs )) && atfront( xs ); }

      friend constexpr size_t
      length( const zipper& xs ){ return length( data( xs )); }

      friend constexpr size_t
      position( const zipper& xs ){ return length( context( xs )); }

      friend constexpr size_t
      total_length( const zipper& xs ){ return length( data( xs )) + length( context( xs )); }

      friend constexpr auto
      head( const zipper& xs ){ return head( data( xs )); }

      friend constexpr auto
      head( zipper&& xs ){ return head( data( move( xs ))); }

      
      template< typename D, typename C >
      static constexpr auto
      fwd_aux( D&& xs, C&& ys ){
	using DNew = decay_t<decltype( tail( forward<D>( xs )))>;
	using CNew = decay_t<decltype( cons( head( forward<D>( xs )),
					     forward<C>( ys )))>;
	return zipper<DNew,CNew>(
	  tail( forward<D>( xs )),
	  cons( head( forward<D>( xs )),
		forward<C>( ys )));
      }

      friend constexpr auto
      fwd( const zipper& xs ){
	return fwd_aux( data( xs ), context( xs ));
      }
	
      friend constexpr auto
      fwd( zipper&& xs ){
	return fwd_aux( data( move( xs )), context( move( xs )));
      }


      template< typename D, typename C >
      static constexpr auto
      bwd_aux( D&& xs, C&& ys ){
	using DNew = decay_t<decltype( cons( head( forward<D>( ys )), forward<C>( xs )))>;
	using CNew = decay_t<decltype( tail( forward<C>( ys )))>;
											    
	return zipper<DNew,CNew>(
	  cons( head( forward<C>( ys )), forward<D>( xs )),
	  tail( ys ));
      }

      friend constexpr auto
      bwd( const zipper& xs ){
	return bwd_aux( data( xs ), context( xs ));
      }

      friend constexpr auto
      bwd( zipper&& xs ){
	return bwd_aux( data( move( xs )),  context( move( xs )));
      }


      friend constexpr auto
      tail( const zipper& xs ){ return fwd( xs ); }


      friend constexpr auto
      tail( zipper&& xs ){ return fwd( move( xs )); }

      template< typename T >
      friend constexpr auto      
      push( T&& x, const zipper& xs ){
	using D = decay_t<decltype(cons( x, data( xs )))>;
	using C = decay_t<decltype(context( xs ))>;
	return zipper<D,C>( cons( x, data( xs )), context( xs ));
      }

      template< typename T >
      friend constexpr auto      
      push( T&& x, zipper&& xs ){
	using D = decay_t<decltype(cons( x, data( move( xs ))))>;
	using C = decay_t<decltype(context( move( xs )))>;
	return zipper<D,C>( cons( x, data( move( xs ))), context( move( xs )));
      }

      template< typename T >
      friend constexpr auto
      cons( T&& x, const zipper& xs ){
	return push( forward<T>( x ), xs );
      }

      template< typename T >
      friend constexpr auto
      cons( T&& x, zipper&& xs ){
	return push( forward<T>( xs ), move( xs ));
      }

      template< typename Vs>
      friend constexpr auto
      splice( const zipper& xs, Vs&& ys ){
	using D = decay_t<decltype( append( data( xs ),  data( forward<Vs>( ys ))))>;
	using C = decay_t<decltype( append( context( xs ), context( forward<Vs>( ys ))))>;
	return zipper<D,C>(
	  append( data( xs ), 
		  data( forward<Vs>( ys ))),
	  append( context( xs ), 
		  context( forward<Vs>( ys ))));
      }

      
      template< typename Vs, typename Ws >
      friend constexpr bool
      eq( const zipper& xs, const zipper<Vs,Ws>& ys ){
	return ( data( xs ) == data( ys )) &&
	  ( context( xs ) == context( ys ));
      }


      template< typename Vs, typename Ws >
      friend constexpr bool
      equal( const zipper& xs, const zipper<Vs,Ws>& ys ){
	return data( xs ) == data( ys );
      }

      template< typename Vs >
      friend constexpr bool
      equal( const zipper& xs, const Vs& ys){
	return data( xs ) == ys;
      }

      template< typename Vs, typename Ws >
      friend constexpr bool
      operator ==( const zipper& xs, const zipper<Vs,Ws>& ys ){
	return eq( xs, ys);
      }

      

      

      template< typename Vs, typename Ws >
      friend constexpr bool
      operator !=( const zipper& xs, const zipper<Vs,Ws>& ys ){
	return !( xs == ys );
      }
      
      
    }; // end of class zipper


    template< typename ... Ts >
    constexpr auto
    make_zipper( Ts&& ... xs ){
      return zipper( list( forward<Ts>( xs ) ... ), nothing );
    }

    constexpr auto empty_zipper = make_zipper();
      


  } // end of namespace Core
} // end of namespace StaticData

#endif // !defined ZIPPER_HPP_INCLUDED_741907820090049131
