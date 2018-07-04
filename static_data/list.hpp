#ifndef LIST_HPP_INCLUDED_981697518487840817
#define LIST_HPP_INCLUDED_981697518487840817 1

//
// ... Static Data header files
//
#include <static_data/import.hpp>
#include <static_data/nothing.hpp>



namespace StaticData
{
  namespace Core
  {

    /** 
     * @brief A pair used to form lists
     *
     * @details A cell is used to build a list, when
     * terminated by an instance of Nothing
     */
    template< typename Head, typename Tail >
    class cell : pair<Head,Tail> { 
    public:
      
      using head_type = Head;
      using tail_type = Tail;


      static_assert( 
	is_same<decay_t<Head>,Head>::value,
	"\nExpected Head to be free of any const or "
	"\nreference modifications. ");

      static_assert( 
	is_same<decay_t<Tail>,Tail>::value,
	"\nExpected Head to be free of any const or "
	"\nreference modifications. ");
      

      using base = pair<head_type,tail_type>;

      template< typename H, typename T >
      constexpr
      cell( H&& head, T&& tail )
	: base( forward<H>( head ), forward<T>( tail ))
      {}

      constexpr
      cell( const cell& input )
	: base( input )
      {}

      constexpr
      cell( cell&& input )
	: base( move( input ))
      {}

      
    private:

      /** 
       * @brief Instances of cell have data 
       */
      friend constexpr bool
      has_data( const cell& ){ return true; }

      /**
       * @brief Instances of cell are not empty
       */
      friend constexpr bool
      empty( const cell& xs ){ return ! has_data( xs ); }

      /**
       * @brief The head of a cell is the first item in the pair
       */
      friend constexpr const head_type&
      head( const cell& xs ){ return xs.first; }

      /**
       * @brief The head of a cell is the first item in the pair
       */
      friend constexpr head_type&&
      head( cell&& xs ){ return move( xs.first ); }

      /**
       * @brief the tail of a cell is the second item in the
       * pair
       */
      friend constexpr const tail_type&
      tail( const cell& xs ){ return xs.second; }

      /**
       * @brief the tail of a cell is the second item in the
       * pair
       */
      friend constexpr tail_type&&
      tail( cell&& xs ){ return move( xs.second ); }


      /**
       * @brief A cell is a list, only if its tail is a list
       */
      friend constexpr bool
      islist( const cell& xs ){ return islist( tail( xs )); }


      /**
       * @brief Instances of cell can be constructed using cons.
       */
      template< typename T >
      friend constexpr auto
      cons( T&& x, const cell& xs ){
	return cell<decay_t<T>,cell>( forward<T>( x ), xs );
      }

      
      
      /**
       * @brief Instances of cell can be constructed using cons.
       */
      template< typename T >
      friend constexpr auto
      cons( T&& x, cell&& xs ){
	return cell<decay_t<T>,cell>( forward<T>( x ), move( xs ));
      }


      /** 
       * @brief A cell can be reversed and have a list appended, but
       * only if the cell is a list.
       */
      template< typename Accum >
      friend constexpr auto
      rappend( const cell& xs, Accum&& ys ){
	return rappend( tail( xs ), cons( head( xs ), ys ));

	static_assert(
	  islist_type( xs ),
	  "\nThe map function requires a list" );
      }


      /** 
       * @brief A cell can be reversed and have a list appended, but
       * only if the cell is a list.
       */
      template< typename Accum >
      friend constexpr auto
      rappend( cell&& xs, Accum&& ys ){
	return rappend( tail( move( xs )), cons( head( move( xs )), ys ));

	static_assert(
	  islist_type( xs ),
	  "\nThe map function requires a list" );
      }

      /**
       * @brief A cell can be reversed, but only if it is a list.
       */
      friend constexpr auto
      reverse( const cell& xs ){
	return rappend( xs, nothing );
	
	static_assert(
	  islist_type( xs ),
	  "\nThe map function requires a list" );
      }

      /**
       * @brief A cell can be reversed, but only if it is a list.
       */
      friend constexpr auto
      reverse( cell&& xs ){
	return rappend( move( xs ), nothing );

	static_assert(
	  islist_type( xs ),
	  "\nThe map function requires a list" );
      }


      /**
       * @brief A cell can have something appended to it, but only
       * if the cell is a list
       */
      template< typename Us >      
      friend constexpr auto
      append( const cell& xs, Us&& ys ){
	return rappend( reverse( xs ), forward<Us>( ys ));

	static_assert(
	  islist_type( xs ),
	  "\nThe map function requires a list" );
      }


      /**
       * @brief A cell can have something appended to it, but only
       * if the cell is a list
       */
      template< typename Us >      
      friend constexpr auto
      append( cell&& xs, Us&& ys ){
	return rappend( reverse( move( xs )), forward<Us>( ys ));
	
	static_assert(
	  islist_type( xs ),
	  "\nThe map function requires a list" );
      }


      /**
       * @brief An auxilliary function for calculating the length of
       * a list
       */
      template< typename Ts >
      static constexpr size_t
      length_aux( const Ts& xs, size_t accum ){
	return has_data( xs )
	  ? length_aux( tail( xs ), accum+1 )
	  : accum;
      }

      /**
       * @brief Return the length of cell that is a list
       */
      friend constexpr size_t
      length( const cell& xs ){
	
	return length_aux( xs, 0 );
	
	static_assert(
	  islist_type( xs ),
	  "\nThe length function requires a list" );
      }

      
      /**
       * @brief An auxilliary function for mapping a function over
       * a list
       */
      template< typename F, typename Accum >
      static constexpr auto
      map_aux( F&&, const Nothing&, Accum&& ys ){
	return reverse( forward<Accum>( ys ));
      }

      /**
       * @brief An auxilliary function for mapping a function over
       * a list
       */
      template< typename F, typename Ts, typename Accum >
      static constexpr auto
      map_aux( F&& f, const Ts& xs, Accum&& ys ){
	return map_aux(
	  forward<F>( f ),
	  tail( xs ),
	  cons( f( head( xs )),
		forward<Accum>( ys )));
      }


      /**
       * @brief An auxilliary function for mapping a function over
       * a list.
       */
      template< typename F, typename Ts, typename Accum >
      static constexpr auto
      map_aux( F&& f, Ts&& xs, Accum&& ys ){
	return map_aux(
	  forward<F>( f ),
	  tail( move( xs )),
	  cons( f( head( move( xs ))),
		forward<Accum>( ys )));
      }

      /**
       * @brief Map a function over a list.
       */
      template< typename F >
      friend constexpr auto
      map( F&& f, cell&& xs ){
	return map_aux( forward<F>( f ), move( xs ), nothing );

	static_assert(
	  islist_type( xs ),
	  "\nThe map function requires a list" );
      }

      /**
       * @brief Equality comparison
       */
      friend constexpr bool
      operator ==( const cell xs, const cell ys ){
	return (head( xs ) == head( ys )) && (tail( xs ) == tail( ys ));
      }
      
      /**
       * @brief Equality comparison
       */
      template< typename UHead, typename UTail >
      friend constexpr bool
      operator ==( const cell& xs, const cell<UHead,UTail>& ys ){
	return (head( xs ) == head( ys )) && (tail( xs ) == tail( ys ));
      }
      
      /**
       * @brief Equality comparison
       */
      template< typename T >
      friend constexpr bool
      operator ==( const cell&, const T& ){ return false; }

    }; // end of class static list


    template< typename T >
    constexpr bool
    islist_type( Type<T> ){
      return conditional_t<
	is_same<T,decay_t<T>>::value,
	false_type,
	bool_constant<islist_type(type<decay_t<T>>)>>::value;
    }

    constexpr bool
    islist_type( Type<Nothing> ){ return true; }

    template< typename Head, typename Tail >
    constexpr bool
    islist_type( Type<cell<Head,Tail>> ){
      return islist_type( type<Tail> );
    }

    template< typename T >
    constexpr bool
    islist_type( const T& ){ return islist_type( type<T> ); }




    template< typename T >
    constexpr auto
    cons( T&& x, const Nothing& ){
      return cell<decay_t<T>,Nothing>( forward<T>( x ), nothing );
    }

    constexpr auto
    list(){ return nothing; }

    template< typename T, typename ... Ts >
    constexpr auto
    list( T&& x, Ts&& ... xs ){
      return cons( forward<T>( x ), list( forward<Ts>( xs ) ... ));
    }



    
  } // end of namespace Core
} // end of namespace StaticData

#endif // !defined LIST_HPP_INCLUDED_981697518487840817
