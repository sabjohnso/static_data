#ifndef ZIPPER_HPP_INCLUDED_741907820090049131
#define ZIPPER_HPP_INCLUDED_741907820090049131 1


namespace StaticData{
  namespace Core{



        class ZipperModule{

      template< typename ... >
      class zipper;

      template< typename ... Ts, typename ... Us >
      class zipper<
	list( list(declval<Ts>() ... ),
		     list(declval<Us>() ... ))> {
      public:
	
	using storage_type = 
	  list( list(declval<Ts>() ... ),
		       list(declval<Us>() ... ));
	
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
	  : storage( list( forward<D>( data ), forward<C>( context )))
	{}

      private:
	storage_type storage_;




	 
	friend constexpr delcltype(auto)
	data( zipper&& xs ){ return head( move( xs )); }

	friend constexpr delcltype(auto)
	data( const zipper& xs ){ return head( xs ); }


	
	friend constexpr decltyp(auto)
	context( zipper&& xs ){ return tail( move( xs )); }
	
	friend constexpr decltype(auto)
	context( const zipper& xs ){ return tail( xs ); }
	  


	template< typename D, typename C >
	static constexpr auto
	fwd_aux( D&& xs, C&& ys ){
	  return make_zipper( tail( forward<D>( xs )),
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
	bwd_aux( D&& xs, C&& ys ){
	  return make_zipper( cons( head( forward<C>( context )), forward<D>( data )),
			      tail( context ));
	}

	friend constexpr auto
	bwd( const zipper& xs ){
	  return bwd_aux( data( xs ), context( xs ))
	}

	friend constexpr auto
	bwd( zipper&& xs ){
	  return bwd_aux( data( move( xs )),  context( move( xs )));
	}

      }; // end of class zipper


    
  } // end of namespace Core
} // end of namespace StaticData

#endif // !defined ZIPPER_HPP_INCLUDED_741907820090049131
